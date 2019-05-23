#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "PlayerInfo.h"

using namespace std;

/*************************/
/*PlayerInfo Constructor */
/*************************/
PlayerInfo::PlayerInfo(){
    playerSpace = nullptr;
    playerNames = nullptr;
    cout << "Dangling pointers have been removed." << endl;
}

/*************************/
/*PlayerInfoDeconstructor*/
/*************************/
PlayerInfo::~PlayerInfo(){
    delete[] playerNames; //frees memory space for pointers
    delete[] playerSpace;
    cout << "Player memory storage deallocated." << endl;
}
/*************************/
/*  setPlayers function  */
/*************************/
void PlayerInfo::setPlayers(){
    int players;

    cout << "How many players would you like for this game? [2-6]" << endl;
    cin >> players;

    while(cin.fail() || players > 6 || players < 2){
        cout << "Invalid entry, please enter a number between 2 and 6." << endl;
        cin.clear();
        cin.ignore();
        cin >> players;
    }
    numOfPlayers = players; //Sets the amount of players for the game

    try{
        playerNames = new string[numOfPlayers]; //Creates new array of player names
        playerSpace = new int[numOfPlayers]; //Creates new array of player spaces
        for(int a = 0; a < numOfPlayers; a++){
            cout << "Please enter player " << a + 1 << "'s name." << endl;
            cin >> playerNames[a];
            playerSpace[a] = 0;
        }
        this->setFirstTurn(); //Sets the first players turn
    }
    catch(bad_alloc){
        cout << "Unable to allocate space, closing program." << endl;
        system("exit"); //Closes program
    }
}
/*************************/
/*  printSpaces Function */
/*************************/
void PlayerInfo::printSpaces(){
    for(int playerNumber = 0; playerNumber < numOfPlayers; playerNumber++){
        cout << playerNames[playerNumber] << " is on square " << playerSpace[playerNumber] << "." << endl;
    }
}

/*************************/
/* setFirstTurn function */
/*************************/
void PlayerInfo::setFirstTurn(){
    int playerHold[6] = {0, 1, 2, 3, 4, 5};
    int spotHold;

    //Loops around and puts the number of the player with the shortest name at the
    //beginning of the playerHold array
    for(int outLoop = 0; outLoop < numOfPlayers; outLoop++){
        for(int inLoop = 0; inLoop < numOfPlayers -1; inLoop++){
            if(playerNames[playerHold[inLoop]].length() > playerNames[playerHold[inLoop+1]].length()){
                spotHold = playerHold[inLoop];
                playerHold[inLoop] = playerHold[inLoop + 1];
                playerHold[inLoop + 1] = spotHold;
            }
        }
    }
    firstTurn = playerHold[0];
    cout << "The first player will be " << playerNames[firstTurn] << "." << endl;
}

/*************************/
/*  moveForwardFunction  */
/*************************/
void PlayerInfo::moveForward(int turnNum, int cardVal, int boardSpaces, ofstream& output){
    int overStep = 0;
    int backStep = 0;
    playerSpace[turnNum] += cardVal;
    if(playerSpace[turnNum] > boardSpaces){
        overStep = playerSpace[turnNum] - boardSpaces;
        backStep = boardSpaces - overStep;
        playerSpace[turnNum] = backStep;
        cout << playerNames[turnNum] << " has gone over the winning square by" << overStep << " spaces." << endl;
        cout << "They have gone back " << overStep << " spaces to square " << playerSpace[turnNum] << "." << endl;
        output << playerNames[turnNum] << " has gone over the winning square by" << overStep << " spaces." << endl;
        output << "They have gone back " << overStep << " spaces to square " << playerSpace[turnNum] << "." << endl;
    }
    else{
        cout << playerNames[turnNum] << " has advanced " << cardVal << " spaces." << endl;
        cout << "They are now on square " << playerSpace[turnNum] << "." << endl;
        output << playerNames[turnNum] << " has advanced " << cardVal << " spaces." << endl;
        output << "They are now on square " << playerSpace[turnNum] << "." << endl;
    }
}

/*************************/
/*  moveBackwardFunction */
/*************************/
void PlayerInfo::moveBackward(int currentTurn, int obstMax, ofstream& output){
    int stepBack = rand() % obstMax + 1;
    if(playerSpace[currentTurn] - stepBack < 0){
        playerSpace[currentTurn] = 0;
        cout << playerNames[currentTurn] << " has gone back to space 0." << endl;
        output << playerNames[currentTurn] << " has gone back to space 0." << endl;
    }
    else{
    playerSpace[currentTurn] -= stepBack;
    cout << playerNames[currentTurn] << " has gone back " << stepBack << " spaces." << endl;
    cout << "They are now on square " << playerSpace[currentTurn] << "." << endl;
    output << playerNames[currentTurn] << " has gone back " << stepBack << " spaces." << endl;
    output << "They are now on square " << playerSpace[currentTurn] << "." << endl;
    }
}
/*************************/
/*  swapPlaces Function  */
/*************************/
void PlayerInfo::swapPlaces(int turnNumber, ofstream& output){
    int playerLoc[6] = {0, 1, 2, 3, 4, 5};
    int placeHolder;

    for(int outLoop = 0; outLoop < numOfPlayers; outLoop++){
        for(int inLoop = 0; inLoop < numOfPlayers - 1; inLoop++){
            if(playerSpace[playerLoc[inLoop]] < playerSpace[playerLoc[inLoop+1]]){
                placeHolder = playerLoc[inLoop];
                playerLoc[inLoop] = playerLoc[inLoop+1];
                playerLoc[inLoop+1] = placeHolder;
            }
        }
    }
    if(playerSpace[playerLoc[0]] > playerSpace[playerLoc[turnNumber]]){
        cout << "Swapping places with " << playerNames[playerLoc[0]] << "." << endl;
        output << "Swapping places with " << playerNames[playerLoc[0]] << "." << endl;
        placeHolder = playerSpace[turnNumber];
        playerSpace[turnNumber] = playerSpace[playerLoc[0]];
        playerSpace[playerLoc[0]] = placeHolder;
    }
    else{
        cout << "You are currently the farthest on the board." << endl;
        output << "You are currently the farthest on the board." << endl;
        }
    }
