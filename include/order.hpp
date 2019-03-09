#include <iostream>
#include <vector>
#include <string>
#include <ostream>

using string = std::string;

class Order
{
    public:
        enum Side { Bid, Ask };
        enum Type { Market, Limit };

        Order(uint64_t client_orderid, 
            string symbol, Side side, Type type, 
            double price, long quantity)
        {
            this->client_orderid = client_orderid;
            this->orderid = 0;
            this->symbol = symbol;
            this->side = side;
            this->type = type;
            this->price = price;
            this->quantity = quantity;
        }

        uint64_t get_client_order_id() const {return this->client_orderid; }
        uint64_t get_order_id() const { return this->orderid; }
        string get_order_symbol() const { return this->symbol; }
        Side get_order_side() const { return this->side; }
        Type get_order_type() const { return this->type; }
        double get_order_price() const { return this->price; }
        long get_order_quantity() const { return this->quantity; }
        
        friend std::ostream& operator<<( std::ostream&, const Order& );

        void set_order_id(uint64_t id) { this->orderid = id; }
        void set_order_quantity(long quantity) { this->quantity = quantity; }
        void set_order_price(double price) { this->price = price; }

    private:
        uint64_t client_orderid;
        uint64_t orderid;
        string symbol;
        Side side;
        Type type;
        double price;
        long quantity;

};

inline std::ostream& operator<<( std::ostream& ostream, const Order& order )
{
  return ostream
         << "ClientOrderID: " << order.get_client_order_id() << ", "
         << "OrderID: " << order.get_order_id() << ", "
         << "OrderSymbol: " << order.get_order_symbol() << ", "
         << "OrderSide: " << order.get_order_side() << ", "
         << "OrderType: " << order.get_order_type() << ", "
         << "OrderPrice: " << order.get_order_price() << ", "
         << "OrderQuantity: " << order.get_order_quantity() << std::endl;
}