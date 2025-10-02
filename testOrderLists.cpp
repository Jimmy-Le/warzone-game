#include "Orders.h"
#include "Player.h"
#include <string>

int main() {
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
    Player p1("Umer");

    // Issue a few different orders
    p1.issueOrder(5, "India", "China", "deploy");
    p1.issueOrder(10, "USA", "Canada", "advance");
    p1.issueOrder(3, "Germany", "Poland", "bomb");
    p1.issueOrder(8, "France", "Italy", "airlift");
    //p1.issueOrder(0, "Pakistan", "Bangladesh", "negotiate");

    // Print out player details (<< operator)
    cout << p1 << endl;
    return 0;
}


