#include "PlayerStrategies.h"

#include <algorithm>
#include <cctype>

//even if i did not explcitly called the default constructor no problem in this case
//why exactly as the Parent class PlayerStrategy does not have any user defined constructors

// ========================================== Base Player Strategy ===========================
PlayerStrategy::PlayerStrategy(Player* p): player(p){
    player = p;
}







// =========================================== Human Player Strategy ===========================

HumanPlayerStrategy::HumanPlayerStrategy(Player* p): PlayerStrategy(p) {

};

void HumanPlayerStrategy::issueOrder() {
    cout << "Human Player Strategy: prompt user for commands." << endl;
    bool finished = false;
    player->setTentativePool(player->getReinforcementPool());                    // Initialize tentative pool at the start of issuing orders
    while (!finished)
    {
        cout << player->BANNER << endl;
        cout << player->getName() << " is playing their turn." << endl;
        cout << player->BANNER << endl;

        cout << "\n=========== Ally Territories ===========" << endl;
        player->printTerritoryList(player->toDefend()); // Update the defend collection
        cout << "\n=========== Enemy Territories ==========" << endl;
        player->printTerritoryList(player->toAttack()); // Update the attack collection

        cout << "\n" << player->BANNER << endl;

        toAttack(); // Update the attack collection

        finished = player->generateOrder();
    }
}

std::vector<Territory*>* HumanPlayerStrategy::toAttack() {
    // Human player decides via UI, return new list that engine can fill in
    player->getAttackCollection()->clear();                                  //IMPORTANT: Clear previous entries to avoid duplicates
    for (Territory * territory : * player->getDefendCollection())              // Loop through each territory the player owns and find adjacent enemy territories
    {
        player->getEnemyTerritories(territory);
    }

    return player->getAttackCollection();
}

std::vector<Territory*>* HumanPlayerStrategy::toDefend() {

    return player->getDefendCollection();
}


// =========================================== Aggressive Player Strategy =========================== 

AggressivePlayerStrategy::AggressivePlayerStrategy(Player* p): PlayerStrategy(p) {
    

}


void AggressivePlayerStrategy::issueOrder(){
    cout<<"Aggressive Player Strategy: Issuing aggressive orders. " <<endl;

    // Check for cheater player effect
    if (player->getDefendCollection()->size() == 0 ){
        cout << "ERROR 404: " + player->getName() + "'s territories has been corrupted!!" << endl;
        return;
    }

    std::vector<Territory*>* defendList = toDefend();
    if(defendList->empty()){
        cout << "Aggressive Player Strategy: No territories available to defend or attack." << endl;
        delete defendList;
        return;
    }
    Territory* strongestTerritory = (*defendList)[0];

    // =========================================== Deployment Phase ===========================================
    // Add all the new reinforcments to the territory with the highest number of armies

    // Create a Deploy order and add it to the order list
    std::unique_ptr<Orders> deployOrder;
    
    deployOrder = std::make_unique<DeployOrder>(player->getReinforcementPool(), strongestTerritory->getName(), strongestTerritory->getName()); // maybe change the source
    player->setLastAction("Deployed " + std::to_string(player->getReinforcementPool()) + " units to " + strongestTerritory->getName());
    player->notify(player);
    player->getOrderList()->orderList.push_back(std::move(deployOrder));
    cout << strongestTerritory->getName() << " has tentatively increased army units by " << player->getReinforcementPool() << endl;



    // =========================================== Order Phase ===========================================
    // Refresh attackable territories before issuing offensive orders
    int attackableTerritories = player->toAttack()->size(); //with this now bomb orders can be issued properly

    // If there are no attackable territories adjacent to the strongest territory, attempt to advance to an adjacent territory
    // This will however, skip the player's turn
    // if(attackableTerritories == 0){
        Territory* lastTerritoryVisited = strongestTerritory;
        Territory* currentTerritory = strongestTerritory;
        while(attackableTerritories == 0){

            // Hopefully this does not result in an infinite loop
            int numAdjacent = currentTerritory->getAdjacentTerritories()->size();
            int randomIndex = rand() % numAdjacent; // Select a random adjacent territory

            Territory* targetTerritory;

            if(numAdjacent == 1){
                targetTerritory = lastTerritoryVisited;
            } else {
                targetTerritory = currentTerritory->getAdjacentTerritories()->at(randomIndex);
                while(targetTerritory->getName() == lastTerritoryVisited->getName()){
                    randomIndex = rand() % numAdjacent;
                    targetTerritory = currentTerritory->getAdjacentTerritories()->at(randomIndex);
                }

            }

            std::unique_ptr<Orders> order = std::make_unique<Advance>(currentTerritory->getArmies(), currentTerritory->getName(), targetTerritory->getName());
            player->setLastAction("Issued Advance order: " + std::to_string(currentTerritory->getArmies()) + " units from " + lastTerritoryVisited->getName()+ " to " + targetTerritory->getName());
            player->notify(player);
            player->getOrderList()->orderList.push_back(std::move(order));
            cout << "New Advance Order created." << endl;


            lastTerritoryVisited = currentTerritory;
            currentTerritory = targetTerritory;
            player->getAttackCollection()->clear();  // Clear previous entries to avoid duplicates
            player->getEnemyTerritories(currentTerritory); //get new attackable territories from the currently advanced territory
            attackableTerritories =  player->getAttackCollection()->size();//update the number of attackable territories after the advance
            
                
        }

        strongestTerritory = currentTerritory;

        int randomIndex = rand() % attackableTerritories; // Select a random Enemy territory

        Territory* targetTerritory = player->getAttackCollection()->at(randomIndex);

        // Attempt to bomb every territory (the validate function will prevent invalid bombs)
        std::unique_ptr<Orders> bombOrder = std::make_unique<Bomb>(0, strongestTerritory->getName(), targetTerritory->getName());
        player->setLastAction("Issued Bomb order: " + player->getName() + " bombed " + targetTerritory->getName());
        player->notify(player);
        player->getOrderList()->orderList.push_back(std::move(bombOrder));
        cout << "New Bomb Order created." << endl;

        // Split the army equally among all attackable territories of the player's Strongest Territory
        // The Floor will ensure that all the deployed armies will be valid
        std::unique_ptr<Orders> order = std::make_unique<Advance>(strongestTerritory->getArmies(), strongestTerritory->getName(), targetTerritory->getName());
        player->setLastAction("Issued Advance order: " + std::to_string(strongestTerritory->getArmies()) + " units from " + strongestTerritory->getName()+ " to " + targetTerritory->getName());
        player->notify(player);
        player->getOrderList()->orderList.push_back(std::move(order));
        cout << "New Advance Order created." << endl;
        

    delete defendList;
}


/***
 * This function will return a list of enemy territories 
 */
std::vector<Territory*>* AggressivePlayerStrategy::toAttack() {
    // Would normally prioritize strongest territories, placeholder for now
    player->getAttackCollection()->clear();   
    std::unique_ptr<std::vector<Territory*>> defendList(toDefend());

    //IMPORTANT: Clear previous entries to avoid duplicates

    if(!defendList->empty()){
        player->getEnemyTerritories(defendList->at(0));
    }

    return player->getAttackCollection();
    // return new vector<Territory*>();
}

// Make sure to delete defendList after use to avoid memory leaks (in issueOrder)
std::vector<Territory*>* AggressivePlayerStrategy::toDefend() {

    std::vector<Territory*>* defendList = new std::vector<Territory*>();

    if(player->getDefendCollection()->size() == 0){
        return defendList;
    }

    for (Territory* terr : *(player->getDefendCollection())) {
        if(terr->getArmies() > 0 ){         // add all the territories with armies to defend list
            defendList->push_back(terr);
        }
    }

    // If no territories have armies, at least return one to avoid empty list
    
    // Assuming that a player always has at least one territory (or else they are out of the game)
    if(defendList->empty()) {
        Territory* terr = player->getDefendCollection()->at(0);
        defendList->push_back(terr); // Return empty list if no territories to defend
    } else {
        std::sort(defendList->begin(), defendList->end(), [](Territory* a, Territory* b) {
            return a->getArmies() > b->getArmies();             // Sort in descending order of armies, ensuring strongest territories come first
        });
    }

    return defendList;
}


// =========================================== Benevolent Player Strategy ===========================

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* p): PlayerStrategy(p) {
}

void BenevolentPlayerStrategy::issueOrder() {
    cout << "Benevolent Player Strategy: reinforcing weak territories." << endl;

    // Check for cheater player effect
    if (player->getDefendCollection()->size() == 0 ){
        cout << "ERROR 404: " + player->getName() + "'s territories has been corrupted!!" << endl;
        return;
    }

    // =========================================== Deployment Phase ===========================================
    // The player will spread out reinforcements equally among their weakest territories
    std::vector<Territory*>* defendList = toDefend();
    
    Territory* weakestTerritory = (*defendList)[0];
    int numTerritories = defendList->size();
    int tentativeReinforcements = player->getReinforcementPool();
    int armiesPerTerritory = floor(player->getReinforcementPool()/numTerritories);

    std::unique_ptr<Orders> deployOrder;

    //Attempt to deploy an equal amount of reinforcements to each territory
    // This is mostly useful at the start of the game or when the player has a low amount of territories
    //NOTE: Keep a look at it out 
    for (int i = 0; i < numTerritories; i++){   

        if(tentativeReinforcements <= 0 || armiesPerTerritory <= 0){   // If there are no more reinforcement left or the armies per territory is 0, break
            break;
        }

        deployOrder = std::make_unique<DeployOrder>(armiesPerTerritory, (*defendList)[i]->getName(), (*defendList)[i]->getName());
        player->setLastAction("Deployed " + std::to_string(armiesPerTerritory) + " units to " + (*defendList)[i]->getName());
        player->notify(player);
        player->getOrderList()->orderList.push_back(std::move(deployOrder));
        cout << (*defendList)[i]->getName() << " has tentatively increased army units by " << armiesPerTerritory << endl;
        tentativeReinforcements -= armiesPerTerritory;
    }

    // If there are leftover reinforcements, add them to the weakest territory
    if(tentativeReinforcements > 0){ 
        deployOrder = std::make_unique<DeployOrder>(tentativeReinforcements, weakestTerritory->getName(), weakestTerritory->getName()); 
        player->setLastAction("Deployed " + std::to_string(tentativeReinforcements) + " units to " + weakestTerritory->getName());
        player->notify(player);
        player->getOrderList()->orderList.push_back(std::move(deployOrder));
        cout << weakestTerritory->getName() << " has tentatively increased army units by " << tentativeReinforcements << endl;
    }

    // ============================================ Order Phase ===========================================

    // Attempt to negotiate with enemies adjacent to weakest territory
    for(Territory* terr: *(toAttack())){

        std::unique_ptr<Orders> order = std::make_unique<Negotiate>(0, weakestTerritory->getName(), terr->getName(), terr->getOwner()->getName());
        player->setLastAction("Issued Negotiate order with " + terr->getOwner()->getName());
        player->notify(player);
        player->getOrderList()->orderList.push_back(std::move(order));
        cout << "New Negotiate Order created." << endl;
    }


    // Advances armies from adjacent ally territories to weakest territory
    // Currently sending 1/3 of armies from each adjacent territory
    if(numTerritories > 1){
        // Attempt to airlift armies from the strongest territory to the weakest territory
        Territory* strongestTerritory = (*defendList)[numTerritories - 1];
        std::unique_ptr<Orders> airliftOrder = std::make_unique<Airlift>(floor(strongestTerritory->getArmies()/3), strongestTerritory->getName(), weakestTerritory->getName());
        player->setLastAction("Issued Airlift order: " + std::to_string(floor(strongestTerritory->getArmies()/3)) + " units from " + strongestTerritory->getName()+ " to " + weakestTerritory->getName());
        player->notify(player);
        player->getOrderList()->orderList.push_back(std::move(airliftOrder));
        cout << "New Airlift Order created." << endl;



        // Advance armies from allied adjacent territories to weakest territory
        for(Territory* terr: *(weakestTerritory->getAdjacentTerritories()) ){
            // Check if the adjacent territory is owned by an enemy player
            if(terr->getOwner() == player){
                int sendArmies = floor(terr->getArmies()/3); // Send a third of the armies to the weakest territory

                std::unique_ptr<Orders> order = std::make_unique<Advance>(sendArmies, terr->getName(), weakestTerritory->getName());
                player->setLastAction("Issued Advance order: " + std::to_string(terr->getArmies()) + " units from " + terr->getName()+ " to " + weakestTerritory->getName());
                player->notify(player);
                player->getOrderList()->orderList.push_back(std::move(order));
                cout << "New Advance Order created." << endl;
            }
        }

    }

    // Use a defensive Airlift card if available: move armies from strongest to weakest ally
    auto hasAirlift = std::find_if(player->getHand()->hand->begin(), player->getHand()->hand->end(), [](Card* c){
        std::string type = *c->cardType;
        std::transform(type.begin(), type.end(), type.begin(), ::tolower);
        return type == "airlift";
    });

    if (hasAirlift != player->getHand()->hand->end() && numTerritories > 1) {
        Territory* strongestTerritory = (*defendList)[numTerritories - 1];
        if (strongestTerritory != weakestTerritory && strongestTerritory->getArmies() > 0) {
            int sendArmies = std::max(1, strongestTerritory->getArmies() / 2);
            std::unique_ptr<Orders> airliftOrder = std::make_unique<Airlift>(sendArmies, strongestTerritory->getName(), weakestTerritory->getName());
            player->setLastAction("Issued defensive Airlift: " + std::to_string(sendArmies) + " units from " + strongestTerritory->getName() + " to " + weakestTerritory->getName());
            player->notify(player);
            player->getOrderList()->orderList.push_back(std::move(airliftOrder));
            cout << "Airlift card used defensively: moved " << sendArmies << " armies to " << weakestTerritory->getName() << endl;
        }
    }

    // Benevolent players will not issue harmful card-based orders (e.g., Bomb); explicitly ignore bomb cards
    // to reinforce the “never harms anyone” rule.
    
    delete defendList;
    defendList = nullptr;
}

std::vector<Territory*>* BenevolentPlayerStrategy::toAttack() {
        
    // Clear
    player->getAttackCollection()->clear();

    // Get enemy territories adjacent to weakest territory
    // This will be used to get players to negotiate with
    // Check if the toDefend is empty or not
    if(player->toDefend()->size() > 0){
        player->getEnemyTerritories((*toDefend())[0]);
    }

    return player->getAttackCollection();
}

std::vector<Territory*>* BenevolentPlayerStrategy::toDefend() {
    std::vector<Territory*>* defendList = new std::vector<Territory*>();
    if(player->getDefendCollection()->size() == 0){
        return defendList;
    }

    for (Territory* terr : *(player->getDefendCollection())) {
        defendList->push_back(terr);   
    }

    std::sort(defendList->begin(), defendList->end(), [](Territory* a, Territory* b) {
        return a->getArmies() < b->getArmies();             // Sort in ascending order of armies, ensuring weakest territories come first
    });
    return defendList;
}

// =========================================== Cheater Player Strategy ===========================
CheaterPlayerStrategy::CheaterPlayerStrategy(Player * p):PlayerStrategy(p){

}

//i did not comment the demo version i talked about you can overwrite it this version works but if you want to work on your own implementation change it as you wish
void CheaterPlayerStrategy::issueOrder() {

    // Other Cheaters may corrupt each other 
    if (player->getDefendCollection()->size() == 0 ){
        cout << "ERROR 404: " + player->getName() + "'s territories has been corrupted!!" << endl;
        return;
    }
    
    cout << "Cheater Player Strategy: automatically conquering adjacent territories." << endl;
    std::vector<Territory *> * toTakeOver = toAttack(); // attackCollection is owned by player; do not delete
    for (Territory * target : *toTakeOver)
    {
        Player* previousOwner = target->getOwner();
        if (previousOwner != nullptr && previousOwner != player) {
            previousOwner->removeFromDefend(target); // clean up previous owner's list
        }

        target->setOwner(this->player);

        // Track new ownership in this player's defend collection (avoid duplicates) //safety precaution not mandatory 
        if (std::find(player->getDefendCollection()->begin(), player->getDefendCollection()->end(), target) == player->getDefendCollection()->end()) {
            player->addToDefend(target);

            //NOTE:attackCollection would leave stale entries.
            //Clearing it just resets the “targets to attack” list the next call to toAttack() will repopulate it based on current ownership. 
            //It doesn’t remove anything from defendCollection, so owned territories stay tracked.
        }

        player->setLastAction("Captured " + target->getName());
        player->notify(player);
    }

    player->getAttackCollection()->clear(); // reset transient attack list
}

std::vector<Territory*>* CheaterPlayerStrategy::toAttack() {
    player->getAttackCollection()->clear();
    for (Territory * territory : * player->getDefendCollection())
    {
        player->getEnemyTerritories(territory);
    }

    return player->getAttackCollection();
}

std::vector<Territory*>* CheaterPlayerStrategy::toDefend() {
    return player->getDefendCollection();
}

// =========================================== Neutral Player Strategy ===========================
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* p): PlayerStrategy(p) {

}

void NeutralPlayerStrategy::issueOrder(){
  cout<<"Neutral Player Strategy: No orders can be issued. " <<endl;

}


vector<Territory*>* NeutralPlayerStrategy::toAttack(){
  //return an empty vector as a neutral player does not attack
  return new vector<Territory*>();
}

vector<Territory*>* NeutralPlayerStrategy::toDefend(){
  //returns an empty vector as a neutral player has no territory to defend 
  return player->getDefendCollection();
}


// Add other derived destructors if needed
PlayerStrategy::~PlayerStrategy(){}
NeutralPlayerStrategy::~NeutralPlayerStrategy() {}
AggressivePlayerStrategy::~AggressivePlayerStrategy() {}
HumanPlayerStrategy::~HumanPlayerStrategy() {}
BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {}
CheaterPlayerStrategy::~CheaterPlayerStrategy() {}
