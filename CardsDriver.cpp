//
// Created by Keishaun on 2025-09-19.
//

#include "CardsDriver.h"

/**
 * The free function to test out all the code in Cards.cpp
 */
void testCards() {
    cout << //For presentation purposes
        "-----------------------------------------------------------------------\n"
        "---- Here is the test driver for the cards section of the project! ----\n"
        "-----------------------------------------------------------------------\n"
    << endl;
    Deck gameDeck;                                                          // Creating a Deck for the game
    Hand playerHand;                                                        // Creating a singular player Hand 
    for (int o = 0; o < 10; o++) {gameDeck.draw(&playerHand);}              // Draws a specified number of random Cards into the Hand
    cout << playerHand << endl;                                             // Displays the contents of the Hand
    cout << gameDeck << endl;                                               // Displays the contents of the Deck                
    for (int o = 0; o < playerHand.hand->size();) {
        playerHand.hand->at(o).play(&playerHand,&gameDeck);                 // Plays all Cards within the Hand and returns them all to the Deck
    }
    cout << gameDeck << endl;                                               // Displays the contents of the Deck
    cout << playerHand << endl;                                             // Displays the contents of the Hand
}