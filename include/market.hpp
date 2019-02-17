#include <ostream>
#include <map>
#include "order.hpp"
#include "instrument.hpp"
#include "idGenerator.hpp"

using string = std::string;

class Market : public Instrument, public IDGenerator
{
    public:
        Market(uint32_t id, string symbol) : Instrument(id, symbol), IDGenerator(id)
        {

        }

        bool market_insert_order(Order&);
        bool market_delete_order(Order&);
        void market_modify_order(Order::Side, uint64_t, double, long);
        Order& market_find_order(Order::Side, uint64_t);
        void market_display_book () const;
        void market_order_match(Order&);
        void market_trade_dispatch(long, double);

    private:
        using BidOrders = std::multimap<double, Order, std::greater<double>>;
        using AskOrders = std::multimap<double, Order, std::less<double>>;

        BidOrders market_bid_orders;
        AskOrders market_ask_orders;
};

bool Market::market_insert_order(Order& order)
{
    try
    {
        if(order.get_order_side() == Order::Side::Bid)
            market_bid_orders.insert(std::pair<double, Order> (order.get_order_price(),
                                                               order));
        else
            market_ask_orders.insert(std::pair<double, Order> (order.get_order_price(),
                                                               order));
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Market::market_insert_order() - " << e.what() <<std::endl;
        return false;
    }
}

Order& Market::market_find_order(Order::Side side, uint64_t id)
{
    if(side == Order::Side::Bid)
    {
        for(auto itr = market_bid_orders.begin(); itr != market_bid_orders.end(); itr++)
        {
            if(id == itr->second.get_order_id())
            {
                return itr->second;
            }
        }
    }
    else
    {
        for(auto itr = market_ask_orders.begin(); itr != market_ask_orders.end(); itr++)
        {
            if(id == itr->second.get_order_id())
            {
                return itr->second;
            }
        }        
    }

    throw std::exception();
}

void Market::market_modify_order(Order::Side side, uint64_t id, double price, long quantity)
{
    Order& order = market_find_order(side, id);

    order.set_order_quantity(quantity);

    order.set_order_price(price);

    Order order_cpy = order;

    market_delete_order(order);

    market_insert_order(order_cpy);
}

bool Market::market_delete_order(Order& order)
{
    uint64_t id = order.get_order_id();

    if (order.get_order_side() == Order::Side::Bid)
    {
        for(auto itr = market_bid_orders.begin(); itr != market_bid_orders.end();
            itr++)
        {
            if(itr->second.get_order_id() == id)
            {
                market_bid_orders.erase(itr);
                return true;
            }
        }

        return false;
    } 
    else 
    {
        for(auto itr = market_ask_orders.begin(); itr != market_ask_orders.end();
            itr++)
        {
            if(itr->second.get_order_id() == id)
            {
                market_ask_orders.erase(itr);
                return true;
            }
        }

        return false;
    }
}

void Market::market_order_match(Order & _order)
{
    Order & order = market_find_order(_order.get_order_side(), _order.get_order_id());

    double price = order.get_order_price();
    long quantity = order.get_order_quantity();
    long traded_quantity = 0;

    if(order.get_order_side() == Order::Side::Bid)
    {
        auto curr_best_ask = market_ask_orders.begin();

        while(price >= curr_best_ask->first && quantity != 0)
        {
            long curr_best_quantity = curr_best_ask->second.get_order_quantity();

            if(quantity > curr_best_quantity)
            {
                traded_quantity = curr_best_quantity;
                market_trade_dispatch(traded_quantity, curr_best_ask->second.get_order_price());
                market_delete_order(curr_best_ask->second);
                quantity -= traded_quantity;
                order.set_order_quantity(quantity);
                curr_best_ask = market_ask_orders.begin();
            }
            else if (quantity == curr_best_quantity)
            {
                traded_quantity = quantity;
                market_trade_dispatch(traded_quantity, curr_best_ask->second.get_order_price());
                market_delete_order(order);
                market_delete_order(curr_best_ask->second);
                quantity = 0;
                break;
            }
            else
            {
                traded_quantity = quantity;
                market_trade_dispatch(traded_quantity, curr_best_ask->second.get_order_price());
                market_delete_order(order);
                curr_best_ask->second.set_order_quantity(curr_best_quantity - traded_quantity);
                quantity = 0;
                break;                
            }
        }
    }
    else
    {
        auto curr_best_bid = market_bid_orders.begin();

        while(price <= curr_best_bid->first && quantity != 0)
        {
            long curr_best_quantity = curr_best_bid->second.get_order_quantity();

            if(quantity > curr_best_quantity)
            {
                traded_quantity = curr_best_quantity;
                market_trade_dispatch(traded_quantity, curr_best_bid->second.get_order_price());
                market_delete_order(curr_best_bid->second);
                quantity -= traded_quantity;
                order.set_order_quantity(quantity);
                curr_best_bid = market_bid_orders.begin();
            }
            else if (quantity == curr_best_quantity)
            {
                traded_quantity = quantity;
                market_trade_dispatch(traded_quantity, curr_best_bid->second.get_order_price());
                market_delete_order(order);
                market_delete_order(curr_best_bid->second);
                quantity = 0;
                break;
            }
            else
            {
                traded_quantity = quantity;
                market_trade_dispatch(traded_quantity, curr_best_bid->second.get_order_price());
                market_delete_order(order);
                curr_best_bid->second.set_order_quantity(curr_best_quantity - traded_quantity);
                quantity = 0;
                break;                
            }
        }
    }   
}

void Market::market_trade_dispatch(long quantity, double price)
{
    std::cout << "Trade on " << get_instrument_symbol() << ": "
              << "Price = " << price << ", Quantity = " << quantity
              << std::endl;
}

void Market::market_display_book () const
{
    std::map<double, long, std::greater<double>> total_bid_side;
    std::map<double, long, std::less<double>> total_ask_side;

    for(auto itr = market_bid_orders.begin(); itr != market_bid_orders.end(); 
        itr = market_bid_orders.upper_bound(itr->first))
    {   
        auto result = market_bid_orders.equal_range(itr->first);
        
        long sum = 0;
        
        for(auto it = result.first; it != result.second; it++)
        {
            sum += it->second.get_order_quantity();
        }
        
        total_bid_side.insert(std::pair<double, long> (itr->first, sum));
    }

    for(auto itr = market_ask_orders.begin(); itr != market_ask_orders.end(); 
        itr = market_ask_orders.upper_bound(itr->first))
    {   
        auto result = market_ask_orders.equal_range(itr->first);
        
        long sum = 0;
        
        for(auto it = result.first; it != result.second; it++)
        {
            sum += it->second.get_order_quantity();
        }
        
        total_ask_side.insert(std::pair<double, long> (itr->first, sum));
    }

    std::cout << "Market for " << get_instrument_symbol() << std::endl;
    std::cout << "Bid"  << "\t\t" << "Ask" << std::endl;
    std::cout << "---------\t---------" << std::endl;

    for(auto bid_itr = total_bid_side.begin(), ask_itr = total_ask_side.begin(),
        end_bid = total_bid_side.end(), end_ask = total_ask_side.end();
        bid_itr != end_bid || ask_itr != end_ask;)
    {
        if(bid_itr != end_bid)
        {
            std::cout << bid_itr->second << " @ " << bid_itr->first << "\t";
            bid_itr++;
        }
        else
        {
            std::cout << 0 << " " << "X" << "\t";
        }

        if(ask_itr != end_ask)
        {
            std::cout << ask_itr->second << " @ " << ask_itr->first << std::endl;
            ask_itr++;
        }
        else
        {
            std::cout << 0 << " @ " << "X" << std::endl;
        }
    }
}