#ifndef PLAYER_H
#define PLAYER_H

#include "Orders.h"
#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include "Map.h"
#include <memory>
#include "Cards.h"
using namespace std;


class Orderlist;
class Orders;

class Player{
    public:
        Player();                                                       // Player Constructor
        Player(std::string name);                                       // Parameterized Constructor
        Player(const Player& other);                                    // Player Copy Constructor
        Player& operator=(const Player& other);                         // Player Copy Assignment Operator
        ~Player();                                                      // Player Destructor
        

        void addToDefend(Territory* territory);                             // Add a territory to the list of territories to be defended
        void addToAttack(Territory* territory);                             // Add a territory to the list of territories to be attacked

        std::vector<Territory*>* toDefend();                                // Returns a list of territories to be defended
        std::vector<Territory*>* toAttack();                                // Returns a list of territories to be attacked
        void issueOrder(std::unique_ptr<Orders> order) ;      // Add a specific Order to the OrderList

        friend std::ostream& operator << (std::ostream& out, const Player& player);     // Overload the << operator for easy printing of Player details
        std::string getName() const { return *name; }                                   // Getter for player's name
        
    private:
        void copyFrom(const Player& other);                                             // Helper to deep copy from another player
        void cleanUp();                                                                 // Helper to free resources

        std::string* name;

        // TODO change int to pointer of territories and Cards
        std::vector<Territory*>* defendCollection;                     // A List of Territories the Player should Defend
        std::vector<Territory*>* attackCollection;                     // A List of Territories the Player should Attack
        Hand* cardCollection;                                           // A List of Cards in a Player's hand

        Orderlist* orderCollection;                                     // A List of Orders a player executes
};

#endif
