#include <iostream>
#include <vector>
#include "market.hpp"

int main(int argc, char *argv[])
{
    Order order1(908787, "FDAX", Order::Side::Bid, 
    	Order::Type::Limit , 87.50, 1000);

    std::cout << order1 << std::endl;

    //   Create some orders
    //     Bid        Ask 
    // 1000@87.50  2000@88.00
    // 2278@87.00  3000@88.50
    // 8556@86.50  5443@89.00
    // 6552@86.00  7878@89.50
    //

   	Order order2(908788, "FDAX", Order::Side::Bid, 
    	Order::Type::Limit , 87.00, 2278);

   	Order order3(908789, "FDAX", Order::Side::Ask, 
    	Order::Type::Limit , 88.00, 2000);

   	Order order4(908790, "FDAX", Order::Side::Ask, 
    	Order::Type::Limit , 88.50, 3000);

   	Order order5(908791, "FDAX", Order::Side::Ask, 
    	Order::Type::Limit , 89.00, 5443);
   	
   	Order order6(908792, "FDAX", Order::Side::Bid, 
    	Order::Type::Limit , 86.50, 8556);
   	
   	Order order7(908793, "FDAX", Order::Side::Ask, 
    	Order::Type::Limit , 89.50, 7878);

   	Order order8(908794, "FDAX", Order::Side::Bid, 
    	Order::Type::Limit , 86.00, 6552);


   	// Create the market

   	Market market(2387, "FDAX");

   	// Add order to market

   	market.market_insert_order(order1);
   	market.market_insert_order(order2);
   	market.market_insert_order(order3);
   	market.market_insert_order(order4);
   	market.market_insert_order(order5);
   	market.market_insert_order(order6);
   	market.market_insert_order(order7);
   	market.market_insert_order(order8);


   	// Display the market

   	market.market_display_book();


   	// Add order +1000@87.5
   	Order order9(908795, "FDAX", Order::Side::Bid, 
    	Order::Type::Limit , 87.50, 1000);

   	std::cout << "Adding order = " << order9 << std::endl;

   	market.market_insert_order(order9);

   	//Display the market now

   	market.market_display_book();

   	// Delete order 908790
   	std::cout << "Deleting order = " << order4 <<std::endl;

   	market.market_delete_order(order4);

   	market.market_display_book();

   	std::cout << "Finding order side Ask, Id 908791 = "
   			  << market.market_find_order(Order::Side::Ask, 908791)
   			  << std::endl;

    // Modify order

    std::cout << "Modifying order side Ask, Id 908791 " << std::endl; 
    
    market.market_modify_order(Order::Side::Ask, 908791, 93, 8001);

    market.market_display_book();

    std::cout << order5 << std::endl;

    // Add order to match

    Order order10(908796, "FDAX", Order::Side::Bid, 
      Order::Type::Limit , 88, 3000);

    market.market_insert_order(order10);

    market.market_display_book();

    market.market_order_match(order10);

    market.market_display_book();

    Order order11(908799, "FDAX", Order::Side::Ask, 
      Order::Type::Limit , 87.5, 3000);

    market.market_insert_order(order11);

    market.market_display_book();

    market.market_order_match(order11);

    market.market_display_book();

    return 0;
}
