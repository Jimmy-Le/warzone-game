#include "Player.h"

/***
 * Player Constructor, 
 * Initializes the set of territories, cards, and orderlist of a Player
 * TODO Update this to be the proper type
 */
Player::Player(){
    this->name = new string("John Doe");
    this->defendCollection = new vector<Territory*>();
    this->attackCollection = new vector<Territory*>();
    this->cardCollection = new Hand();
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
    this->defendCollection = new vector<Territory*>();
    this->attackCollection = new vector<Territory*>();
    this->cardCollection = new Hand();
    this->orderCollection = new Orderlist();//same as above
}

/***
 * Player Destructor
 * Frees all the dynamically allocated memory inside the Player object
 */
Player::~Player(){
    delete name;


    // Free each Territory pointer in the territories to defend collection
    for (Territory* territory : *defendCollection) {
        delete territory;
    }

    // Free each Territory pointer in the territories to attack collection
    for (Territory* territory : *attackCollection) {
        delete territory;
    }

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
    defendCollection = new vector<Territory*>(*other.defendCollection);
    
    // Deep copy of attackCollection
    attackCollection = new vector<Territory*>(*other.attackCollection);
    
    // Deep copy of cardCollection
    cardCollection = new Hand(*other.cardCollection);
    
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
    for (const Territory* territory : *player.defendCollection) {
        out << territory->getName() << " " <<endl;
    }

    out << "\n-Territories to Attack: " << endl;                                       // Territories to be attacked
    for (const Territory* territory : *player.attackCollection) {
        out << territory->getName() << " " << endl;
    }

    out << "\n-Cards: " << endl;
    for (const auto& card : *player.cardCollection->hand) {                     // Cards in player's hand
        out << card.cardType << " " << endl;
    }

    out << "\n-Orders: " << endl;

    // Use dynamic_cast to identify the actual type and call the appropriate function
    for (const auto& order : player.orderCollection->orderList) {
        out << *order <<endl;
    };//there is a more compact way like use another method and then making it virtual that i currently do not understand
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
vector<Territory*>* Player::toDefend(){
    return defendCollection;
}

/***
 * toAttack()
 * Returns a list of territories that are to be attacked
 * TODO Arbitrarily choose which territory to be attacked
 */
vector<Territory*>* Player::toAttack(){
    return attackCollection;
}

/***
 * issueOrder()
 * Creates an Order object and puts it in the player’s list of orders
 * TODO replace order object with actual Order class
 * TODO maybe replace move with an insert function
 */
void Player::issueOrder(std::unique_ptr<Orders> order) 
{

    string orderType = typeid(*order).name();                    // Get the type name of the order object
    cout << "Issuing Order of type: " << orderType << endl;

    orderCollection->orderList.push_back(std::move(order));

    cout << "Order successfully created and added to list." << endl;
}


/***
 * addToDefend()
 * Adds a territory to the list of territories to be defended
 */
void Player::addToDefend(Territory* territory) {
    if (territory != nullptr) {
        defendCollection->push_back(territory);
    }
}

/***
 * addToAttack()
 * Adds a territory to the list of territories to be attacked
 */
void Player::addToAttack(Territory* territory) {
    if (territory != nullptr) {
        attackCollection->push_back(territory);
    }
}



