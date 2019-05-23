/* Name: Michael Lewis
 * Username: mlewis
 * Section: EWQ6
 * DueDate: Wednesday April 26, 2017
 * Assignment #7
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <string>
#include "GameAssets.h"

using namespace std;

/**************************************************/
//Displays the game rules
void displayRules(){
    cout << "Welcome to the GoHome! board game. This game may be played with 2 to 6 players." << endl;
    cout << "The objective is to reach the last square on the board. Each player will draw a card" << endl;
    cout << "on their turn and depending on the number on the card will either move forward that" << endl;
    cout << "amount of spaces or lose a turn. After drawing a card and moving the next player will" << endl;
    cout << "go and the process will repeat until someone wins the game." << endl << endl;
}
/**************************************************/
//Prompts user for whether or not they want to begin a game
int gamePrompt(){
    int result;
    char response;

    cout << "Would you like to start a game? [Y/N]" << endl;
    cin >> response;
    //Checks for valid input of type char within accepted parameters
    while(cin.fail() || (response != 'Y' && response != 'y' && response != 'N' && response != 'n')){
        cout << "Invalid entry, Would you like to start a game? [Y/N]" << endl;
        cin.clear(); //Clears the input stream
        cin.ignore();
        cin >> response;
    }
    if(response == 'Y' || response == 'y'){
        result = 1;
    }
    else if(response == 'N' || response == 'n'){
        result = 0;
    }
    return(result);
}
/**************************************************/
playerInfo* initializeGame(boardInfo &bData, cardInfo &cData, int &startTurn){
    playerInfo* playPtr;
    bData.playerPrompt(); //Gets the number of players and stores value in bData

    try{
        playPtr = new playerInfo[bData.getNumOfPlayers()]; //Makes an array of playerInfo
        for(int a = 0; a < bData.getNumOfPlayers(); a++){
            playPtr[a].setPlayerName(a+1); //Sets the names for each player in the array
        }
        bData.initializeBoard(); //Sets up the boards obstacles and extra spaces
        startTurn = bData.firstTurn(playPtr);
    }
    catch(bad_alloc){ //Catches bad memory allocation and closes program
        cout << "Unable to allocate space. Closing Program." << endl;
        system("exit"); //exits out of program
    }
    return(playPtr);
}
/**************************************************/
void swapPlaces(playerInfo* &playersDat, boardInfo &boardsDat, int currentTurn, ofstream &output){
    int placeHold;
    int pLocations[6] = {0, 1, 2, 3, 4, 5};

    for(int m = 0; m < boardsDat.getNumOfPlayers(); m++){
        for(int n = 0; n < boardsDat.getNumOfPlayers() - 1; n++){
            if(playersDat[pLocations[n]].getPlayerSpace() < playersDat[pLocations[n+1]].getPlayerSpace()){
                placeHold = pLocations[n];
                pLocations[n] = pLocations[n+1];
                pLocations[n+1] = placeHold;
            }
        }
    }
    if(playersDat[pLocations[0]].getPlayerSpace() > playersDat[currentTurn].getPlayerSpace()){
        cout << "Swapping places with " << playersDat[pLocations[0]].getName() << "." << endl;
        placeHold = playersDat[currentTurn].getPlayerSpace();
        playersDat[currentTurn].setPlayerSpace(playersDat[pLocations[0]].getPlayerSpace());
        playersDat[pLocations[0]].setPlayerSpace(placeHold);
    }
    else{
        cout << "No players are ahead of you. Unable to swap spaces." << endl;
        output << "No players are ahead of you. Unable to swap spaces." << endl;
    }
}
/**************************************************/
int takeTurn(playerInfo* &playerD, boardInfo &boardD, cardInfo &cardD, int turnNumber, ofstream &output){
    int results = 0;
    int drawnCard, stepBack;

    cardD.shuffleDeck(); //Checks if deck is used up, shuffles if it is
    cout << "It is currently " << playerD[turnNumber].getName() << "'s turn." << endl;
    output << "It is currently " << playerD[turnNumber].getName() << "'s turn." << endl;
    drawnCard = cardD.drawCard();

    if(drawnCard == 0){
        cout << playerD[turnNumber].getName() << " has drawn a 0 and has lost a turn." << endl;
        output << playerD[turnNumber].getName() << " has drawn a 0 and has lost a turn." << endl;
        return(results); //Ends turn
    }
    else if(drawnCard == 10){
        cout << playerD[turnNumber].getName() << " has earned a chance to swap places." << endl;
        output << playerD[turnNumber].getName() << " has earned a chance to swap places." << endl;
        swapPlaces(playerD, boardD, turnNumber, output);
    }
    else{
        playerD[turnNumber].moveForward(drawnCard, boardD.getBoardSize(), output);
    }
    for(int g = 0; g < boardD.getNumObsts(); g++){
        if(playerD[turnNumber].getPlayerSpace() == boardD.getObstacles(g)){
            stepBack = rand() % boardD.getObstSize() + 1;
            playerD[turnNumber].moveBackward(stepBack, output);
        }
    }
    for(int j = 0; j < boardD.getNumAgain(); j++){
        if(playerD[turnNumber].getPlayerSpace() == boardD.getGoAgain(j)){
            cout << playerD[turnNumber].getName() << " has earned an extra turn!" << endl;
            output << playerD[turnNumber].getName() << " has earned an extra turn!" << endl;
            cardD.shuffleDeck();
            drawnCard = cardD.drawCard();
            if(drawnCard == 0){
                cout << playerD[turnNumber].getName() << " has drawn a 0 and has lost a turn." << endl;
                output << playerD[turnNumber].getName() << " has drawn a 0 and has lost a turn." << endl;
                return(results); //Ends turn
            }
            else if(drawnCard == 10){
                cout << playerD[turnNumber].getName() << " has earned a chance to swap places." << endl;
                output << playerD[turnNumber].getName() << " has earned a chance to swap places." << endl;
                swapPlaces(playerD, boardD, turnNumber, output);
            }
            else{
                playerD[turnNumber].moveForward(drawnCard, boardD.getBoardSize(), output);
            }
        }
     }
     for(int q = 0; q < boardD.getNumOfPlayers(); q++){
        if(playerD[turnNumber].getPlayerSpace() == playerD[q].getPlayerSpace() && q != turnNumber){
            cout << playerD[turnNumber].getName() << " has landed on " << playerD[q].getName() << "'s spot." << endl;
            cout << playerD[q].getName() << " has been sent back to square 0." << endl;
            output << playerD[turnNumber].getName() << " has landed on " << playerD[q].getName() << "'s spot." << endl;
            output << playerD[q].getName() << " has been sent back to square 0." << endl;
            playerD[q].setPlayerSpace(0);
        }
     }

     if(playerD[turnNumber].getPlayerSpace() == boardD.getBoardSize()){
        cout << playerD[turnNumber].getName() << " has landed on the winning square!" << endl;
        output << playerD[turnNumber].getName() << " has landed on the winning square!" << endl;
        results = 1;
     }
    return(results);
}
/**************************************************/
void showStates(playerInfo* playerStuff, boardInfo boardStuff, ofstream &output){
    for(int v = 0; v < boardStuff.getNumOfPlayers(); v++){
        cout << playerStuff[v].getName() << " is on space " << playerStuff[v].getPlayerSpace() << "." << endl;
        output << playerStuff[v].getName() << " is on space " << playerStuff[v].getPlayerSpace() << "." << endl;
    }
}
/**************************************************/
int play(){
    srand(time(NULL));

    ofstream outfile("GameResults.txt");
    playerInfo* playerPtr;
    boardInfo boardData;
    cardInfo cardData;
    int winCheck, firstPlay, players;

    playerPtr = initializeGame(boardData, cardData, firstPlay);
    players = boardData.getNumOfPlayers();
    cardData.getCardValues();
    cout << "There are " << players << " players." << endl;
    for(int turn = firstPlay; turn < players; turn++){
        cout << "Hi, this is turn " << turn << endl;
        outfile << "Hi, this is turn " << turn << endl;
        winCheck = takeTurn(playerPtr, boardData, cardData, turn, outfile);
        if(winCheck == 1){
        cout << playerPtr[turn].getName() << " has won. Game Over!" << endl;
        turn = boardData.getNumOfPlayers();
        }
        else if(winCheck == 0 && turn == boardData.getNumOfPlayers() - 1){
                showStates(playerPtr, boardData, outfile);
                turn = -1;
            }
        }
        outfile.close();
    return(0);
}
/**************************************************/
int main()
{
    int promptResult;

    displayRules();
    promptResult = gamePrompt();

    if(promptResult == 0){
        cout << "Closing the game." << endl;
        system("exit");
    }
    else if(promptResult == 1){
        cout << "Starting up the game." << endl;
        play();
    }
    return(0);
}
