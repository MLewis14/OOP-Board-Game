#include <cstdlib>
#include <iostream>
#include <fstream>
#include "GameInfo.h"

using namespace std;

/*************************/
/*  gamePrompt Function  */
/*************************/
void gameInfo::gamePrompt(){
    char response;

    cout <<"Would you like to start a game? [Y/N]" << endl;
    cin >> response;
    //Checks for valid input and prompts until acceptable parameters are entered
    while(cin.fail() || (response != 'Y' && response != 'y' && response != 'N' && response != 'n')){
        cout << "Invalid entry, Would you like to start a game? [Y/N]" << endl;
        cin.clear();
        cin.ignore();
        cin >> response;
    }
    if(response == 'Y' || response == 'y'){
        this->initializeGameAssets(); //Initializes board and player assets
        this->playGame(); //Plays through the game
    }
    else if(response == 'N' || response == 'n'){
        cout << "Closing the game." << endl;
        system("exit"); //exits the program
    }
}

/*************************/
/* initializeGameAssets  */
/*************************/
void gameInfo::initializeGameAssets(){
    playerData.setPlayers(); //Sets number of players and names
    boardData.initializeBoard(); //Sets boardSize, obstacles, bonus turns, etc.
}

/*************************/
/*   playGame Function   */
/*************************/
void gameInfo::playGame(){
    ofstream outfile("GameResults.txt"); //Opens output file stream
    int winCheck = 0;

    for(int playTurn = playerData.firstTurn; playTurn < playerData.numOfPlayers; playTurn++){
            winCheck = this->takeTurn(playTurn, outfile);
            if(winCheck == 1){
                cout << playerData.playerNames[playTurn] << " has won! Game Over!" << endl;
                outfile << playerData.playerNames[playTurn] << " has won! Game Over!" << endl;
                playTurn = playerData.numOfPlayers; //ends loop
            }
            else if(winCheck == 0 && playTurn == playerData.numOfPlayers - 1){
                playerData.printSpaces(); //Prints all player locations
                playTurn = -1; //Resets loop to go through all players
            }
    }
    outfile.close(); //Closes output files stream
}

/*************************/
/*   takeTurn Function   */
/*************************/
int gameInfo::takeTurn(int turn, ofstream& output){
    int drawnCard;
    int results = 0;
    int counter = 0;
    bool encounter = true;

    cardData.deckShuffle(); //Checks if deck is used up, shuffles if it is
    cout << "It is currently " << playerData.playerNames[turn] << "'s turn." << endl;
    output << "It is currently " << playerData.playerNames[turn] << "'s turn." << endl;
    drawnCard = cardData.drawCard(); //Draws a random card, function checks for drawnCards

    if(drawnCard == 0){
        cout << playerData.playerNames[turn] << " has drawn a 0 and lost a turn." << endl;
        output << playerData.playerNames[turn] << " has drawn a 0 and lost a turn." << endl;
        return(results); //ends turn and moves onto next player
    }
    else if(drawnCard == 10){
        cout << playerData.playerNames[turn] << " has earned a chance to swap places." << endl;
        output << playerData.playerNames[turn] << " has earned a chance to swap places." << endl;
        playerData.swapPlaces(turn, output); //Swaps with farthest player on board
    }
    else{
        cout << playerData.playerNames[turn] << " has drawn a " << drawnCard << "." << endl;
        output << playerData.playerNames[turn] << " has drawn a " << drawnCard << "." << endl;
        playerData.moveForward(turn, drawnCard, boardData.boardSize, output); //Moves player forward
    }
    cout << "Made it here" << endl;
    //This while loop allows the function to check if the player lands on another obstacle or
    //bonus turn space and keeps checking until the player lands on an empty board space
    while(encounter == true){
        counter = 0; //counter will check if the player hits an obstacle or bonus that may make it land on another
        for(int obstCheck = 0; obstCheck < boardData.numOfObsts; obstCheck++){
            if(playerData.playerSpace[turn] == boardData.obstacles[obstCheck]){
                cout << playerData.playerNames[turn] << " has encountered an obstacle." << endl;
                output << playerData.playerNames[turn] << " has encountered an obstacle." << endl;
                playerData.moveBackward(turn, boardData.maxObstSize, output);
                counter++;
            }
        }
        for(int bonusCheck = 0; bonusCheck < boardData.numOfBonus; bonusCheck++){
            if(playerData.playerSpace[turn] == boardData.bonusTurns[bonusCheck]){ //Checks if player lands on extra turn
                cout << playerData.playerNames[turn] << " has earned an extra turn." << endl;
                output << playerData.playerNames[turn] << " has earned an extra turn." << endl;
                this->takeTurn(turn, output); //Runs another turn on calling object
                counter++;
            }
        }
        for(int playerLand = 0; playerLand < playerData.numOfPlayers; playerLand++){
            if(playerData.playerSpace[turn] == playerData.playerSpace[playerLand] && turn != playerLand && playerData.playerSpace[turn] != 0){
                cout << playerData.playerNames[turn] << " has landed on " << playerData.playerNames[playerLand]
                     << "'s square." << playerData.playerNames[playerLand] << " has been sent back to square 0." << endl;
                output << playerData.playerNames[turn] << " has landed on " << playerData.playerNames[playerLand]
                     << "'s square." << playerData.playerNames[playerLand] << " has been sent back to square 0." << endl;
                playerData.playerSpace[playerLand] = 0; //Sends the player landed on back to square 0
            }
        }
        if(counter > 0){ //if the counter is greater than 0, the player may have backstepped onto an obstacle or bonus turn
            encounter = true; //the true value will restart the loop and check if this is true then take appropriate action
        }
        else if(counter <= 0){ //Otherwise if no obstacles or bonus turns have been landed on, the function continues
            encounter = false; //without repeating a check
        }
    }
    if(playerData.playerSpace[turn] == boardData.boardSize){ //Checks if player has landed on winning space
        cout << playerData.playerNames[turn] << " has landed on the winning square!" << endl;
        output << playerData.playerNames[turn] << " has landed on the winning square!" << endl;
        results = 1;
    }
    return(results);
}
