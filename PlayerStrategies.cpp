#include "PlayerStrategies.h"

//even if i did not explcitly called the default constructor no problem in this case
//why exactly as the Parent class PlayerStrategy does not have any user defined constructors

HumanPlayerStrategy::HumanPlayerStrategy() = default;

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

void AggressivePlayerStrategy::issueOrder(){
  cout<<"Aggressive Player Strategy: Issuing aggressive orders. " <<endl;
}

std::vector<Territory*>* AggressivePlayerStrategy::toAttack() {
    // Would normally prioritize strongest territories, placeholder for now
    return new vector<Territory*>();
}

std::vector<Territory*>* AggressivePlayerStrategy::toDefend() {
    return new vector<Territory*>();
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy() = default;

void BenevolentPlayerStrategy::issueOrder() {
    cout << "Benevolent Player Strategy: reinforcing weak territories." << endl;
}

std::vector<Territory*>* BenevolentPlayerStrategy::toAttack() {
    // Benevolent never attacks
    return new vector<Territory*>();
}

std::vector<Territory*>* BenevolentPlayerStrategy::toDefend() {
    return new vector<Territory*>();
}

CheaterPlayerStrategy::CheaterPlayerStrategy() = default;

void CheaterPlayerStrategy::issueOrder() {
    cout << "Cheater Player Strategy: automatically conquering adjacent territories." << endl;
}

std::vector<Territory*>* CheaterPlayerStrategy::toAttack() {
    return new vector<Territory*>();
}

std::vector<Territory*>* CheaterPlayerStrategy::toDefend() {
    return new vector<Territory*>();
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
