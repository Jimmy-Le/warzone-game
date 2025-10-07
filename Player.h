#ifndef PLAYER_H
#define PLAYER_H

#include "Cards.h"
#include "Orders.h"
#include "Map.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Orderlist;
class Orders;
class Card;
class Hand;
class Territory;

class Player{
    public:
        Player();                                                                       // Player Constructor
        Player(std::string name);                                                       // Parameterized Constructor
        Player(const Player& other);                                                    // Player Copy Constructor
        Player& operator=(const Player& other);                                         // Player Copy Assignment Operator
        ~Player();                                                                      // Player Destructor
        
        void addToDefend(Territory* territory);                                         // Add a territory to the list of territories to be defended
        void addToAttack(Territory* territory);                                         // Add a territory to the list of territories to be attacked
        Orderlist* getOrderList();                                                      // Returns the player's order list
        Hand* getHand();                                                                // Returns the player's hand of cards


        std::vector<Territory*>* toDefend();                                            // Returns a list of territories to be defended
        std::vector<Territory*>* toAttack();                                            // Returns a list of territories to be attacked
        void issueOrder() ;                                                             // Add a specific Order to the OrderList

        friend std::ostream& operator << (std::ostream& out, const Player& player);     // Overload the << operator for easy printing of Player details                                        // Player assignment operator
        std::string getName() const { return *name; }                                   // Getter for player's name
        
    private:
        bool generateOrder();                                           // Helper to generate an order

        std::string* name;

        std::vector<Territory*>* defendCollection;                      // A List of Territories the Player should Defend
        std::vector<Territory*>* attackCollection;                      // A List of Territories the Player should Attack
        Hand* cardCollection;                                           // A List of Cards in a Player's hand

        Orderlist* orderCollection;                                     // A List of Orders a player executes
};

#endif
