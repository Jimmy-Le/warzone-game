#include "Orders.h"


int testOrderLists() {
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
    

    // cout<<"[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]" <<endl;
    // cout<<"------------------------------------------------------------" <<endl;
    // arr.move(bomb , 0);

    
    return 0;
    



};
