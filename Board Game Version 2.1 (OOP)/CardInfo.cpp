#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include "CardInfo.h"

using namespace std;

/*************************/
/*  CardInfoConstructor  */
/*************************/
CardInfo::CardInfo(){
    srand(time(NULL));

    //Sets all the card values randomly and one turn loss and one swapPlace
    for(int deckInit = 0; deckInit < 12; deckInit++){
        cardDeck[deckInit] = rand() % 9 + 1;
        drawnPile[deckInit] = 0;
    }
    cardDeck[rand() % 12 + 0] = 0; //One card is lose a turn
    cardDeck[rand() % 12 + 0] = 10; //One card is swap places
    this->printCardValues(); //Prints all card vales
}

/*************************/
/*  deckShuffleFunction  */
/*************************/
void CardInfo::deckShuffle(){
    srand(time(NULL));
    int usedCount = 0;
    //Checks if all cards in cardDeck have been drawn
    for(int deckCheck = 0; deckCheck < 12; deckCheck++){
        if(drawnPile[deckCheck] == 1){
            usedCount++;
        }
    }
    //Sets new values for all cards if they have been used up
    if(usedCount == 12){
        for(int shuffle = 0; shuffle < 12; shuffle++){
            cardDeck[shuffle] = rand() % 9 + 1; //Gives all cards new values
            drawnPile[shuffle] = 0; //Resets all cards to undrawn
        }
        cardDeck[rand() % 12 + 0] = 0; //One card is lose a turn
        cardDeck[rand() % 12 + 0] = 10; //One card is swap places
    }
}

/**************************/
/*    printCardValues     */
/**************************/
void CardInfo::printCardValues(){
    for(int cards = 0; cards < 12; cards++){
        cout << "Card " << cards + 1 << " is " << cardDeck[cards] << "." << endl;
    }
}
/**************************/
/*    drawCard Function   */
/**************************/
int CardInfo::drawCard(){
    srand(time(NULL));
    int randomDraw = rand() % 12 + 0;
    //Picks a new card that has not been drawn yet
    while(drawnPile[randomDraw] == 1){
        randomDraw = rand() % 12 + 0;
    }
    drawnPile[randomDraw] = 1;
    return(cardDeck[randomDraw]); //returns an undrawn card
}
