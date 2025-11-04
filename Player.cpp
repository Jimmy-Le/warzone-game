#include "Player.h"

/***
 * Player Constructor,
 * Initializes the set of territories, cards, and orderlist of a Player
 */
Player::Player()
{
    this->name = new string("John Doe");
    Territory* t = new Territory("Mexico");
    this->defendCollection = new vector<Territory *>();
    this->defendCollection->push_back(t);
    this->attackCollection = new vector<Territory *>();
    this->cardCollection = new Hand();
    this->orderCollection = new Orderlist(); // the default constructor of orderlist used i didnt define any for orderlist class
}
/***
 * Parameterized Player Constructor,
 * Initializes the set of territories, cards, and orderlist of a Player
 * Gives the player a name
 */
Player::Player(string name)
{
    this->name = new string(name);
    this->defendCollection = new vector<Territory *>();
    this->attackCollection = new vector<Territory *>();
    this->cardCollection = new Hand();
    this->orderCollection = new Orderlist(); // same as above
}

/***
 * Player Destructor
 * Frees all the dynamically allocated memory inside the Player object
 */
Player::~Player()
{
    delete name;

    // Free each Territory pointer in the territories to defend collection
    for (Territory *territory : *defendCollection)
    {
        delete territory;
    }

    // Free each Territory pointer in the territories to attack collection
    for (Territory *territory : *attackCollection)
    {
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
Player::Player(const Player &other)
{
    // Deep copy of defendCollection
    defendCollection = new vector<Territory *>(*other.defendCollection);

    // Deep copy of attackCollection
    attackCollection = new vector<Territory *>(*other.attackCollection);

    // Deep copy of cardCollection
    cardCollection = new Hand(*other.cardCollection);

    // Deep copy of orderCollection
    orderCollection = new Orderlist();
    for (const auto &order : other.orderCollection->orderList)
    {
        Orders *newOrder = new Orders(*order); //objects from an abstract class cannot be instantiated
        orderCollection->orderList.push_back(make_unique<Orders>(*newOrder));
    }
}

/***
 * Overloading the << operator for easy printing of Player details
 */
ostream &operator<<(ostream &out, const Player &player)
{
    out << "Player Details:" << endl;

    out << "Name: " << *player.name << endl; // Player's name

    out << "\n-Territories to Defend: " << endl; // Territories to be defended
    for (const Territory *territory : *player.defendCollection)
    {
        out << territory->getName() << " " << endl;
    }

    out << "\n-Territories to Attack: " << endl; // Territories to be attacked
    for (const Territory *territory : *player.attackCollection)
    {
        out << territory->getName() << " " << endl;
    }

    out << "\n-Cards: " << endl;
    out << *player.cardCollection << endl; // Player's cards

    out << "\n-Orders: " << endl;

    // Use dynamic_cast to identify the actual type and call the appropriate function
    // dynamic_cast<DeployOrder*> checks at runtime if it’s actually a DeployOrder.
    // If yes, it returns a non-null pointer and you print with the subclass’s operator<<.
    // If not, it tries the next branch.
    // If none match, it falls back to the base Orders print.
    for (const auto &order : player.orderCollection->orderList)
    {
        out << *order << endl;
    }; // there is a more compact way like use another method and then making it virtual that i currently do not understand
    // but the dynamic_cast's ability to verify tpyes at run time does make this a bit better and easy to understand , but definitely huge chunk of code
    // order.get() gives you the raw Orders* from the unique_ptr.
    return out;
}
/***
 * Player Assignment Operator
 * Creates a deep copy of the Player object
 */
Player &Player::operator=(const Player &other)
{
    if (this == &other)
        return *this; // self-assignment check

    // Clean up existing resources
    delete name;
    for (Territory *territory : *defendCollection)
    {
        delete territory;
    }
    for (Territory *territory : *attackCollection)
    {
        delete territory;
    }
    delete defendCollection;
    delete attackCollection;
    delete cardCollection;
    delete orderCollection;

    // Deep copy of name
    name = new string(*other.name);

    // Deep copy of defendCollection
    defendCollection = new vector<Territory *>(*other.defendCollection);

    // Deep copy of attackCollection
    attackCollection = new vector<Territory *>(*other.attackCollection);

    // Deep copy of cardCollection
    cardCollection = new Hand(*other.cardCollection);

    // Deep copy of orderCollection
    orderCollection = new Orderlist();
    for (const auto &order : other.orderCollection->orderList)
    {
        Orders *newOrder = new Orders(*order);
        orderCollection->orderList.push_back(make_unique<Orders>(*newOrder));
    }

    return *this;
}

/***
 * toDefend()
 * Returns a list of territories that are to be defended
 * TODO Arbitrarily choose which territory to be defended
 */
vector<Territory *> *Player::toDefend()
{
    return defendCollection;
}

/***
 * toAttack()
 * Returns a list of territories that are to be attacked
 * TODO Arbitrarily choose which territory to be attacked
 */
vector<Territory *> *Player::toAttack()
{
    return attackCollection;
}

/***
 * issueOrder()
 * Creates an Order object and puts it in the player’s list of orders
 * TODO maybe replace move with an insert function
 */
void Player::issueOrder()
{
    bool finished = false;
    while (!finished)
    {
        finished = generateOrder();
    }
}

/***
 * addToDefend()
 * Adds a territory to the list of territories to be defended
 */
void Player::addToDefend(Territory *territory)
{
    if (territory != nullptr)
    {
        defendCollection->push_back(territory);
    }
}

/***
 * addToAttack()
 * Adds a territory to the list of territories to be attacked
 */
void Player::addToAttack(Territory *territory)
{
    if (territory != nullptr)
    {
        attackCollection->push_back(territory);
    }
}

/***
 * getOrderList()
 * Returns the player's order list
 */
Orderlist *Player::getOrderList()
{
    return orderCollection;
}

/***
 *  getHand()
 *  Returns the player's hand of cards
 */
Hand *Player::getHand()
{
    return this->cardCollection;
}

//--------Functions related to reinforcement armies pool(Ass2)-------//
void Player::setReinforcementPool(int arimes)
{
    this->reinforcementPool = arimes;
}

int Player::getReinforcementPool() const
{
    return this->reinforcementPool;
}

/***
 * This function will generate an order based on user input
 * Currently it serves as the main functionality of issueOrder()
 * It allows players to generate an invalid order
 */
bool Player::generateOrder()
{
    int orderChoice;
    string source, target , enemy;
    int numUnits;
    
    std::unique_ptr<Orders> order;

    cout << "========== Generating Order ==========" << endl; // Allows the player to choose which type of order to issue
    cout << "Please choose which order to issue:" << endl;
    cout << "1. Deploy" << endl;
    cout << "2. Advance" << endl;
    cout << "3. Bomb (Requires Bomb Card)" << endl;
    cout << "4. Airlift (Requires Airlift Card)" << endl;
    cout << "5. Negotiate (Requires Diplomacy Card)" << endl;
    cout << "6. Blockade (Requires Blockade Card)" << endl;
    cout << "7. Finish issuing orders\n"
         << endl;
    cout << *cardCollection << endl; // Display the player's cards
    cin >> orderChoice;              // Get the player's choice

    if (orderChoice == 7)
    {
        return true; // Exit if the player is finished issuing orders
    }

    cout << "\nEnter source territory: " << endl; // Get the source territory
    for (const Territory *territory : *defendCollection)
    { // Display territories to defend
        cout << territory->getName() << " " << endl;
    }
    cin >> source;

    cout << "\nEnter target territory: " << endl; // Get the target territory
    for (const Territory *territory : *attackCollection)
    { // Display territories to attack
        cout << territory->getName() << " " << endl;
    }
    cin >> target;

    cout << "\nEnter number of army units: " << endl; // Get the number of armies
    cin >> numUnits;

    cout <<"\n Enter the name of the enemy for negotiate order: " <<endl;
    cin >> enemy;


    switch (orderChoice)
    { // Based on the Player's choice, create an Order and send it to the OrderList
    case 1:
    {
        order = std::make_unique<DeployOrder>(numUnits, source, target);
        orderCollection->orderList.push_back(std::move(order));
        cout << "New Deploy Order created.\n"
             << endl;
        break;
    }
    case 2:
    {
        order = std::make_unique<Advance>(numUnits, source, target);
        orderCollection->orderList.push_back(std::move(order));
        cout << "New Advance Order created.\n"
             << endl;
        break;
    }
    case 3:
    {
        order = std::make_unique<Bomb>(numUnits, source, target);
        orderCollection->orderList.push_back(std::move(order));
        cout << "New Bomb Order created.\n"
             << endl;
        break;
    }
    case 4:
    {
        order = std::make_unique<Airlift>(numUnits, source, target);
        orderCollection->orderList.push_back(std::move(order));
        cout << "New Airlift Order created.\n"
             << endl;
        break;
    }
    case 5:
    {
        order = std::make_unique<Negotiate>(numUnits, source, target , enemy);
        orderCollection->orderList.push_back(std::move(order));
        cout << "New Negotiate Order created.\n"
             << endl;
        break;
    }
    case 6:
    {
        order = std::make_unique<Blockade>(numUnits, source, target);
        orderCollection->orderList.push_back(std::move(order));
        cout << "New Blockade Order created.\n"
             << endl;
        break;
    }
    default:
    { // If the player enters an invalid type , cancel the order issueing
        cout << "Invalid choice. Order not created.\n"
             << endl;
        break;
    }
    }
    return false;
}
