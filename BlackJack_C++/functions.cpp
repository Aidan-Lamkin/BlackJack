//
// Created by Aidan Lamkin on 8/3/20.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "functions.h"
using namespace std;
/**displays user with basic rules of blacckjack
 *
 */
void introduction(){
    cout << "Welcome to my player versus computer blackjack game! The goal of the game is to get your hand of cards as" << endl;
    cout << "close to 21 as possible without exceeding 21." << endl;
}

/**creates a copy of a full deck of cards from reading from a file
 *
 * @param deck - vector for a copy of a full deck of cards
 */
void fillDeck(vector <string>& deck){
    ifstream DeckOfCards;
    DeckOfCards.open("DeckOfCards.txt");

    if(!DeckOfCards.is_open()){
        cerr << "Error opening input file." << endl;
        return;
    }

    int counter = 0;
    while(!DeckOfCards.eof()){
        deck.resize(deck.size() + 1);
        string line;
        getline(DeckOfCards, line);
        deck.at(counter) = line;
        ++counter;
    }

    DeckOfCards.close();
}

/**copys a full deck of cards to a vector that will be used in the round
 *
 * @param fullDeck - vector of a full deck of cards
 * @param currentDeck - vector of a deck of cards used in the round
 */
void copyDeck(vector<string>& fullDeck, vector<string> &currentDeck){
    for(int i = 0; i < fullDeck.size(); ++i){
        currentDeck.resize(currentDeck.size() + 1);
        currentDeck.at(i) = fullDeck.at(i);
    }
}
/**function that clears the deck of cards used in the round for next round
 *
 * @param currentDeck - vector of deck of cards used in the round
 */
void clearCurrentDeck(vector<string>& currentDeck){
    currentDeck.clear();
}

/**function that asks the user whether or not they would like to play another round, repeats prompt until a
 *valid answer is given
 *
 * @return - string of the users answer (either play or quit)
 */
string playAgain(){
    string userInput;
    while(userInput != "Play" || userInput != "play" || userInput != "quit" || userInput != "Quit") {
        cout << "Would you like to play a round or quit: (type answer) ";
        cin >> userInput;
        if(userInput == "Play" || userInput == "play" || userInput == "quit" || userInput == "Quit"){
            return userInput;
        }
    }
}
/**asks the user how many chips they would like to bet
 *
 * @param numberOfChips
 * @return
 */
int placeBet(int numberOfChips){
    int currentBet = -1;
    while(currentBet < 0 && currentBet < numberOfChips){
        cout << "How many chips would you like to bet? ";
        cin >> currentBet;
    }
    return currentBet;
}