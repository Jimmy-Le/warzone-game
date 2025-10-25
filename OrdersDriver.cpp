#include "Orders.h"
#include "Player.h"
#include <string>
#include "OrdersDriver.h"


int testOrderList() {
      // 1️⃣ Base Order creation
    Orders baseOrder(5, "Canada", "USA");
    cout << "\nBase Order:\n" << baseOrder << endl;

    // 2️⃣ Subclass creation
    DeployOrder deploy(10, "Toronto", "Montreal");
    Bomb bomb(3, "Berlin", "Paris");
    Advance advance(7, "Quebec", "Ottawa");
    Airlift airlift(12, "Rome", "Milan");
    Blockade blockade(2, "Tokyo", "Osaka");
    Negotiate negotiate(90, "Delhi", "Beijing");

    cout << "\n===== Individual subclass prints =====" << endl;
    cout << deploy << endl;
    cout << bomb << endl;
    cout << advance << endl;
    cout << airlift << endl;
    cout << blockade << endl;
    cout << negotiate << endl;

    // 3️⃣ Polymorphism test
    cout << "\n===== Polymorphism test =====" << endl;
    vector<unique_ptr<Orders>> polymorphicOrders;
    polymorphicOrders.push_back(make_unique<DeployOrder>(deploy));
    polymorphicOrders.push_back(make_unique<Bomb>(bomb));
    polymorphicOrders.push_back(make_unique<Airlift>(airlift));
    polymorphicOrders.push_back(make_unique<Advance>(advance));
    polymorphicOrders.push_back(make_unique<Blockade>(blockade));

    for (auto &o : polymorphicOrders) {
        cout << *o << endl;
        o->validate();
        cout << endl;
        o->execute();
        cout << "\n--------------------------------------\n";
    }

    // 4️⃣ Deep copy / assignment test
    cout << "\n===== Copy & Assignment test =====" << endl;
    Orders copyOrder = baseOrder; // copy constructor
    Orders assignedOrder;
    assignedOrder = baseOrder;    // assignment operator
    cout << "Copied:\n" << copyOrder << endl;
    cout << "Assigned:\n" << assignedOrder << endl;
    DeployOrder copyDeployOrder = deploy;
    cout << "Copied:\n" << copyDeployOrder << endl;
    cout << "Assigned:\n" << deploy << endl;
    

    // 5️⃣ Orderlist functionality
    cout << "\n===== Testing Orderlist =====" << endl;
    Orderlist list;
    list.orderList.push_back(make_unique<DeployOrder>(deploy));
    list.orderList.push_back(make_unique<Bomb>(bomb));
    list.orderList.push_back(make_unique<Airlift>(airlift));

    cout << "\nInitial Orderlist:\n";
    for (auto &o : list.orderList) cout << *o << endl;

    // Remove a specific order
    cout << "\nRemoving Bomb order...\n";
    list.remove(bomb);
    cout << "After removal:\n";
    for (auto &o : list.orderList) cout << *o << endl;

    // Move an order
    cout << "\nMoving Airlift to index 0...\n";
    list.move(airlift, 0);
    cout << "After moving:\n";
    for (auto &o : list.orderList) cout << *o << endl;

    cout << "\n===== END OF DRIVER TEST =====" << endl;
    return 0;

}


