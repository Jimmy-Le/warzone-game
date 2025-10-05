//
// Created by Keishaun on 2025-09-19.
//

#include "CardsDriver.h"

// int main() {
//     testCards();
//     return 0;
// }

void testCards() {
    cout <<
        "-----------------------------------------------------------------------\n"
        "---- Here is the test driver for the cards section of the project! ----\n"
        "-----------------------------------------------------------------------\n"
    << endl;
    Deck gameDeck;
    Hand playerHand;
    for (int o = 0; o < 10; o++) {gameDeck.draw(&playerHand);}
    cout << "The player now has " << playerHand.hand->size() << " cards in their hand.\n" << endl;
    cout << "The deck now contains " << (* gameDeck.deckSize) << " cards.\n" << endl;
    for (int o = 0; o < playerHand.hand->size();) {
        playerHand.hand->at(o).play(&playerHand,&gameDeck);
    }
    cout << "The player now has " << playerHand.hand->size() << " cards in their hand.\n" << endl;
    cout << "The deck now contains " << (* gameDeck.deckSize) << " cards.\n" << endl;
}