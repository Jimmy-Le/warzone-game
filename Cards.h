//
// Created by Keishaun on 2025-09-13.
//

#ifndef CARDS_H
#define CARDS_H

#include <string>
#include <vector>
#include <memory>

#include "Orders.h"
#include "Player.h"
using namespace std;

/**
 * These are so the classes exist to be used/referenced within the Card class
 */
class Hand;
class Deck;
class Player;

/**
 * This is the Card class
 */
class Card {
    public:
    std::shared_ptr<std::string> cardType;                          // This is an attribute of the Card class

    Card();                                                         // This is the default constructor for a Card
    Card(std::string type);                                         // This is the parameterized constructor for a Card     
    Card(const Card& other);                                        // This is the copy constructor for a Card
    ~Card();                                                        // This is the destructor for a Card      

    Card& operator=(const Card& other);                             // This is the overloaded assignment operator for Cards    
    friend std::ostream& operator<<(ostream& os, const Card& c);    // This is the stream operator for a Card

    void play(Hand * specificHand,Deck * specificDeck, Player* player);  // This function allows a player to play a specific Card from their Hand
};

/**
 * This is the Hand class
 */
class Hand {
public:
    std::shared_ptr<std::vector<Card>> hand;                        // This holds all the Cards that a player has in their Hand 

    Hand();                                                         // This is the default constructor for a Hand                       
    Hand(const Hand& other);                                        // This is the copy constructor for a Hand
    ~Hand();                                                        // This is the destructor for a Hand                           

    Hand& operator=(const Hand& other);                             // This is the overloaded assignment operator for Hands
    friend std::ostream& operator<<(ostream& os, const Hand& h);    // This is the stream operator for a Hand
};

/**
 * This is the Deck class
 */
class Deck{
    public:
    std::shared_ptr<std::vector<Card>> deck;                        // This holds all the Cards contained within a Deck   
    std::shared_ptr<int> deckSize;                                  // This is an attribute of the Deck class
    
    Deck();                                                         // This is the default constructor for a Deck                                        
    Deck(const Deck& other);                                        // This is the copy constructor for a Deck              
    ~Deck();                                                        // This is the destructor for a Deck                   

    Deck& operator=(const Deck& other);                             // This is the overloaded assignment operator for Decks
    friend std::ostream& operator<<(ostream& os, const Deck& d);    // This is the stream operator for a Deck
    void draw(Hand * specificHand);                                 // This function allows a player to draw a random Card from the Deck
    
};

/**
 * This is a helper function used in Cards.cpp to find the index of a selected card in a vector
 */
int findIndexOfCard(std::shared_ptr<vector<Card>> TV, std::shared_ptr<std::string> CT);

#endif //COMP345_CARDS_H