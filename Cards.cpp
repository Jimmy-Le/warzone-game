//
// Created by Keishaun on 2025-09-13.
//

#include "Cards.h"

#include <iostream>
#include <random>
#include <vector>
#include <string>

using namespace std;

/**
 * These are the implementations of the functions which concern the Hand class
 */
Hand::Hand() : hand(make_shared<vector<Card*>>()) {}                     // Default constructor initializes an empty vector
Hand::Hand(const Hand& other) {                                         // A regular deep copy constructor
    hand = make_shared<vector<Card*>>(*other.hand);
}
Hand& Hand::operator=(const Hand& other) {                              // Assignment operator overloading for the Hand class
    if (this == &other) return * this;
    hand = make_shared<vector<Card*>>(*other.hand);
    return * this;
}
Hand::~Hand() = default;                                                                // Hand uses the default deconstructor
ostream& operator<<(ostream& os, const Hand& h) {                                       // Stream operator overloading for the Hand class
    if (h.hand->empty()) {                                                              // Checks if the player's Hand is empty
        os << "The player's Hand is empty.\n" << endl;
        return os;
    }
    os << "The player's Hand contains the following " << h.hand->size() << " Cards [";  // Gives both the amount and the types of Cards in the Hand
    for (size_t i = 0; i < h.hand->size(); i++) {
        os << *h.hand->at(i)->cardType;
        if (i != h.hand->size() - 1) os << ", "; 
    }
    os << "].\n" << endl;
    return os;
}


/**
 * These are the implementations of the functions which concern the Card class
 */
Card::Card() : cardType(std::make_shared<std::string>("")) {}                                       // Default constructor leaves the Card type blank
Card::Card(std::string type) : cardType(std::make_shared<std::string>(type)) {}                     // Parameterized constructor defines a Card type
Card::Card(const Card& other) : cardType(std::make_shared<std::string>(*other.cardType)) {}         // A regular deep copy constructor
Card& Card::operator=(const Card& other) {                                                          // Assignment operator overloading for the Card class         
    if (this == &other) return * this; 
    cardType = std::make_shared<std::string>(*other.cardType);
    return * this;
}
void Card::play(Hand * specificHand,Deck * specificDeck, Player* player) {                           // This function plays a Card from a specified Hand and then returns it to a specified Deck                   
    int usedCard = findIndexOfCard(specificHand->hand, this->cardType);                             // Finds and save the index of the played Card
    Orderlist* playerOrders = player->getOrderList();

    //FIXME: Time to write the implementation for actual returning the card to the deck.
    // The following if/else section is to find the Card type and continue depending on which
    // We are currently removing the functionality of adding to the player's OrderList as we will implement that in the issueOrders
    if ((* this->cardType) == "bomb") {
        // playerOrders->orderList.push_back(make_unique<Bomb>(Bomb(0, "", "")));
        cout << "Player used a bomb card. The card has been returned to the deck.\n" << endl;
    }
    else if ((* this->cardType) == "reinforcement") {
        // playerOrders->orderList.push_back(make_unique<DeployOrder>(DeployOrder(0, "", "")));
        cout << "Player used a reinforcement card. The card has been returned to the deck.\n" << endl;
    }
    else if ((* this->cardType) == "blockade") {
        // playerOrders->orderList.push_back(make_unique<Blockade>(Blockade(0, "", "")));
        cout << "Player used a blockade card. The card has been returned to the deck.\n" << endl;
    }
    else if ((* this->cardType) == "airlift") {
        // playerOrders->orderList.push_back(make_unique<Airlift>(Airlift(0, "", "")));
        cout << "Player used a airlift card. The card has been returned to the deck.\n" << endl;
    }
    else if ((* this->cardType) == "diplomacy") {
        // playerOrders->orderList.push_back(make_unique<Negotiate>(Negotiate(0, "", "" , nullptr)));
        cout << "Player used a diplomacy card. The card has been returned to the deck.\n" << endl;
    }
    specificDeck->deck->push_back(specificHand->hand->at(usedCard));                                // This adds the Card back to the Deck
    specificHand->hand->erase(specificHand->hand->begin() + usedCard);                              // This removes the Card from the Hand
    (* specificDeck->deckSize)++;                                                                   // This increments the Deck size
}
Card::~Card() = default;                                                                            // Card uses the default deconstructor                         
ostream& operator<<(ostream& os, const Card& c) {                                                   // Card stream operator overload gives the Card type
    os << "This Card is of the following type: " << *c.cardType << ".\n" << endl;                              
    return os;
}

/**
 * These are the implementations of the functions which concern the Deck class
 */
Deck::Deck() : deck(make_shared<vector<Card*>>()) {                                              // The Deck default constructor creates the match Deck 
    deckSize = make_shared<int>(0);                                                             // Initializing the Deck size to zero 
    for (int i = 0; i < 10; i++) {                                                              // This is to make sure the Deck always has the same number of each Card type (Modify "i < 10 " to change initial Deck size) 
        this->deck->push_back(new Card("bomb"));
        // this->deck->push_back(new Card("reinforcement"));
        this->deck->push_back(new Card("blockade"));
        this->deck->push_back(new Card("airlift"));
        this->deck->push_back(new Card("diplomacy"));
        (* this->deckSize) += 4;                                                                // Increment Deck size by the amount of Cards added  
    }
}
Deck::Deck(const Deck& other) : deck(std::make_shared<std::vector<Card*>>(*other.deck)),         
deckSize(std::make_shared<int>(*other.deckSize)) {}                                             // A regular deep copy constructor                    
Deck& Deck::operator=(const Deck& other) {                                                      // Assignment operator overloading for the Deck class
    if (this == &other) return * this;
    deck = make_shared<vector<Card*>>(*other.deck);
    deckSize = make_shared<int>(*other.deckSize);
    return * this;
}
void Deck::draw(Hand * specificHand) {
    if ((* this->deckSize) == 0) {cout << "The deck is empty.\n" << endl; return;}              // Checks if the Deck is empty
    // The following Lines are to select a Card from the Deck as randomly as possible
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, (* deckSize) - 1);
    int cardPicked = dis(gen);                                                                  // Save the index of the randomly selected Card to a variable
    specificHand->hand->push_back(deck->at(cardPicked));                                        // Place the selected Card within a player's Hand
    deck->erase(deck->begin() + cardPicked);                                                    // Remove the Card from the Deck    
    (* deckSize)--;                                                                             // Decrement the Deck's Card count                        
}
Deck::~Deck() = default;                                                                        // Deck uses the default deconstructor   
ostream& operator<<(ostream& os, const Deck& d) {                                                           // Deck stream operator overloading 
    if ((* d.deckSize) == 0) {                                                                              // Checks if the Deck is empty
        os << "The Deck is empty.\n" << endl;
        return os;
    }
    os << "The Deck contains " << *d.deckSize << " Cards. There are ";                                      // Gives the number of Cards remmaining
    int bombCount = 0, reinforcementCount = 0, blockadeCount = 0, airliftCount = 0, diplomacyCount = 0;
    for (auto & i : *d.deck) {                                                                              // Grives the amount of each type of Card                        
        if (*(i->cardType) == "bomb") bombCount++;
        else if (*(i->cardType) == "reinforcement") reinforcementCount++;
        else if (*(i->cardType) == "blockade") blockadeCount++;
        else if (*(i->cardType) == "airlift") airliftCount++;
        else if (*(i->cardType) == "diplomacy") diplomacyCount++;
    }
    os << "" << bombCount << " bomb Cards, " << reinforcementCount << " reinforcement Cards, "
       << blockadeCount << " blockade Cards, " << airliftCount << " airlift Cards, and " 
       << diplomacyCount << " diplomacy Cards still within the Deck. \n" << endl;
    return os;
}

/**
 * This is the implementation of the helper function
 * @param TV Is the specified vector to search for the Card in
 * @param CT Is the specified Card type the function is looking for 
 * @return The index of the Card matching the searched Card type
 */
int findIndexOfCard(std::shared_ptr<vector<Card*>> &TV, std::shared_ptr<std::string> CT) {
    for (int i = 0; i < TV->size(); i++) {
        if (*(TV->at(i)->cardType) == *CT) { return i; }
    }
    cout << " There is no Card of this type in this vector." << endl;
    return -1;                                                     // This section should never be reached
}