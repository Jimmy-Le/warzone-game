#include "Player.h"
#include <iostream>
#include <vector>
using namespace std;

/***
 * Player Constructor, 
 * Initializes the set of territories, cards, and orderlist of a Player
 * TODO Update this to be the proper type
 */
Player::Player(){
    defendCollection = {"France", "Canada", "USA"};
    attackCollection = {"France", "Canada", "USA"};
    cardCollection = {"1", "2", "3"};
    orderCollection = {"Order 1", "Order 2", "Order 3", "Order 4"};
}

/***
 * toDefend()
 * Returns a list of territories that are to be defended
 * TODO Arbitrarily choose which territory to be defended
 */
vector<string> Player::toDefend(){
    cout << "printing Territory to defend";
    return defendCollection;
}

/***
 * toAttack()
 * Returns a list of territories that are to be attacked
 * TODO Arbitrarily choose which territory to be attacked
 */
vector<string> Player::toAttack(){
    cout << "printing Territory to attack";
    return attackCollection;
}

/***
 * issueOrder()
 * Creates an Order object and puts it in the player’s list of orders
 * TODO create Order object
 */
void Player::issueOrder(){
    cout << "issuing orders";
}

