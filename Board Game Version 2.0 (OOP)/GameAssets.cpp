#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <ctime>
#include "GameAssets.h"

using namespace std;

/************************* playerInfo member Functions ************************/
//Initializes playerSpaces
playerInfo::playerInfo(){
    playerSpace = 0;
    cout << "Player Space Initialized to 0." << endl;
}
//Allows player space to be changed in swapSpaces function
void playerInfo::setPlayerSpace(int newSpot){
    playerSpace = newSpot;
}
//Allows playerNames to be set upon game initialization
void playerInfo::setPlayerName(int playerNum){
        cout << "Please enter player " << playerNum << "'s name." << endl;
        cin >> cNames;
        cout << "Player " << playerNum << " is " << cNames << "." << endl;
}
//Adds the value of drawnCard to current playerSpace
void playerInfo::moveForward(int cardValue, int maxSpaces, ofstream &output){
    playerSpace += cardValue;
    if(playerSpace > maxSpaces){
        int overStep = playerSpace - maxSpaces;
        int backStep = maxSpaces - overStep;
        playerSpace = backStep;
        cout << cNames << " has gone over the winning square by " << overStep << "." << endl;
        cout << cNames << " has gone back " << overStep << " spaces to square " << backStep << "." << endl;
        output << cNames << " has gone over the winning square by " << overStep << "." << endl;
        output << cNames << " has gone back " << overStep << " spaces to square " << backStep << "." << endl;
    }
    else if(playerSpace <= maxSpaces){
    cout << cNames << " has advanced " << cardValue << " spaces." << endl;
    cout << cNames << " is now on board space " << playerSpace << "." << endl;
    output << cNames << " has advanced " << cardValue << " spaces." << endl;
    output << cNames << " is now on board space " << playerSpace << "." << endl;
    }
}
//Subtracts the obstacle amount from playerSpace
void playerInfo::moveBackward(int goBack, ofstream &output){
    playerSpace -= goBack;

    if(playerSpace < 0){
        playerSpace = 0;
        cout << cNames << " is now on space 0." << endl;
        output << cNames << " is now on space 0." << endl;
    }
}
//Returns the players Name
char* playerInfo::getName(){
    return(cNames);
}
//Returns the players board space
int playerInfo::getPlayerSpace(){
    return(playerSpace);
}
/************************* boardInfo member Functions *************************/
//Prompts user for number of players then sets the value
void boardInfo::playerPrompt(){
    int numPlayers;

    cout << "Please enter the number of players. [2-6]" << endl;
    cin >> numPlayers;
    //While loop checks for any invalid input and prompts for valid input
    while(cin.fail() || numPlayers < 2 || numPlayers > 6){
        cout << "Invalid entry, Please enter a number between 2 and 6." << endl;
        cin.clear();
        cin.ignore();
        cin >> numPlayers;
    }
    numOfPlayers = numPlayers;
    cout << "You have selected " << numOfPlayers << " players for this game." << endl;

}
//Prompts the user for obstacles and extra turns then sets values
void boardInfo::initializeBoard(){
    int boardCapacity, obstacleCapacity, extraTurnCapacity, largestObst;
    cout << "Please enter the number of spaces you would like on the board." << endl;
    cout << "You may pick a number between 20 and 100." << endl;
    cin >> boardCapacity;
    while(cin.fail() || boardCapacity > 100 || boardCapacity < 20){
        cout << "Error, please enter a number between 20 and 100." << endl;
        cin.clear();
        cin.ignore();
        cin >> boardCapacity;
    }
    boardSize = boardCapacity;
    cout << "This board will have " << boardSize << " spaces." << endl;
    cout << "How many obstacles would you like on the board?" << endl;
    cout << "You may pick a value between 7 and 12." << endl;
    cin >> obstacleCapacity;
    while(cin.fail() || obstacleCapacity < 7 || obstacleCapacity > 12){
        cout << "Invalid entry, please enter a value between 7 and 12." << endl;
        cin.clear();
        cin.ignore();
        cin >> obstacleCapacity;
    }
    numObsts = obstacleCapacity;
    obstacles.resize(numObsts);
    cout << "There will be " << obstacleCapacity << " obstacles on the board." << endl;
    for(int obstFill = 0; obstFill < numObsts; obstFill++){
            obstacles[obstFill] = rand() % (boardSize - 1) + 1;
            cout << "Obstacle " << obstFill + 1 << " is located on space " << obstacles[obstFill] << "." << endl;
    }
    cout << "What would you like the largest obstacle to be? You may choose a value between 1 and 5." << endl;
    cin >> largestObst;
    while(cin.fail() || largestObst > 5 || largestObst < 1){
        cout << "Invalid entry, please enter a value between 1 and 5." << endl;
        cin.clear();
        cin.ignore();
        cin >> largestObst;
    }
    obstSize = largestObst; //Sets the largest possible obstacle size
    cout << "How many extra turn spaces would you like on the board?" << endl;
    cout << "You may enter a value between 1 and 3." << endl;
    cin >> extraTurnCapacity;
    while(cin.fail() || extraTurnCapacity < 1 || extraTurnCapacity > 3){
        cout << "Invalid entry, please enter a value between 1 and 3." << endl;
        cin.clear();
        cin.ignore();
        cin >> extraTurnCapacity;
    }
    numAgain = extraTurnCapacity; //Sets the number of extra turns on the board
    goAgain.resize(numAgain); //Resizes vector to amount of extra turn spaces
    for(int againFill = 0; againFill < numAgain; againFill++){
        goAgain[againFill] = rand() % (boardSize - 1) + 1;
    }
}

int boardInfo::firstTurn(playerInfo* playerDatum){
    int playerHold[6] = {0, 1, 2, 3, 4, 5};
    int spotHold;

    //Sorts playerHold array and puts num of player with shortest name at the top
    for(int e = 0; e < numOfPlayers; e++){
            for(int f = 0; f < numOfPlayers - 1; f++){
                if(strlen(playerDatum[playerHold[f]].getName()) > strlen(playerDatum[playerHold[f+1]].getName())){
                        spotHold = playerHold[f];
                        playerHold[f] = playerHold[f+1];
                        playerHold[f+1] = spotHold;
                }
            }
        }
    cout << "The first player will be " << playerDatum[playerHold[0]].getName() << "." << endl;
    return(playerHold[0]);
}

int boardInfo::getNumOfPlayers(){
    return(numOfPlayers);
}

int boardInfo::getBoardSize(){
    return(boardSize);
}

int boardInfo::getNumObsts(){
    return(numObsts);
}

int boardInfo::getObstSize(){
    return(obstSize);
}

int boardInfo::getNumAgain(){
    return(numAgain);
}

int boardInfo::getObstacles(int obstNum){
    return(obstacles[obstNum]);
}

int boardInfo::getGoAgain(int goAgainNum){
    return(goAgain[goAgainNum]);
}
/****************** cardInfo Functions ******************************/
cardInfo::cardInfo(){
//Initializes all card values so the initializeGame function in main.cpp
//does not have to
    for(int x = 0; x < 12; x++){
        cardPile[x] = rand() % 9 + 1;
        drawnPile[x] = 0;
    }
    cardPile[rand() % 12 + 0] = 0;
    cardPile[rand() % 12 + 0] = 10;
}
void cardInfo::getCardValues(){
    for(int w = 0; w < 12; w++){
        cout << "Card " << w + 1 << " is " << cardPile[w] << "." << endl;
    }
}
/************************* drawCard Function *************************/
int cardInfo::drawCard(){
    srand(time(NULL));
    int randomDraw = rand() % 12 + 0;

    while(drawnPile[randomDraw] == 1){
        randomDraw = rand() % 12 + 0;
    }
    drawnPile[randomDraw] = 1;
    return(cardPile[randomDraw]);
}
/************************* shuffleDeck Function *************************/
void cardInfo::shuffleDeck(){
    srand(time(NULL));
    int drawnCards = 0;

    for(int z = 0; z < 12; z++){ //Checks if all cards have been used once
        if(drawnPile[z] == 1){
            drawnCards++;
        }
    }
    if(drawnCards == 12){ //Resets all cards with random values
        for(int y = 0; y < 12; y++){
            cardPile[y] = rand() % 9 + 1;
            drawnPile[y] = 0;
        }
    }
    cardPile[rand() % 12 + 0] = 0;
    cardPile[rand() % 12 + 0] = 10;
}

