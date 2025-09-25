#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;




class FakeOrder {
    public:
        FakeOrder();
        void printOrder();
        string name;
};

class FakeOrderList {
    public:
        FakeOrderList();
        void add(FakeOrder* order);
        void printOrderList();
        vector<FakeOrder*> orders;

};


/***
 * Player Class
 */
class Player{
    public:
        Player();                                                       // Player Constructor

        // TODO Change string to list of territories 
        vector<string> toDefend();                                      // Returns a list of territories to be defended
        vector<string> toAttack();                                      // Returns a list of territories to be attacked
        void issueOrder();                                              // Create a Order object and add it to the OrderList (orderCollection)
        void printPlayer();                                             // Print the player's details (for debugging)

    private:
        // TODO change int to pointer of territories and Cards
        vector<string> defendCollection;                                // A List of Territories the Player should Defend
        vector<string> attackCollection;                                // A List of Territories the Player should Attack
        vector<string> cardCollection;                                  // A List of Cards in a Player's hand

        // TODO Change this to be an OrderList object
        FakeOrderList orderCollection;                                 // A List of Orders a player executes?

};








#endif