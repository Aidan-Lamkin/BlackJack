//
// Created by Aidan Lamkin on 8/3/20.
//

#ifndef FINALPROJECT_FUNCTIONS_H
#define FINALPROJECT_FUNCTIONS_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "functions.h"
using namespace std;

void introduction();

void fillDeck(vector <string>& deck);

void copyDeck(vector<string>& fullDeck, vector<string> &currentDeck);

void clearCurrentDeck(vector<string>& currentDeck);

string playAgain();

int placeBet(int numberOfChips);

//function definitions for functions.cpp
#endif //FINALPROJECT_FUNCTIONS_H
