#include "PlayerStrategies.h"

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
}

std::vector<Territory*>* HumanPlayerStrategy::toAttack() {
    // Human player decides via UI, return new list that engine can fill in
    return new vector<Territory*>();
}

std::vector<Territory*>* HumanPlayerStrategy::toDefend() {
    return new vector<Territory*>();
}


// =========================================== Aggressive Player Strategy =========================== 

AggressivePlayerStrategy::AggressivePlayerStrategy(Player* p): PlayerStrategy(p) {
    

}


void AggressivePlayerStrategy::issueOrder(){
    cout<<"Aggressive Player Strategy: Issuing aggressive orders. " <<endl;


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
    // Advance all armies from weaker territories to strongest territory
    // We assume that the bot will deploy all its reinforcments to 1 territory and conquer neighboring territories, allowing for them to easily advance back to the main colony
    if(defendList->size() > 1){
        for(int i = 1; i < defendList->size();i++){
            std::unique_ptr<Orders> order = std::make_unique<Advance>(strongestTerritory->getArmies(), (*defendList)[i]->getName(), strongestTerritory->getName());
            player->setLastAction("Issued Advance order: " + std::to_string((*defendList)[i]->getArmies()) + " units from " + (*defendList)[i]->getName()+ " to " + strongestTerritory->getName());
            player->notify(player);
            player->getOrderList()->orderList.push_back(std::move(order));
            cout << "New Advance Order created." << endl;
        }
    }

    int attackableTerritories = player->getAttackCollection()->size();

    // If there are no attackable territories adjacent to the strongest territory, attempt to advance to an adjacent territory
    // This will however, skip the player's turn
    if(attackableTerritories == 0){
        // Hopefully this does not result in an infinite loop
        Territory* targetTerritory = strongestTerritory->getAdjacentTerritories()->at(0);

        std::unique_ptr<Orders> order = std::make_unique<Advance>(strongestTerritory->getArmies(), strongestTerritory->getName(), targetTerritory->getName());
        player->setLastAction("Issued Advance order: " + std::to_string(strongestTerritory->getArmies()) + " units from " + strongestTerritory->getName()+ " to " + targetTerritory->getName());
        player->notify(player);
        player->getOrderList()->orderList.push_back(std::move(order));
        cout << "New Advance Order created." << endl;


    } else { // There are attackable territories adjacent to the strongest territory
        for(int i = 0; i < attackableTerritories; i++){                                     // Loop through all attackable territories and attempt to bomb and advance on them by splitting the armies equally
            Territory* targetTerritory = player->getAttackCollection()->at(i);

            // Attempt to bomb every territory (the validate function will prevent invalid bombs)
            std::unique_ptr<Orders> bombOrder = std::make_unique<Bomb>(0, strongestTerritory->getName(), targetTerritory->getName());
            player->setLastAction("Issued Bomb order: " + player->getName() + " bombed " + targetTerritory->getName());
            player->notify(player);
            player->getOrderList()->orderList.push_back(std::move(bombOrder));
            cout << "New Bomb Order created." << endl;

            // Split the army equally among all attackable territories of the player's Strongest Territory
            // The Floor will ensure that all the deployed armies will be valid
            std::unique_ptr<Orders> order = std::make_unique<Advance>(floor(strongestTerritory->getArmies()/attackableTerritories), strongestTerritory->getName(), targetTerritory->getName());
            player->setLastAction("Issued Advance order: " + std::to_string(floor(strongestTerritory->getArmies()/attackableTerritories)) + " units from " + strongestTerritory->getName()+ " to " + targetTerritory->getName());
            player->notify(player);
            player->getOrderList()->orderList.push_back(std::move(order));
            cout << "New Advance Order created." << endl;
        }
    }
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
    
}

std::vector<Territory*>* BenevolentPlayerStrategy::toAttack() {
        
    // Clear
    player->getAttackCollection()->clear();

    // Get enemy territories adjacent to weakest territory
    // This will be used to get players to negotiate with
    player->getEnemyTerritories((*toDefend())[0]);

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

void CheaterPlayerStrategy::issueOrder() {
    cout << "Cheater Player Strategy: automatically conquering adjacent territories." << endl;
}

std::vector<Territory*>* CheaterPlayerStrategy::toAttack() {
    return new vector<Territory*>();
}

std::vector<Territory*>* CheaterPlayerStrategy::toDefend() {
    return new vector<Territory*>();
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
  return new vector<Territory*>();
}


// Add other derived destructors if needed
PlayerStrategy::~PlayerStrategy(){}
NeutralPlayerStrategy::~NeutralPlayerStrategy() {}
AggressivePlayerStrategy::~AggressivePlayerStrategy() {}
HumanPlayerStrategy::~HumanPlayerStrategy() {}
BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {}
CheaterPlayerStrategy::~CheaterPlayerStrategy() {}
