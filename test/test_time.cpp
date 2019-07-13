#include <iostream>
#include <map>
#include "matcher.hpp"
#include "timer.hpp"

int main(int argc, char *argv[])
{
    // Create some markets
    // 19031 -> FDAX 1903
    // 19032 -> FESC 1903
    // 19061 -> FDAX 1906

    TimeStamper::Timer t;

    std::map<uint32_t, std::string> instruments; 

    instruments.insert(std::make_pair(19031, "FDAX 1903"));
    instruments.insert(std::make_pair(19032, "FESC 1903"));
    instruments.insert(std::make_pair(19061, "FDAX 1906"));

    // Initiate the markets
    Matcher order_matcher(instruments);

    // Insert orders for FDAX 1903

    Order order1(908787,"FDAX 1903", Order::Side::Bid, 
        Order::Type::Limit , 84.5, 2278);

    Order order2(908788, "FDAX 1903", Order::Side::Bid, 
        Order::Type::Limit , 87.00, 2278);

    Order order3(908789, "FDAX 1903", Order::Side::Ask, 
        Order::Type::Limit , 88.00, 2000);

    Order order4(908790, "FDAX 1903", Order::Side::Ask, 
        Order::Type::Limit , 88.50, 3000);

    Order order5(908791, "FDAX 1903", Order::Side::Ask, 
        Order::Type::Limit , 89.00, 5443);
    
    Order order6(908792, "FDAX 1903", Order::Side::Bid, 
        Order::Type::Limit , 86.50, 8556);
    
    Order order7(908793, "FDAX 1903", Order::Side::Ask, 
        Order::Type::Limit , 89.50, 7878);

    Order order8(908794, "FDAX 1903", Order::Side::Bid, 
        Order::Type::Limit , 86.00, 6552);    

    // Insert into market

    uint64_t start = t.microseconds();
    order_matcher.insert(order1);
    uint64_t end = t.microseconds();
    std::cout << "Time taken (us) = " << (end - start) << std::endl;


    start = t.microseconds();
    order_matcher.insert(order2);
    end = t.microseconds();
    std::cout << "Time taken (us) = " << (end - start) << std::endl;


    start = t.microseconds();
    order_matcher.insert(order3);
    end = t.microseconds();
    std::cout << "Time taken (us) = " << (end - start) << std::endl;

    order_matcher.insert(order4);
    order_matcher.insert(order5);
    order_matcher.insert(order6);
    order_matcher.insert(order7);
    order_matcher.insert(order8);

    std::cout << order1 << order2 << order3 << order4
              << order6 << order7 << order8 << std::endl; 
    // // Display
    order_matcher.display("FDAX 1903");
    order_matcher.display();

    // Trade in FDAX 1903

    Order order_m(908795, "FDAX 1903", Order::Side::Bid,
        Order::Type::Limit, 88.5, 3500);

    start = t.microseconds();
    order_matcher.insert(order_m);
    end = t.microseconds();
    std::cout << "Time taken matching order (us) = " << (end - start) << std::endl;

    order_matcher.display("FDAX 1903");

    start = t.microseconds();
    order_matcher.match("FDAX 1903", order_m);    
    end = t.microseconds();
    std::cout << "Time taken trade (us) = " << (end - start) << std::endl;

    Order order9(908763, "FDAX 1906", Order::Side::Ask, 
        Order::Type::Limit , 567, 7878);

    Order order10(908764, "FDAX 1906", Order::Side::Bid, 
        Order::Type::Limit , 566, 6552);

    start = t.microseconds();
    order_matcher.insert(order9);
    end = t.microseconds();
    std::cout << "Time taken FDAX 1906 (us) = " << (end - start) << std::endl;

    start = t.microseconds();    
    order_matcher.insert(order10);
    end = t.microseconds();
    std::cout << "Time taken FDAX 1906 (us) = " << (end - start) << std::endl;

    std::cout << order9 << order10 << std::endl;

    order_matcher.display("FDAX 1906");

    return 0;


}
