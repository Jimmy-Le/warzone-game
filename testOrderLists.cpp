#include "Orders.h"
#include "Player.h"
#include <string>
#include "testOrderLists.h"

int testOrderList() {
    //Orders b = Orders(10 ,"Australia" , "Kuwait");
    Advance a = Advance(50 , "Qatar" , "Poland");
    Orderlist arr;
    Bomb bomb{100,"Japan","USA"};
    Bomb bomb2(200 , "Kenya" , "Nigeria");
    cout<< a;
    cout<< bomb ;
    cout<< bomb2;
    arr.orderList.push_back(make_unique<Advance>(a));
    arr.orderList.push_back(make_unique<Bomb>(bomb));
    arr.orderList.push_back(make_unique<Bomb>(bomb2));
    cout<<"BEFORE REMOVE" <<endl;
    cout<<*arr.orderList[0] <<endl;
    cout<<*arr.orderList[1] <<endl;
    cout<<*arr.orderList[2] <<endl;

    arr.move(bomb2 , 0);
    //arr.remove(a);
    cout<<"AFTER REMOVE" <<endl;
    cout<<*arr.orderList[0]<<endl;
    cout<<*arr.orderList[1] <<endl;
    cout<<*arr.orderList[2] <<endl;



    // Create a player
    // Player p1("Umer");

    // Issue a few different orders
    // p1.issueOrder(std::make_unique<DeployOrder>(3, "USA", "Russia"));
    // p1.issueOrder(std::make_unique<Advance>(10, "USA", "Canada"));
    // p1.issueOrder(std::make_unique<Bomb>(3, "Germany", "Poland"));
    // p1.issueOrder(std::make_unique<Airlift>(5, "France", "Italy"));
    //p1.issueOrder(0, "Pakistan", "Bangladesh", "negotiate");

    // Print out player details (<< operator)
    // cout << p1 << endl;
    return 0;
}


