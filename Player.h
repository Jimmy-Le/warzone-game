#ifndef PLAYER_H
#define PLAYER_H

#include "Cards.h"
#include "Orders.h"
#include "Map.h"
#include "LoggingObserver.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Forward declarations to avoid circular dependencies
class Orderlist;
class Orders;
class Card;
class Hand;
class Territory;
class PlayerStrategy;
//NOTE: I added a few things to satisfy the Strategy design pattern
//mainly a PlayerStrategy data member and a setStrategy() method;
class Player : public Subject, public ILoggable{
    private:
        std::string lastAction;
        int reinforcementPool;                                                          // Number of reinforcement armies the player has
        int tentativePool;                                                              // Number of reinforcement armies displayed during the reinforcement phase (Used to show how many armies are left to deploy)
        Hand* hand;    
        PlayerStrategy* strategy;

    public:
        const string BANNER = "========================================";               // Banner for display purposes
        vector<Player*> negotiatedWith;
        Player();                                                                       // Player Constructor
        Player(std::string name);                                                       // Parameterized Constructor
        Player(const Player& other);                                                    // Player Copy Constructor
        Player& operator=(const Player& other);                                         // Player Copy Assignment Operator
        ~Player();                                                                      // Player Destructor
        
        void onAttacked();
        void addToDefend(Territory* territory);                                         // Add a territory to the list of territories to be defended
        void addToAttack(Territory* territory);                                         // Add a territory to the list of territories to be attacked
        void removeFromDefend(Territory* territory);                                      // Remove a territory from the list of territories to be defended
        void removeFromAttack(Territory* territory); 
        void setStrategy(PlayerStrategy* strategy);    
        PlayerStrategy* getStrategy(){ return this->strategy; }                               // Remove a territory from the list of territories to be attacked

        Orderlist* getOrderList();                                                      // Returns the player's order list
        Hand* getHand();

        void setReinforcementPool(int armies);                                        // Sets the number of reinforcement armies the player has
        int getReinforcementPool() const;                                             // Returns the number of reinforcement armies
        void addToReinforcementPool(int armies);                                         // Adds armies to the reinforcement pool
        void removeFromReinforcementPool(int armies);                                      // Removes armies from the reinforcement pool

        std::vector<Territory*>* toDefend();                                            // Returns a list of territories to be defended
        std::vector<Territory*>* toAttack();                                            // Returns a list of territories to be attacked

        std::vector<Territory*>* getDefendCollection();                                 // Getter for defendCollection
        std::vector<Territory*>* getAttackCollection();                                 // Getter for attackCollection

        void issueOrder() ;                                                             // Add a specific Order to the OrderList

        friend std::ostream& operator << (std::ostream& out, const Player& player);     // Overload the << operator for easy printing of Player details                                        // Player assignment operator
        std::string getName() const { return *name; }                                   // Getter for player's name
         //okay i have removed defend collection from private just so that i can work on execute of deploy order

        void setLastAction(const std::string &action);
        std::string stringToLog() override;

        void getEnemyTerritories(Territory * source);               // Returns a list of territories that can be attacked from the source territory


    private:
        bool generateOrder();                                                                   // Helper to generate an order
        void deployReinforcments(string source);                                           // Helper to deploy reinforcements
        Territory* findTerritory(std::vector<Territory*> *territoryList, string source);        // Helper to find a territory by name from a list

        void printTerritoryList(std::vector<Territory*>* territoryList);                        // Helper to print a list of territories

        std::string* name;
        Hand* cardCollection;                                           // The Player's Hand of Cards
        Orderlist* orderCollection;                           // The Player's List of Orders    
        std::vector<Territory*>* attackCollection;  // A List of Territories the Player should Attack
        std::vector<Territory*>* defendCollection; // A List of Territories the Player should Defend                                    
};

#endif
