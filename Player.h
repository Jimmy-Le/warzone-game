#ifndef PLAYER_H
#define PLAYER_H

#include "Cards.h"
#include "Orders.h"
#include "Map.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Forward declarations to avoid circular dependencies
class Orderlist;
class Orders;
class Card;
class Hand;
class Territory;

class Player{
    private:
        int reinforcementPool = 10;   
        Hand* hand;                                                 // Number of reinforcement armies the player has
    public:
        vector<Player*> negotiatedWith;
        Player();                                                                       // Player Constructor
        Player(std::string name);                                                       // Parameterized Constructor
        Player(const Player& other);                                                    // Player Copy Constructor
        Player& operator=(const Player& other);                                         // Player Copy Assignment Operator
        ~Player();                                                                      // Player Destructor
        
        void addToDefend(Territory* territory);                                         // Add a territory to the list of territories to be defended
        void addToAttack(Territory* territory);                                         // Add a territory to the list of territories to be attacked
        Orderlist* getOrderList();                                                      // Returns the player's order list
        Hand* getHand();

        void setReinforcementPool(int armies);                                        // Sets the number of reinforcement armies the player has
        int getReinforcementPool() const;                                             // Returns the number of reinforcement armies

        std::vector<Territory*>* toDefend();                                            // Returns a list of territories to be defended
        std::vector<Territory*>* toAttack();                                            // Returns a list of territories to be attacked
        void issueOrder() ;                                                             // Add a specific Order to the OrderList

        friend std::ostream& operator << (std::ostream& out, const Player& player);     // Overload the << operator for easy printing of Player details                                        // Player assignment operator
        std::string getName() const { return *name; }                                   // Getter for player's name
         //okay i have removed defend collection from private just so that i can work on execute of deploy order
    private:
        bool generateOrder();                                           // Helper to generate an order
        std::string* name;
        Hand* cardCollection;                                           // The Player's Hand of Cards
        Orderlist* orderCollection;                           // The Player's List of Orders    
        std::vector<Territory*>* attackCollection;  // A List of Territories the Player should Attack
        std::vector<Territory*>* defendCollection; // A List of Territories the Player should Defend                                    // A List of Orders a player executes
};

#endif
