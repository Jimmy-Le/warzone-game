//
// Created by Keishaun on 2025-09-13.
//

#include "Cards.h"

#include <iostream>
#include <random>
#include <vector>
#include <string>

using namespace std;

Hand::Hand() : hand(make_shared<vector<Card>>()) {}
Hand::Hand(const Hand& other) {
    hand = make_shared<vector<Card>>(*other.hand);
}
Hand& Hand::operator=(const Hand& other) {
    if (this == &other) return * this;
    hand = make_shared<vector<Card>>(*other.hand);
    return * this;
}
Hand::~Hand() = default;
Card::Card() : cardType(std::make_shared<std::string>("")) {}
Card::Card(std::string type) : cardType(std::make_shared<std::string>(type)) {}
Card::Card(const Card& other) : cardType(std::make_shared<std::string>(*other.cardType)) {}
Card& Card::operator=(const Card& other) {
    if (this == &other) return * this;
    cardType = std::make_shared<std::string>(*other.cardType);
    return * this;
}
void Card::play(Hand * specificHand,Deck * specificDeck) {
    int usedCard = findIndexOfCard(specificHand->hand, this->cardType);
    if ((* this->cardType) == "bomb") {
        cout << "Player used a bomb card. The card has been returned to the deck.\n" << endl;
    }
    else if ((* this->cardType) == "reinforcement") {
        cout << "Player used a reinforcement card. The card has been returned to the deck.\n" << endl;
    }
    else if ((* this->cardType) == "blockade") {
        cout << "Player used a blockade card. The card has been returned to the deck.\n" << endl;
    }
    else if ((* this->cardType) == "airlift") {
        cout << "Player used a airlift card. The card has been returned to the deck.\n" << endl;
    }
    else if ((* this->cardType) == "diplomacy") {
        cout << "Player used a diplomacy card. The card has been returned to the deck.\n" << endl;
    }
    specificDeck->deck->push_back(specificHand->hand->at(usedCard));
    specificHand->hand->erase(specificHand->hand->begin() + usedCard);
    (* specificDeck->deckSize)++;
}
Card::~Card() = default;
Deck::Deck() : deck(make_shared<vector<Card>>()),deckSize(make_shared<int>(0)) {
    for (int i = 0; i < 10; i++) {
        this->deck->push_back(Card("bomb"));
        this->deck->push_back(Card("reinforcement"));
        this->deck->push_back(Card("blockade"));
        this->deck->push_back(Card("airlift"));
        this->deck->push_back(Card("diplomacy"));
        (* this->deckSize) += 5;
    }
}
Deck::Deck(const Deck& other) : deck(std::make_shared<std::vector<Card>>(*other.deck)),
deckSize(std::make_shared<int>(*other.deckSize)) {}
Deck& Deck::operator=(const Deck& other) {
    if (this == &other) return * this;
    deck = make_shared<vector<Card>>(*other.deck);
    deckSize = make_shared<int>(*other.deckSize);
    return * this;
}
void Deck::draw(Hand * specificHand) {
    if ((* this->deckSize) == 0) {cout << "The deck is empty.\n" << endl; return;}
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, (* deckSize) - 1);
    int cardPicked = dis(gen);
    specificHand->hand->push_back(deck->at(cardPicked));
    deck->erase(deck->begin() + cardPicked);
    (* deckSize)--;
}
Deck::~Deck() = default;
int findIndexOfCard(std::shared_ptr<vector<Card>> TV, std::shared_ptr<std::string> CT) {
    for (int i = 0; i < TV->size(); i++) {
        if (*(TV->at(i).cardType) == *CT) { return i; }
    }
}