#include "Player.h"

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
    this->orderCollection = new Orderlist(); //the default constructor of orderlist used i didnt define any for orderlist class
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
    this->orderCollection = new Orderlist();//same as above
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
    orderCollection = new Orderlist();
    for ( const auto& order : other.orderCollection->orderList) {
        Orders* newOrder = new Orders(*order); // Assuming FakeOrder has a copy constructor
        //move was not tend to add / insert order objects to vector . since the orderlist is a vector use the built in functions to add 
        //below i have changed 
        //again maybe polymorphism /many forms
        orderCollection->orderList.push_back(make_unique<Orders>(*newOrder));
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
    out << "\n-Orders: " << endl;
    for (const auto& order : player.orderCollection->orderList) {
        if (auto d = dynamic_cast<DeployOrder*>(order.get()))
            out << *d << endl;
        else if (auto a = dynamic_cast<Advance*>(order.get()))
            out << *a << endl;
        else if (auto b = dynamic_cast<Bomb*>(order.get()))
            out << *b << endl;
        else if (auto al = dynamic_cast<Airlift*>(order.get()))
            out << *al << endl;
        else if (auto n = dynamic_cast<Negotiate*>(order.get()))
            out << *n << endl;
        else
            out << *order << endl; // fallback: base class print
    } //there is a more compact way like use another method and then making it virtual that i currently do not understand
    //but the dynamic_cast's ability to verify tpyes at run time does make this a bit better and easy to understand , but definitely huge chunk of code
    //order.get() gives you the raw Orders* from the unique_ptr.

//dynamic_cast<DeployOrder*> checks at runtime if it’s actually a DeployOrder.

//If yes, it returns a non-null pointer and you print with the subclass’s operator<<.

//If not, it tries the next branch.

//If none match, it falls back to the base Orders print.


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
 * TODO maybe replace move with an insert function
 */
void Player::issueOrder(int numberOfArmyUnits, 
                        string sourceTerritory, 
                        string targetTerritory, 
                        string orderType) 
{
    cout << "Issuing Order of type: " << orderType << endl;

    if (orderType == "deploy") {
        DeployOrder d = DeployOrder(numberOfArmyUnits, sourceTerritory, targetTerritory);
        orderCollection->orderList.push_back(
            unique_ptr<Orders>(new DeployOrder(d))  // copy-construct from d
        );
    } 
    else if (orderType == "advance") {
        Advance a = Advance(numberOfArmyUnits, sourceTerritory, targetTerritory);
        orderCollection->orderList.push_back(
            unique_ptr<Orders>(new Advance(a))
        );
    } 
    else if (orderType == "bomb") {
        Bomb b= Bomb(numberOfArmyUnits, sourceTerritory, targetTerritory);
        orderCollection->orderList.push_back(
            unique_ptr<Orders>(new Bomb(b))
        );
    } 
    else if (orderType == "airlift") {
        Airlift al= Airlift(numberOfArmyUnits, sourceTerritory, targetTerritory);
        orderCollection->orderList.push_back(
            unique_ptr<Orders>(new Airlift(al))
        );
    } 
    // else if (orderType == "negotiate") {
    //     Negotiate n(numberOfArmyUnits, sourceTerritory, targetTerritory);
    //     orderCollection->orderList.push_back(
    //         unique_ptr<Orders>(new Negotiate(n))
    //     );
    //} 
    else {
        cout << "Invalid order type: " << orderType << endl;
        return;
    }

    cout << "Order successfully created and added to list." << endl;
}





// ------------------------------- Fake Stuff (Delete After) --------------------------------
// FakeOrder::FakeOrder(){
//     FakeOrder::name = "Default Order";
// }
// void FakeOrder::printOrder(){
//     cout << "Order Name: " << name << endl;
// }

// FakeOrderList::FakeOrderList(){
//     orders = vector<FakeOrder*>();
// }

// void FakeOrderList::add(FakeOrder* order){
//     orders.push_back(order);
// }

// void FakeOrderList::printOrderList(){
//     cout << "Order List: " << endl;
//     for (FakeOrder* order : orders) {
//         order->printOrder();
//     }
// }



