//Aidan Lamkin
//Final Project: BlackJack
#include <iostream>
#include <vector>
#include <string>
#include "functions.h"
#include "HandofCards.h"
using namespace std;
int main() {
    vector<string> fullDeck;
    vector<string> currentDeck;
    fillDeck(fullDeck);
    //Declaring vectors for a full deck, a deck to copy the full deck, then filling full deck from file

    HandOfCards playerHand;
    HandOfCards playerSplit;
    HandOfCards dealerHand;
    //establishing the class objects for the players hand, players split hand, and the dealers hand

    string userMove;
    string nextGame = "play";
    //establishing a variable for the user to input their next move, and whether or not they want to play another game
    //(initially defined the nextGame variable to play to start the game loop)

    srand(time(0));
    //using time to simulate true randomness when drawing cards from a deck

    int numberOfChips = 10;
    int currentBet = 0;
    int splitBet = 0;
    const int BLACKJACK = 21;
    //defining integers for the users number of chips and initial bets

    introduction();
    cout << endl;
    //calls a function to display the basic rules of blackjack to user

    while((nextGame == "play" || nextGame == "play") && numberOfChips > 0) {
        //loop repeats while the user enters play or if they have any chips to bet

        nextGame = playAgain();
        //asks the user whether or not they want to play another round

        if(nextGame == "play" || nextGame == "Play") {
            //if the user enters play the round starts

            cout << "You have " << numberOfChips << " chips" << endl;
            //tells the user how many total chips the user has

            bool split = false;
            //initially declares that the user does not want to split their hand

            currentBet = placeBet(numberOfChips);
            while(currentBet > numberOfChips) {
                currentBet = placeBet(numberOfChips);
            }
            cout << endl;
            //asks the user how much the user wants to bet and if their bet is more chips than what they have it
            //repeats the prompt to enter a bet until a valid input is given

            copyDeck(fullDeck, currentDeck);
            //copies the full deck of cards into a empty deck of cards for the round

            playerHand.hit(currentDeck);
            playerHand.assignCardValue();
            playerHand.hit(currentDeck);
            playerHand.assignCardValue();
            //the player is then dealt two cards from the current deck, which are then taken out of the current deck
            //and then given a numerical value

            if(playerHand.aceLogic() != 1) {
                playerHand.checkForAce();
            }
            playerHand.checkForAce();
            //checks to see if the user has a face card and an ace if so the user has a blackjack and defaults the ace
            //to an 11, if not the user gets the choice on whether the ace is a 1 or a 11

            playerHand.printHandSum();
            //displays the users total hand value to them

            split = playerHand.checkSplit(playerSplit, currentBet, numberOfChips);
            cout << endl;
            //if the user has the same type of card (like two 7's or two Kings's and not two clubs or two diamonds)
            //the game will ask the user to split, if the user chooses yes but does not have enough chips to split the
            //function defaults to false

            if(split == true){
                splitBet = currentBet;
            }
            //if the user chooses to split, the current bet is copied to split bet

            if(playerHand.getHandSum() != BLACKJACK) {
                dealerHand.dealerSetup(currentDeck);
                cout << endl;
            }
            //if the user did not score a blackjack, the dealer draws two cards and shows the second card drawn

            bool bustCheck = false;
            bool bustCheckSplit = false;
            //defaults user to not have busted for both hands


            userMove = "Blank";
            //defaults user move to a string that will enter the loop

            while(userMove != "stay" && userMove != "Stay" && bustCheck == false && playerHand.getHandSum() != BLACKJACK) {
                //loop plays as long as the user did not get a blackjack, bust, or made their move stay

                if(userMove != "hit" || userMove != "Hit" || userMove != "Stay" || userMove != "stay" || userMove != "Doubledown" || userMove != "doubledown") {
                    cout << "Would you like to hit, doubledown, or stay? (type answer) ";
                    cin >> userMove;
                }
                //asks the user to enter in their next move and repeats prompt until a valid answer is given

                if(userMove == "hit" || userMove == "Hit"){
                    playerHand.hit(currentDeck);
                    playerHand.assignCardValue();
                    playerHand.checkForAce();
                    playerHand.printHandSum();
                    cout << endl;
                    //if the user chose hint, they are dealt another card, which is assigned a value, then checks for
                    //an ace to determine a value for the ace, and prints the users hand total

                    bustCheck = playerHand.checkForBust();
                    //checks to see if the user busted (hand totaled over 21)
                }
                if(userMove == "Doubledown" || userMove == "doubledown"){
                    if(((currentBet * 2) + splitBet) > numberOfChips){
                        cout << "You can not double down because you don't have enough chips." << endl << endl;
                    }
                    //if the user does not have enough chips to double down they are prompted so and are
                    //asked to enter in their next move

                    else {
                        currentBet = currentBet * 2;
                        playerHand.hit(currentDeck);
                        playerHand.assignCardValue();
                        playerHand.checkForAce();
                        playerHand.printHandSum();
                        cout << endl;
                        //if the user has enough chips to double down they only hit once, double their bet and are
                        //displayed their total hand value

                        bustCheck = playerHand.checkForBust();
                        //checks to see if the player busted
                        break;
                    }
                }
                else{
                    continue;
                    //if the user entered stay the loop ends
                }
                if(playerHand.getHandSum() == BLACKJACK){
                    break;
                    //if the user gets a blackjack the loop ends
                }
            }
            if(bustCheck == true){
                cout << "You busted!" << endl << endl;
                //if the player busted with their first hand and has a split hand they are only displayed that they
                //busted
                if(split == true){
                    playerHand.clearHand();
                    numberOfChips = numberOfChips - currentBet;
                    cout << "You lost " << currentBet << " chips!" << endl;
                    currentBet = 0;
                }
                else if(split == false) {
                    playerHand.clearHand();
                    dealerHand.clearHand();
                    clearCurrentDeck(currentDeck);
                    numberOfChips = numberOfChips - currentBet;
                    cout << "You lost " << currentBet << " chips!" << endl;
                    continue;
                    //if the player busted and does not have a split hand the hands are reset and the user loses their
                    //current bet amount of chips
                }
            }

            if(playerHand.getHandSum() == BLACKJACK){
                cout << "Blackjack!" << endl << endl;
                //if player scores a blackjack they are displayed so
                if(split == true){
                    playerHand.clearHand();
                    numberOfChips = numberOfChips + (currentBet * 1.5);
                    cout << "You gained " << int (currentBet * 1.5) << " chips!" << endl;
                    currentBet = 0;
                    //if the player ahs a split hand, the player hand is cleared, then payed in a 3:2 ratio, and the current bet is reset.
                }
                if(split == false) {
                    playerHand.clearHand();
                    dealerHand.clearHand();
                    clearCurrentDeck(currentDeck);
                    numberOfChips = numberOfChips + (currentBet * 1.5);
                    cout << "You gained " << int (currentBet * 1.5) << " chips!" << endl;
                    continue;
                    //if the player has no split hand, the hands are cleared and the user wins back in 3:2 ratio
                }
            }


            userMove = "Blank";
            //defaults user move to a string that will enter the loop

            while(userMove != "stay" && userMove != "Stay" && bustCheckSplit == false && split == true) {
                //loop plays as long as the user did not get a blackjack, bust, or made their move stay,
                //split hand also must be true

                if(userMove != "hit" || userMove != "Hit" || userMove != "Stay" || userMove != "stay" || userMove != "Doubledown" || userMove != "doubledown") {
                    cout << "Would you like to hit, double down, or stay with your split hand? (type answer) ";
                    cin >> userMove;
                }
                //asks the user to enter in their next move and repeats prompt until a valid answer is given

                if(userMove == "hit" || userMove == "Hit"){
                    playerSplit.hit(currentDeck);
                    playerSplit.assignCardValue();
                    playerHand.checkForAce();
                    playerSplit.printHandSum();
                    cout << endl;
                    //if the user chose hint, they are dealt another card, which is assigned a value, then checks for
                    //an ace to determine a value for the ace, and prints the users hand total

                    bustCheckSplit = playerSplit.checkForBust();
                    //checks to see if the user busted (hand totaled over 21)

                }
                if(userMove == "Doubledown" || userMove == "doubledown"){
                    if(((splitBet * 2) + currentBet) > numberOfChips){
                        cout << "You can not doubledown because you don't have enough chips." << endl << endl;
                        //if the user does not have enough chips to double down they are prompted so and are
                        //asked to enter in their next move

                    }
                    else {
                        splitBet = splitBet * 2;
                        playerSplit.hit(currentDeck);
                        playerSplit.assignCardValue();
                        playerHand.checkForAce();
                        playerSplit.printHandSum();
                        cout << endl;
                        //if the user has enough chips to double down they only hit once, double their bet and are
                        //displayed their total hand value

                        bustCheckSplit = playerSplit.checkForBust();
                        //checks to see if the user busted (hand totaled over 21)
                        break;
                    }
                }
                else{
                    continue;
                    //if the user entered stay the loop ends
                }
                if(playerSplit.getHandSum() == BLACKJACK){
                    break;
                    //if the user gets a blackjack the loop ends
                }
            }

            if(bustCheckSplit == true){
                cout << "You busted!" << endl << endl;
                playerSplit.clearHand();
                numberOfChips = numberOfChips - splitBet;
                cout << "You lost " << splitBet << " chips!" << endl;
                splitBet = 0;
                //if the player busted with split hand, they are prompted that they busted, the split hand is cleared,
                //and the user loses their split bet, then resets split bet
            }
            if(playerSplit.getHandSum() == BLACKJACK){
                cout << "Blackjack!" << endl << endl;
                playerSplit.clearHand();
                numberOfChips = numberOfChips + int (splitBet * 1.5);
                cout << "You gained " << int (splitBet * 1.5) << " chips!" << endl;
                splitBet = 0;
                //if the user gets a blackjack with their split hand, they are prompted that they got a blackjack,
                //the split hand is cleared, and the user is payed back at a 3:2 ratio, then resets split bet
            }

            dealerHand.dealerHit(currentDeck);
            cout << endl;
            //the dealer then hits until their hand is over 17 or the dealer busted

            if(dealerHand.checkForBust() == true){
                cout << "You won!" << endl << endl;
                playerHand.clearHand();
                dealerHand.clearHand();
                clearCurrentDeck(currentDeck);
                //if the dealer busted the player won and the decks are cleared

                if(split == false) {
                    numberOfChips = numberOfChips + currentBet;
                    cout << "You gained " << currentBet << " chips!" << endl;
                }
                else if(split == true){
                    numberOfChips = numberOfChips + currentBet + splitBet;
                    cout << "You gained " << currentBet + splitBet << " chips!" << endl;
                }
                //depending on how many hands the user has left the bet is payed back
                continue;
            }
            if(dealerHand.getHandSum() == BLACKJACK){
                cout << "Dealer won!" << endl << endl;
                playerHand.clearHand();
                dealerHand.clearHand();
                clearCurrentDeck(currentDeck);
                //if the dealer got a blackjack the user is prompted and the hands are cleared along with the deck

                if(split == false) {
                    numberOfChips = numberOfChips - currentBet;
                    cout << "You lost " << currentBet << " chips!" << endl;
                }
                else if(split == true){
                    numberOfChips = numberOfChips - currentBet - splitBet;
                    cout << "You lost " << splitBet << " chips!" << endl;
                }
                //depending on how many hands the user has left the bets are subtracted from the users total
                continue;
            }

            if(playerHand.getHandSum() > dealerHand.getHandSum() && playerHand.getHandSum() < BLACKJACK){
                cout << "You won!" << endl;
                numberOfChips = numberOfChips + currentBet;
                cout << "You gained " << currentBet << " chips!" << endl;
            }
            else if(playerHand.getHandSum() < dealerHand.getHandSum() && dealerHand.getHandSum() < BLACKJACK){
                cout << "Dealer won!" << endl;
                numberOfChips = numberOfChips - currentBet;
                cout << "You lost " << currentBet << " chips!" << endl;
            }
            else if(playerHand.getHandSum() == dealerHand.getHandSum()){
                cout << "It's a push!" << endl;
                cout << "Your number of chips stayed the same!" << endl;
            }
            cout << endl;
            //if both the player hand and the dealer did not split the winner is determined and the bet is either won,
            //lost, or in the case of a push the total does not change

            if(split == true && bustCheckSplit == false && playerSplit.getHandSum() != BLACKJACK) {
                if (playerSplit.getHandSum() > dealerHand.getHandSum() && playerSplit.getHandSum() < BLACKJACK) {
                    cout << "Your split hand won!" << endl;
                    numberOfChips = numberOfChips + splitBet;
                    cout << "You gained " << splitBet << " chips!" << endl;
                }
                else if (playerSplit.getHandSum() < dealerHand.getHandSum() && dealerHand.getHandSum() < BLACKJACK) {
                    cout << "Dealer won against your split hand!" << endl;
                    numberOfChips = numberOfChips - splitBet;
                    cout << "You lost " << splitBet << " chips!" << endl;
                }
                else if (playerSplit.getHandSum() == dealerHand.getHandSum()) {
                    cout << "It's a push against your split hand!" << endl;
                    cout << "Your number of chips stayed the same!" << endl;
                }
                cout << endl;
                //if both the player split hand and the dealer did not split the winner is determined and the bet is either won,
                //lost, or in the case of a push the total does not change
            }

            playerHand.clearHand();
            playerSplit.clearHand();
            dealerHand.clearHand();
            clearCurrentDeck(currentDeck);
            //all hands are cleared along with the current deck

            currentBet = 0;
            splitBet = 0;
            //bets are reset
        }

    }

    if(numberOfChips == 0){
        cout << "Sorry, you're broke. Better luck next time!" << endl;
    }
    else if(numberOfChips > 10){
        cout << "You gained " << numberOfChips - 10 << " chips while at the table. Nice!" << endl;
    }
    else if(numberOfChips < 10){
        cout << "You lost " << 10 - numberOfChips << " chips while at the table. Try your luck another time!" << endl;
    }
    else{
        cout << "You broke even. Not bad." << endl;
    }
    //once the user wants to quit or has lost all their chips they are displayed how they did compared to their
    //starting chips

    cout << "Have a nice day!" << endl;
    //program ends

    return 0;
}
