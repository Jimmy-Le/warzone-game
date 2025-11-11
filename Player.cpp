#include "Player.h"
#include "LoggingObserver.h"

/***
 * Player Constructor,
 * Initializes the set of territories, cards, and orderlist of a Player
 */
Player::Player()
{
    this->name = new string("John Doe");
    // Territory* t = new Territory("Mexico");
    this->defendCollection = new vector<Territory *>();
    // this->defendCollection->push_back(t);
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

    // // Free each Territory pointer in the territories to defend collection
    // for (Territory *territory : *defendCollection)
    // {
    //     delete territory;
    // }

    // // Free each Territory pointer in the territories to attack collection
    // for (Territory *territory : *attackCollection)
    // {
    //     delete territory;
    // }

    defendCollection->clear();
    attackCollection->clear();
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
 * I am interpreting this as returning all territories adjacent to the player's territories that are owned by other players
 */
vector<Territory *> *Player::toAttack()
{
    
    
    attackCollection->clear(); // Clear previous entries
    for (Territory *territory : *defendCollection)
    {
        getEnemyTerritories(territory);
    }

    return attackCollection;

}

/***
 * This helper function helps to find the adjacent territories and add it to the attackCollection
 * Make sure to clear the attackCollection before calling this function to ensure that it is updated properly
 */
void Player::getEnemyTerritories(Territory *source){
    for (Territory *adjacent : *(source->getAdjacentTerritories()))
    {
        if (adjacent->getOwner() != this)
        {   
            if(std::find_if(attackCollection->begin(), attackCollection->end(), [&](Territory* territory){return territory->getName() == adjacent->getName();}) == attackCollection->end()){ // Avoid duplicates
                attackCollection->push_back(adjacent);
            }
        }
    }
}

/***
 * issueOrder()
 * Creates an Order object and puts it in the player’s list of orders
 * TODO maybe replace move with an insert function
 */
void Player::issueOrder()
{   

    bool finished = false;
    tentativePool = reinforcementPool;                          // Initialize tentative pool at the start of issuing orders
    while (!finished)
    {
        cout << BANNER << endl;
        cout << *name << "'s Territories" << endl;
        cout << BANNER << endl;

        printTerritoryList(defendCollection);

        cout << BANNER << endl;
        cout << "Territories to attack" << endl;
        cout << BANNER << endl;

        toAttack(); // Update the attack collection
        printTerritoryList(attackCollection);



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

    Territory* sourceTerritory;

    // Validation for source territory can be added here

    while(tentativePool > 0){
        cout << "Remaining Reinforcement Pool: " << tentativePool << endl;
        cout << "\nPlease choose a territory: " << endl; // Get the starting territory
        cin >> source;

        // sourceTerritory = findTerritory(defendCollection, source);
        deployReinforcments(source);
    
    } 

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


    switch (orderChoice)
    { // Based on the Player's choice, create an Order and send it to the OrderList
    case 1: // Deploy Order (Should always be 0 tentativePool, but we allow the players to issue it anyway)
    {
        cout << "Remaining Reinforcement Pool: " << tentativePool << endl;
        cout << "\nPlease choose a territory: " << endl; // Get the starting territory
        cin >> source;
        deployReinforcments(source); // Deploy orders are handled separately
        break;
    }
    case 2: // Advance Order
    {
        cout << "Please enter the source territory you would like your army to advance from: " << endl; // Get the source territory
        cin >> source;

        sourceTerritory = findTerritory(defendCollection, source);
        if(sourceTerritory != nullptr){
            cout << BANNER << endl;
            printTerritoryList(sourceTerritory->getAdjacentTerritories());
            cout << BANNER << endl;
        }
        
        cout << "Please enter the target territory you would like your army to advance to: " << endl;   // Get the target territory
        cin >> target;
        cout << "Please enter the number of army units to advance: " << endl;                           // Get the number of army units
        cin >> numUnits;    

        order = std::make_unique<Advance>(numUnits, source, target);
        setLastAction("Issued Advance order: " + std::to_string(numUnits) + " units from " + source + " to " + target);
        notify(this);
        orderCollection->orderList.push_back(std::move(order));
        cout << "New Advance Order created.\n" << endl;
        break;
    }
    case 3: // Bomb Order
    {

        cout << "Please enter the source territory you would like to bomb from: " << endl; // Get the source territory
        cin >> source;

        sourceTerritory = findTerritory(defendCollection, source);
        if(sourceTerritory != nullptr){
            cout << BANNER << endl;
            printTerritoryList(sourceTerritory->getAdjacentTerritories());
            cout << BANNER << endl;
        }
        
        cout << "Please enter the target territory you would like to bomb: " << endl;      // Get the target territory
        cin >> target;


        order = std::make_unique<Bomb>(0, source, target);
        setLastAction("Issued Bomb order: " + source + " bombed " + target);
        notify(this);
        orderCollection->orderList.push_back(std::move(order));
        cout << "New Bomb Order created.\n" << endl;
        break;
    }
    case 4: // Airlift Order
    {

        cout << BANNER << endl;
        printTerritoryList(defendCollection);
        cout << BANNER << endl;

        cout << "Please enter the source territory you would like your army to airlift from: " << endl; // Get the source territory
        cin >> source; 
        cout << "Please enter the target territory you would like your army to airlift to: " << endl;   // Get the target territory
        cin >> target;
        cout << "Please enter the number of army units to airlift: " << endl;                         // Get the number of army units
        cin >> numUnits;

        order = std::make_unique<Airlift>(numUnits, source, target);
        setLastAction("Issued Airlift order: " + std::to_string(numUnits) + " units from " + source + " to " + target);
        notify(this);
        orderCollection->orderList.push_back(std::move(order));
        cout << "New Airlift Order created.\n" << endl;
        break;
    }
    case 5: // Negotiate Order
    {
        cout << "Please enter the name of the player you would like to negotiate with: " << endl; // Get the target player
        cin >> enemy;
        order = std::make_unique<Negotiate>(numUnits, source, target , enemy);
        setLastAction("Issued Negotiate order with player " + enemy);
        notify(this);
        orderCollection->orderList.push_back(std::move(order));
        cout << "New Negotiate Order created.\n" << endl;
        break;
    }
    case 6:
    {
        cout << BANNER << endl;
        printTerritoryList(defendCollection);
        cout << BANNER << endl;
        cout << "Please enter the territory you would like form a blockade: " << endl; // Get the source territory
        cin >> source;
        order = std::make_unique<Blockade>(0, source, source);          // Might have to change the target later
        setLastAction("Issued Blockade order on territory " + source);
        notify(this);
        orderCollection->orderList.push_back(std::move(order));
        cout << "New Blockade Order created.\n" << endl;
        break;
    }
    default:
    { // If the player enters an invalid type , cancel the order issueing
        cout << "Invalid choice. Order not created.\n" << endl;
        setLastAction("Attempted to issue invalid order.");
        notify(this);
        break;
    }
    }
    
    sourceTerritory = nullptr;
    return false;
}

/***
 * This function will handle the deployment of reinforcements to allied territories
 */
void Player::deployReinforcments( string source)
{

    int deployUnits;
    cout << "Please enter the number of armies to deploy (Available: " << tentativePool << "): ";

    cin >> deployUnits;

    // Validate the number of armies to deploy
    while (deployUnits < 0 || deployUnits > tentativePool)
    {
        cout << "Invalid number of armies. Please enter a value between 0 and " << tentativePool << ": ";
        cin >> deployUnits;
    }

    // Create a Deploy order and add it to the order list
    std::unique_ptr<Orders> deployOrder = std::make_unique<DeployOrder>(deployUnits, source, source); // maybe change the source
    setLastAction("Deployed " + std::to_string(deployUnits) + " units to " + source);
    notify(this);
    orderCollection->orderList.push_back(std::move(deployOrder));
    cout << source << " has tentatively increased army units by " << deployUnits << endl;

    // Update the reinforcement pool
    tentativePool -= deployUnits;
    // removeFromReinforcementPool(deployUnits);
    // source->setArmies(source->getArmies() + deployUnits); // Update the armies in the territory (Maybe have a proper function later) or have it in the execute section
}


/***
 * This function will find a territory by its name
 */
Territory *Player::findTerritory(std::vector<Territory*> *territoryList, string source){
    for (Territory *territory : *territoryList){
        if (territory->getName() == source){
            return territory;
        }
    }
    return nullptr; // Territory not found
}

/***
 * This function will add armies to the reinforcement pool
 */
void Player::addToReinforcementPool(int armies){
    reinforcementPool += armies;
}

/***
 * This function will remove armies from the reinforcement pool
 */
void Player::removeFromReinforcementPool(int armies){
    if (armies <= reinforcementPool){
        reinforcementPool -= armies;
    } else {
        reinforcementPool = 0;
    }
}

void Player::printTerritoryList(std::vector<Territory*>* territoryList){

    for (Territory *territory : *territoryList){
        cout << "- "<< std::setw(20) << std::left << (territory->getOwner()->getName() + ": ") << territory->getName() << " = "  << territory->getArmies() << endl;
    }
}

void Player::removeFromDefend(Territory* territory){
    auto it = std::remove(defendCollection->begin(), defendCollection->end(), territory);
    if (it != defendCollection->end()) {
        defendCollection->erase(it, defendCollection->end());
    }
}

void Player::removeFromAttack(Territory* territory){
    auto it = std::remove(attackCollection->begin(), attackCollection->end(), territory);
    if (it != attackCollection->end()) {
        attackCollection->erase(it, attackCollection->end());
    }
}

void Player::setLastAction(const std::string &action) {
    lastAction = action;
}

std::string Player::stringToLog() {
    std::ostringstream logStream;
    logStream << "Player: " << *name << " | Action: " << lastAction;
    return logStream.str();
}
