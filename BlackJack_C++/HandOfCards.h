//
// Created by Aidan Lamkin on 8/3/20.
//

#ifndef FINALPROJECT_HANDOFCARDS_H
#define FINALPROJECT_HANDOFCARDS_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "functions.h"
using namespace std;

class HandOfCards {
public:
    bool checkSplit(HandOfCards&playerSplit, int currentBet, int numberOfChips);
    int aceLogic();
    bool checkForBust();
    void dealerHit(vector<string>&currentDeck);
    void printHandSum();
    int getHandSum();
    void assignCardValue();
    void hit(vector<string> &currentDeck);
    void checkForAce();
    void clearHand();
    void dealerSetup(vector<string> &currentDeck);
private:
    vector <string> cardsInHand;
    vector <int> valueOfCards;

};
//file that establishes class of hand of cards where several public functions are availible while the strings for the
//card names and integers for the card values is kept as a private data type

#endif //FINALPROJECT_HANDOFCARDS_H
