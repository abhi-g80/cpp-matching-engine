#include "market.hpp"
#include <string>
#include <map>
#include <iostream>

// This is the interface, applications will talk to

using Markets = std::map<std::string, Market>;

class Matcher
{
    public:
        Matcher(std::map<uint32_t, std::string> instruments)
        {
            for(auto itr = instruments.begin(); itr != instruments.end(); itr++)
            {
                markets.insert(std::make_pair(itr->second, Market(itr->first, itr->second)));
            }
        }

        bool insert(Order & order)
        {
            Markets::iterator i = markets.find(order.get_order_symbol());
            
            if (i == markets.end())
            {
                throw std::logic_error("Instrument not found");
                return false;
            }
            
            return i->second.market_insert_order(order);
        }

        void cancel(Order& order)
        {
            Markets::iterator i = markets.find(order.get_order_symbol());
            
            if (i == markets.end())
            {
                throw std::logic_error("Instrument not valid");
            }
            
            i->second.market_delete_order(order);
        }

        Order& find(std::string symbol, Order::Side side, int64_t id )
        {
            Markets::iterator i = markets.find(symbol);

            if (i == markets.end())
            {
                throw std::logic_error("Instrument not valid");
            }
            
            return i->second.market_find_order(side, id);
        }

        void match(std::string symbol, Order & order)
        {
            Markets::iterator i = markets.find(symbol);
            
            if (i == markets.end())
            {
                throw std::logic_error("Instrument not found");
                return;
            }
            
            return i->second.market_order_match(order);
        }

        void display(std::string symbol) const
        {
            Markets::const_iterator i = markets.find(symbol);
            
            if (i == markets.end())
            {
                throw std::logic_error("Instrument not found");
                return ;
            }
            
            i->second.market_display_book();
        }

        void display() const
        {
            std::cout << "Tradable symbols:" << std::endl;
            std::cout << "-----------------" << std::endl;

            Markets::const_iterator i;
            
            for(i = markets.begin(); i != markets.end(); ++i)
            {
                std::cout << i->first << std::endl;
            }
        }

    private:
        Markets markets;
};