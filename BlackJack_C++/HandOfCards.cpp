//
// Created by Aidan Lamkin on 8/3/20.
//

#include "HandOfCards.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "functions.h"
using namespace std;
/**draws a card to put in a hand and then erases the card drawn from the deck of cards, then displays what card was drawn
 *
 * @param currentDeck - deck of cards that was used for the round
 */
void HandOfCards::hit(vector<string> &currentDeck){
    cardsInHand.resize(cardsInHand.size() + 1);
    int randomCard = rand() % currentDeck.size();
    cardsInHand.at(cardsInHand.size() - 1) = currentDeck.at(randomCard);
    currentDeck.erase(currentDeck.begin() + randomCard);
    cout << "You were dealt a " << cardsInHand.at(cardsInHand.size() - 1) << endl;
}
/**assigns a value for the string of a card based on the first character of the card
 *
 */
void HandOfCards::assignCardValue(){
    string card;
    card = (cardsInHand.at(cardsInHand.size() - 1));
    valueOfCards.resize(valueOfCards.size() + 1);
    char c = card.at(0);
    if(c == 'A'){
        valueOfCards.at(valueOfCards.size() - 1) = 1;
    }
    else if(c == '2'){
        valueOfCards.at(valueOfCards.size() - 1) = 2;
    }
    else if(c == '3'){
        valueOfCards.at(valueOfCards.size() - 1) = 3;
    }
    else if(c == '4'){
        valueOfCards.at(valueOfCards.size() - 1) = 4;
    }
    else if(c == '5'){
        valueOfCards.at(valueOfCards.size() - 1) = 5;
    }
    else if(c == '6'){
        valueOfCards.at(valueOfCards.size() - 1) = 6;
    }
    else if(c == '7'){
        valueOfCards.at(valueOfCards.size() - 1) = 7;
    }
    else if(c == '8'){
        valueOfCards.at(valueOfCards.size() - 1) = 8;
    }
    else if(c == '9'){
        valueOfCards.at(valueOfCards.size() - 1) = 9;
    }
    else if(c == 'K'){
        valueOfCards.at(valueOfCards.size() - 1) = 10;
    }
    else if(c == 'Q'){
        valueOfCards.at(valueOfCards.size() - 1) = 10;
    }
    else if(c == 'J'){
        valueOfCards.at(valueOfCards.size() - 1) = 10;
    }
    else{
        valueOfCards.at(valueOfCards.size() - 1) = 10;
    }
}
/**checks a hand to see if the user has an ace, if so the user is prompted to enter the value for the ace (1 or 11)
 * the prompt repeats till a valid answer is given
 *
 */
void HandOfCards::checkForAce() {
    int userInput;
    for(int i = 0; i < valueOfCards.size(); ++i){
        if(valueOfCards.at(i) == 1){
            while(userInput != 1 && userInput != 11) {
                cout << "Would you like your Ace to be worth 1 or 11? ";
                cin >> userInput;
            }
            if(userInput == 1){
                continue;
            }
            else if(userInput == 11){
                valueOfCards.at(i) = 11;
            }
        }

    }
}
/**erases both the string and the value of each card from the player hand
 *
 */
void HandOfCards::clearHand() {
    valueOfCards.clear();
    cardsInHand.clear();
}
/**adds all values of the cards in a hand and returns the total sum
 *
 * @return - sum of all cards
 */
int HandOfCards::getHandSum() {
    int sum = 0;
    for(int i = 0; i < valueOfCards.size(); ++i){
        sum = sum + valueOfCards.at(i);
    }
    return sum;
}
/**prints the sum of all cards in a nice sentence format
 *
 */
void HandOfCards::printHandSum(){
    cout << "Your hand total is " << getHandSum() << endl;
}
/**the initial play of the dealer where the dealer hits twice and shows the second card drawn, for the dealer an ace is
 *initially given the value of 11 unless the dealer busts then it reverts to 1
 *
 * @param currentDeck - deck of cards being used in the current round
 */
void HandOfCards::dealerSetup(vector<string> &currentDeck){
    int randomCard;
    cardsInHand.resize(cardsInHand.size() + 1);
    randomCard = rand() % currentDeck.size();
    cardsInHand.at(cardsInHand.size() - 1) = currentDeck.at(randomCard);
    currentDeck.erase(currentDeck.begin() + randomCard);
    assignCardValue();
    cardsInHand.resize(cardsInHand.size() + 1);
    randomCard = rand() % currentDeck.size();
    cardsInHand.at(cardsInHand.size() - 1) = currentDeck.at(randomCard);
    currentDeck.erase(currentDeck.begin() + randomCard);
    assignCardValue();
    for(int i = 0; i < valueOfCards.size(); ++i){
        if(valueOfCards.at(i) == 1){
            valueOfCards.at(i) = 11;
        }
    }
    cout << "The dealer is showing a " << cardsInHand.at(cardsInHand.size() - 1) << endl;

}
/**first displays the other card the dealer initially drew and the total sum of the dealer hand, then makes the dealer
 *hit until the hand has a sum total of at least 17 or the dealer has busted, the card and new total is displayed
 * everytime the dealer hits
 *
 * @param currentDeck - deck of cards being used in the current round
 */
void HandOfCards::dealerHit(vector<string>&currentDeck) {
    int randomCard;
    cout << "The dealer's first card is a " << cardsInHand.at(0) << endl;
    cout << "The dealer hand's total is " << getHandSum() << endl;
    while(getHandSum() < 17){
        cardsInHand.resize(cardsInHand.size() + 1);
        randomCard = rand() % currentDeck.size();
        cardsInHand.at(cardsInHand.size() - 1) = currentDeck.at(randomCard);
        cout << "The dealer drew a " << cardsInHand.at(cardsInHand.size() - 1) << endl;
        currentDeck.erase(currentDeck.begin() + randomCard);
        assignCardValue();
        cout << "The dealer hand's total is " << getHandSum() << endl;
        if(getHandSum() > 21){
            for(int i = 0; i < valueOfCards.size(); ++i){
                if(valueOfCards.at(i) == 11){
                    valueOfCards.at(i) = 1;
                }
            }
            if(getHandSum() > 21) {
                cout << "The dealer busted!" << endl;
                return;
            }
        }
    }
}
/**checks to see if a hand total is over 21 (busted)
 *
 * @return - true/false on whether or not the hand total has busted
 */
bool HandOfCards::checkForBust() {
    if(getHandSum() < 21){
        return false;
    }
    else if(getHandSum() > 21){
        return true;
    }
}
/**makes the players ace worth 11 automatically if it means that the player would get a blackjack
 *
 * @return - returns 1 if the user would score a blackjack with ace and facecard
 */
int HandOfCards::aceLogic() {
    for(int i = 0; i < valueOfCards.size(); ++i){
        if(valueOfCards.at(i) == 1 && getHandSum() + 10 == 21) {
            valueOfCards.at(i) = 11;
            return 1;
        }
    }
}
/**checks to see if the player has the ability to split the hand (this is availible only if the user has the same card)
 *and then asks the user is they would like to split or not, if so it checks to see if the user has enough chips to split,
 *then if all of that is true the second card is moved from the current hand to the split hand along with its value
 *
 * @param PlayerSplit - vector of the players split hand of cards
 * @param currentBet - amount that the player is currently betting in the current round
 * @param numberOfChips - total amount of chips the user has
 * @return - true/false on whether or not the user is splitting their hand
 */
bool HandOfCards::checkSplit(HandOfCards&playerSplit, int currentBet, int numberOfChips) {
    string userInput;
    string card1 = cardsInHand.at(0);
    string card2 = cardsInHand.at(1);
    char c1 = card1.at(0);
    char c2 = card2.at(0);
    if(c1 == c2){
        if(currentBet * 2 < numberOfChips){
            cout << "You are unable to split because you don't have enough chips." << endl;
        }
        while(userInput != "Yes" && userInput != "yes" && userInput != "No" && userInput != "no") {
            cout << "Would you like to split your hand in to two hands? (Type yes or no) ";
            cin >> userInput;
        }
        if(userInput == "Yes" || userInput == "yes"){
            playerSplit.cardsInHand.resize(playerSplit.cardsInHand.size() + 1);
            playerSplit.cardsInHand.at(0) = cardsInHand.at(1);
            cardsInHand.erase(cardsInHand.begin() + 1);
            playerSplit.valueOfCards.resize(playerSplit.valueOfCards.size() + 1);
            playerSplit.valueOfCards.at(0) = valueOfCards.at(1);
            valueOfCards.erase(valueOfCards.begin() + 1);
            return true;
        }
        else if(userInput == "No" || userInput == "no"){
            return false;
        }
    }
}