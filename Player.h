#ifndef PLAYER_H
#define PLAYER_H

#include "Orders.h"
#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <memory>
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
        
        // TODO Change string to list of territories 
        std::vector<std::string>* toDefend();                           // Returns a list of territories to be defended
        std::vector<std::string>* toAttack();                           // Returns a list of territories to be attacked
        void issueOrder(int numberOfArmyUnits, string sourceTerritory, string targetTerritory, string orderType) ;      
        // Add a specific Order to the OrderList

        friend std::ostream& operator << (std::ostream& out, const Player& player);   // Overload the << operator for easy printing of Player details
        std::string getName() const { return *name; }                   // Getter for player's name
        
    private:
        void copyFrom(const Player& other);                             // Helper to deep copy from another player
        void cleanUp();                                                 // Helper to free resources

        std::string* name;

        // TODO change int to pointer of territories and Cards
        std::vector<std::string>* defendCollection;                     // A List of Territories the Player should Defend
        std::vector<std::string>* attackCollection;                     // A List of Territories the Player should Attack
        std::vector<std::string>* cardCollection;                       // A List of Cards in a Player's hand

        Orderlist* orderCollection;                                     // A List of Orders a player executes
};

#endif
