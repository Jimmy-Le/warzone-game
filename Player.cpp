#include "Player.h"
#include <iostream>
#include <vector>
using namespace std;

/***
 * Player Constructor, 
 * Initializes the set of territories, cards, and orderlist of a Player
 * TODO Update this to be the proper type
 */
Player::Player(){
    defendCollection = {"France", "Canada", "USA"};
    attackCollection = {"France", "Canada", "USA"};
    cardCollection = {"1", "2", "3"};
    orderCollection = FakeOrderList();
}

/***
 * toDefend()
 * Returns a list of territories that are to be defended
 * TODO Arbitrarily choose which territory to be defended
 */
vector<string> Player::toDefend(){
    cout << "printing Territory to defend" << endl;
    return defendCollection;
}

/***
 * toAttack()
 * Returns a list of territories that are to be attacked
 * TODO Arbitrarily choose which territory to be attacked
 */
vector<string> Player::toAttack(){
    cout << "printing Territory to attack" << endl;
    return attackCollection;
}

/***
 * issueOrder()
 * Creates an Order object and puts it in the player’s list of orders
 * TODO replace order object with actual Order class
 */
void Player::issueOrder(){

    FakeOrder* newOrder = new FakeOrder();
    orderCollection.add(newOrder);

}

/***
 * printPlayer()
 * Prints the player's details for debugging purposes
 */
void Player::printPlayer(){
    cout << "Player's Territories to Defend: " << endl;
    for (string territory : defendCollection) {
        cout << territory << " ";
    }
    cout << endl;

    cout << "Player's Territories to Attack: " << endl;
    for (string territory : attackCollection) {
        cout << territory << " ";
    }
    cout << endl;

    cout << "Player's Cards: " << endl;
    for (string card : cardCollection) {
        cout << card << " ";
    }
    cout << endl;   

    cout << "Player's Orders: " << endl;
    for (FakeOrder* order : orderCollection.orders) {
        order->printOrder();
    }
    cout << endl;
}


// ------------------------------- Fake Stuff (Delete After) --------------------------------
FakeOrder::FakeOrder(){
    FakeOrder::name = "Default Order";
}
void FakeOrder::printOrder(){
    cout << "Order Name: " << name << endl;
}

FakeOrderList::FakeOrderList(){
    orders = vector<FakeOrder*>();
}

void FakeOrderList::add(FakeOrder* order){
    orders.push_back(order);
}

void FakeOrderList::printOrderList(){
    cout << "Order List: " << endl;
    for (FakeOrder* order : orders) {
        order->printOrder();
    }
}




