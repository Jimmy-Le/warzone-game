//
// Created by Keishaun on 2025-09-13.
//

#ifndef CARDS_H
#define CARDS_H

#include <string>
#include <vector>
#include <memory>

using namespace std;

class Hand;
class Deck;

class Card {
    public:
    std::shared_ptr<std::string> cardType;
    Card();
    Card(std::string type);
    Card(const Card& other);
    Card& operator=(const Card& other);
    void play(Hand * specificHand,Deck * specificDeck);
    ~Card();
};

class Hand {
public:
    std::shared_ptr<std::vector<Card>> hand;
    Hand();
    Hand(const Hand& other);
    Hand& operator=(const Hand& other);
    ~Hand();
};

class Deck{
    public:
    std::shared_ptr<std::vector<Card>> deck;
    std::shared_ptr<int> deckSize;
    // std::shared_ptr<int> deckSize = std::make_shared<int>(0);
    Deck();
    Deck(const Deck& other);
    Deck& operator=(const Deck& other);
    void draw(Hand * specificHand);
    ~Deck();
};

void testCards();

int findIndexOfCard(std::shared_ptr<vector<Card>> TV, std::shared_ptr<std::string> CT);

#endif //COMP345_CARDS_H