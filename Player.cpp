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
    this->name = new string("John Doe");
    this->defendCollection = new vector<string>({"France", "Canada", "USA"});
    this->attackCollection = new vector<string>({"Russia", "Ukraine", "China"});
    this->cardCollection = new vector<string>({"1", "2", "3"});
    this->orderCollection = new FakeOrderList();
}
/***
 * Parameterized Player Constructor,
 * Initializes the set of territories, cards, and orderlist of a Player
 * Gives the player a name
 * TODO Update this to be the proper type
 */
Player::Player(string name) {
    this->name = new string(name);
    this->defendCollection = new vector<string>({"France", "Canada", "USA"});
    this->attackCollection = new vector<string>({"Russia", "Ukraine", "China"});
    this->cardCollection = new vector<string>({"1", "2", "3"});
    this->orderCollection = new FakeOrderList();
}

/***
 * Player Destructor
 * Frees all the dynamically allocated memory inside the Player object
 */
Player::~Player(){
    delete name;
    delete defendCollection;
    delete attackCollection;
    delete cardCollection;
    delete orderCollection;
}
/***
 * Player Copy Constructor
 * Creates a deep copy of the Player object
 */
Player::Player(const Player& other){
    // Deep copy of defendCollection
    defendCollection = new vector<string>(*other.defendCollection);
    
    // Deep copy of attackCollection
    attackCollection = new vector<string>(*other.attackCollection);
    
    // Deep copy of cardCollection
    cardCollection = new vector<string>(*other.cardCollection);
    
    // Deep copy of orderCollection
    // TODO Replace with actual OrderList class
    orderCollection = new FakeOrderList();
    for (FakeOrder* order : other.orderCollection->orders) {
        FakeOrder* newOrder = new FakeOrder(*order); // Assuming FakeOrder has a copy constructor
        orderCollection->add(newOrder);
    }
}

/***
 * Overloading the << operator for easy printing of Player details
 * TODO Update this to be the proper type
 */
ostream& operator<<(ostream& out, const Player& player) {
    out << "Player Details:" << endl;

    out << "Name: " << *player.name << endl;                                // Player's name

    out << "\n-Territories to Defend: " << endl;                                      // Territories to be defended
    for (const string& territory : *player.defendCollection) {
        out << territory << " " <<endl;
    }

    out << "\n-Territories to Attack: " << endl;                                       // Territories to be attacked
    for (const string& territory : *player.attackCollection) {
        out << territory << " " << endl;
    }

    out << "\n-Cards: " << endl;
    for (const string& card : *player.cardCollection) {                     // Cards in player's hand
        out << card << " " << endl;
    }

    out << "\n-Orders: " << endl;
    for (FakeOrder* order : player.orderCollection->orders) {               // Orders in player's order list
        order->printOrder();                                              
    }

    return out;
}

/***
 * toDefend() 
 * Returns a list of territories that are to be defended
 * TODO Arbitrarily choose which territory to be defended
 */
vector<string>* Player::toDefend(){
    // cout << "printing Territory to defend" << endl;
    return defendCollection;
}

/***
 * toAttack()
 * Returns a list of territories that are to be attacked
 * TODO Arbitrarily choose which territory to be attacked
 */
vector<string>* Player::toAttack(){
    // cout << "printing Territory to attack" << endl;
    return attackCollection;
}

/***
 * issueOrder()
 * Creates an Order object and puts it in the player’s list of orders
 * TODO replace order object with actual Order class
 */
void Player::issueOrder(){

    FakeOrder* newOrder = new FakeOrder();
    orderCollection->add(newOrder);

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




