/*
 * Michael Lewis
 * Mlewis14
 * Section: EWQ6
 * HW Assignment #3
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

/********************************************************************************/
//Class to store players names and board locations
class playerInfo{
    public:
        int playerSpace[6];
        string playerName[6];
};
/********************************************************************************/
//class that holds board assets information such as cards and board obstacles
class boardInfo{
    public:
        int cardPile[12];
        int drawnPile[12];
        int boardSize;
        int boardObstacles[7];
};
/********************************************************************************/
//Displays the rules of the game
void displayRules(){
    cout << "Welcome to the GoHome! board game. This game may be played with 2 to 6 players." << endl;
    cout << "The objective is to reach the last square on the board. Each player will draw a card" << endl;
    cout << "on their turn and depending on the number on the card will either move forward that" << endl;
    cout << "amount of spaces or lose a turn. After drawing a card and moving the next player will" << endl;
    cout << "go and the process will repeat until someone wins the game." << endl << endl;
}
/********************************************************************************/
//gets the amount of players and returns it to the gamePrompt function
int playerAmount(ofstream &output){
    int numOfPlayers;

    cout << "Please enter the amount of players. [2-6]" << endl;
    cin >> numOfPlayers;
    //Checks for incorrect data type or integer value and loops until valid input
    if(cin.fail() || numOfPlayers > 6 || numOfPlayers < 2){
        while(cin.fail() || numOfPlayers > 6 || numOfPlayers < 2){
            cout << "Error, Please enter a number between 2 and 6." << endl;
            cin.clear();
            cin.ignore();
            cin >> numOfPlayers;
        } //Loops around until a valid int between 2 and 6 is entered
    }
            cout << numOfPlayers << " players have been selected." << endl;
            output << numOfPlayers << " players have been selected." << endl;
            return(numOfPlayers); //returns the maximum amount of players that will be
            //playing for this game
}
/********************************************************************************/
//Checks to see if user wants to begin a game and returns amount of players, otherwise ends program
int gamePrompt(ofstream &output){
    char response;
    int result;

        cout << "Would you like to play? [Y/N]" << endl;
        cin >> response;
        //Checks to make sure response is a char input and one of the valid char inputs
        if(cin.fail() || (response != 'Y' && response != 'y' && response != 'N' && response != 'n')){
                while(cin.fail() || (response != 'Y' && response != 'y' && response != 'N' && response != 'n')){
                    cout << "Error, Would you like to play? [Y/N]" << endl;
                    cin.clear();
                    cin.ignore();
                    cin >> response;
                }   //Loops around until one of the valid chair inputs is entered
        }
        if(response == 'Y' || response == 'y'){
            cout << "Beginning The Game." << endl;
            result = playerAmount(output); //A value of 0 proceeds to play the game
        }
        else if(response == 'N' || response == 'n'){
                cout << "Closing The Game." << endl;
                    result = 1; //A value of 1 closes out the game
        }

    return(result); //Sends result back to main function to determine
}   //Whether or not to start or close the game
/********************************************************************************/
//Starts setting up the board size, shuffles the deck, and determines which player goes first
int initializeGame(int playerNums, playerInfo &playerData, boardInfo &boardData, ofstream &output){
    const int maxSize = rand()% 29 + 20;
    int placeHolder[6] = {0, 1, 2, 3, 4, 5}; //Holds the 6 spots for each players name length
    int spotHolder;

    boardData.boardSize = maxSize;

    for(int a = 0; a < playerNums; a++){
        cout << "Please enter player " << a + 1 << "'s name." << endl;
        cin >> playerData.playerName[a];
        cout << "Player " << a + 1 << " is " << playerData.playerName[a] << endl;
        output << "Player " << a + 1 << " is " << playerData.playerName[a] << endl;
        playerData.playerSpace[a] = 0;
    }
    for(int b = 0; b < 12; b++){ //Initializes a set of 12 cards
        boardData.cardPile[b] = rand() % 8 + 1; //Gives the cards random values between 1 and 6
        boardData.drawnPile[b] = 0; //Parallel array for telling which cards are used up
    }//A value of 0 means it hasn't been drawn and 1 means it has been drawn
    boardData.cardPile[rand()% 12 + 0] = 0; //Sets one card to lose a turn
    boardData.cardPile[rand()% 12 + 0] = 10; //Sets one card to swap places
    for(int c = 0; c < 7; c++){ //Sets up 7 obstacles across the board
        boardData.boardObstacles[c] = rand()% maxSize - 1 + 1;
    }
    for(int d = 0; d < playerNums; d++){
        for(int e = 0; e < playerNums - 1; e++){
            if(playerData.playerName[placeHolder[e]].length() > playerData.playerName[placeHolder[e+1]].length()){
                    spotHolder = placeHolder[e]; //Holds player name array number
                    placeHolder[e] = placeHolder[e+1]; //Moves Player number up array
                    placeHolder[e+1] = spotHolder; //Moves Player number down array
            }   //placeHolder holds the number associated with a players name in each spot
        }       //As the for loop progresses, if a player with a name in the spot held by placeHolder
    }           //is larger than the name in the spot held by placeHolder + 1, the location is moved
                //up by 1, basically placeHolder is equal to the playerName array
    cout << "The card pile has been shuffled." << endl;
    cout << "This Board has " << boardData.boardSize << " spaces." << endl;
    //cout << "The first player will be " << playerData.playerName[placeHolder[0]] << "." << endl; - was an error check
    output << "The card pile has been shuffled." << endl;
    output << "This Board has " << boardData.boardSize << " spaces." << endl;
    output << "The first player will be " << playerData.playerName[placeHolder[0]] << "." << endl;

    return(placeHolder[0]);
}
/********************************************************************************/
//Checks if all cards have been drawn and shuffles deck if it has
void shuffleStatus(boardInfo &cardStatus, ofstream &output){
    int drawnCards = 0;

    for(int f = 0; f < 12; f++){ //
        if(cardStatus.drawnPile[f] == 1){
            drawnCards += 1;
        }
    }
    cout << drawnCards  << " out of 12 cards have been used." << endl;
    if(drawnCards == 12){
        cout << "The card pile has been used up, Shuffling Deck." << endl;
        for(int g = 0; g < 12; g++){
            cardStatus.cardPile[g] = rand()% 9 + 0;
            cardStatus.drawnPile[g] = 0;
        }
        cardStatus.cardPile[rand()% 12 + 0] = 0; //Sets one card to lose a turn
        cardStatus.cardPile[rand()% 12 + 0] = 10; //Sets one card to swap spaces
    }
}
/********************************************************************************/
//Swaps current players spot with farthest player on the board
void swapPlaces(playerInfo &pInfo, boardInfo &bInfo, int pTurn, int pNums, ofstream &output){
    const int maxpSize = 6;
    int pLocations[maxpSize] = {0, 1, 2, 3, 4, 5}, locationHold, playerHolder;
    //pLocations holds each players number from 0 to 5 (aka players 1 through 6)
    //In this nested for loop the players number is passed to the playerSpace array
    //and the loop determines if player x is on a larger spot than y. If that is true
    //player x moves up 1 in the array and y moves down 1 until the array is sorted top to
    //bottom from largest to smallest
    for(int x = 0; x < pNums; x++){
            for(int y = 0; y < pNums - 1; y++){
                if(pInfo.playerSpace[pLocations[y]] < pInfo.playerSpace[pLocations[y+1]]){
                    locationHold = pLocations[y];
                    pLocations[y] = pLocations[y+1];
                    pLocations[y+1] = locationHold;
                }
            }
    }
    //0 is used with pLocations because it is the beginning of the array, and after sorting has
    //the largest player board space value
    if(pInfo.playerSpace[pLocations[0]] > pInfo.playerSpace[pTurn]){
        cout << "Swapping places with player " << pInfo.playerName[pLocations[0]] << "." << endl;
        output << "Swapping places with player " << pInfo.playerName[pLocations[0]] << "." << endl;
        playerHolder = pInfo.playerSpace[pLocations[0]];
        pInfo.playerSpace[pLocations[0]] = pInfo.playerSpace[pTurn];
        pInfo.playerSpace[pTurn] = playerHolder;
        cout << pInfo.playerName[pLocations[0]] << " is now on space " << pInfo.playerSpace[pLocations[0]] << "." << endl;
        cout << pInfo.playerName[pTurn] << " is now on space " << pInfo.playerSpace[pTurn] << endl;
        output << pInfo.playerName[pLocations[0]] << " is now on space " << pInfo.playerSpace[pLocations[0]] << "." << endl;
        output << pInfo.playerName[pTurn] << " is now on space " << pInfo.playerSpace[pTurn] << endl;
    }
    else{
        cout << "There are no players ahead of you, unable to swap places." << endl;
        output << "There are no players ahead of you, unable to swap places." << endl;
    }
}
/********************************************************************************/
int taketurn(boardInfo &gameStatus, playerInfo &playerDetail, int turnNum, int playerNums, ofstream &output){
    int cardNum = rand()% 12 + 0;
    int backTrack, overStep;

    if(gameStatus.drawnPile[cardNum] == 1){ //Checks to see it the currently picked card has already been drawn
        while(gameStatus.drawnPile[cardNum] == 1){ //If so, it keeps picking a random number until a card
            cardNum = rand()% 12 + 0;          //that hasn't been used is chosen
        }
    }
    cout << playerDetail.playerName[turnNum] << " has drawn a " << gameStatus.cardPile[cardNum] << "." << endl;
    output << playerDetail.playerName[turnNum] << " has drawn a " << gameStatus.cardPile[cardNum] << "." << endl;
    if(gameStatus.cardPile[cardNum] == 0){ //Checks to see if the player loses a turn
        gameStatus.drawnPile[cardNum] = 1;
        cout << "You lose a turn." << endl;
        output << "You lose a turn." << endl;
    }
    else if(gameStatus.cardPile[cardNum] == 10){ //Checks to see if the player can swap places
        gameStatus.drawnPile[cardNum] = 1;
        cout << "Swapping places with the player furthest ahead." << endl;
        output << "Swapping places with the player furthest ahead." << endl;
        swapPlaces(playerDetail, gameStatus, turnNum, playerNums, output);
    }
    else{
    playerDetail.playerSpace[turnNum] += gameStatus.cardPile[cardNum]; //Adds card value to players board spaces
    gameStatus.drawnPile[cardNum] = 1; //Adds the picked up card to the drawn pile
    cout << playerDetail.playerName[turnNum] << " has advanced " << gameStatus.cardPile[cardNum] << " spaces." << endl;
    cout << playerDetail.playerName[turnNum] << " is now on space " << playerDetail.playerSpace[turnNum] << "." << endl;
    output << playerDetail.playerName[turnNum] << " has advanced " << gameStatus.cardPile[cardNum] << " spaces." << endl;
    output << playerDetail.playerName[turnNum]<< " is now on space " << playerDetail.playerSpace[turnNum] << "." << endl;
    }

    if(playerDetail.playerSpace[turnNum] > gameStatus.boardSize){ //Checks to see if player went over the winning space
        overStep = playerDetail.playerSpace[turnNum] - gameStatus.boardSize; //gets the amount of spaces stepped over win
        playerDetail.playerSpace[turnNum] = gameStatus.boardSize - overStep; //Subtracts overstep from winning space
        cout << playerDetail.playerName[turnNum] << " skipped over " << overStep << " spaces." << endl;
        cout << playerDetail.playerName[turnNum] <<" has gone back to space " << playerDetail.playerSpace[turnNum] << "." << endl;
        output << playerDetail.playerName[turnNum] << " skipped over " << overStep << " spaces." << endl;
        output << playerDetail.playerName[turnNum] <<" has gone back to space " << playerDetail.playerSpace[turnNum] << "." << endl;
    }

    for(int h = 0; h < playerNums; h++){ //Checks to see if player landed on a spot shared by another player then
        if(playerDetail.playerSpace[turnNum] == playerDetail.playerSpace[h] && turnNum != h){ //sends the other player back to spot 0
            playerDetail.playerSpace[h] = 0;
            cout << playerDetail.playerName[turnNum] << " has landed on " << playerDetail.playerName[h] << "'s spot." << endl;
            cout << playerDetail.playerName[h] << " has been sent back to the beginning." << endl;
        }
    }
    for(int i = 0; i < 7; i++){ //Checks to see if the player has encountered an obstacle
        if(playerDetail.playerSpace[turnNum] == gameStatus.boardObstacles[i]){
            cout << "You have encountered an obstacle." << endl;
            output << "You have encountered an obstacle." << endl;
            backTrack = rand()% 3 + 1; //Sends the player back a random amount between 1 and 3 spaces
            playerDetail.playerSpace[turnNum] -= backTrack;
            cout << playerDetail.playerName[turnNum] << " has gone back to space " << playerDetail.playerSpace[turnNum] << endl;
            output << playerDetail.playerName[turnNum] << " has gone back to space " << playerDetail.playerSpace[turnNum] << endl;
            for(int j = 0; j < playerNums; j++){ //Checks to see if you land on a shared space after encountering an obstacle
                if(playerDetail.playerSpace[turnNum] == playerDetail.playerSpace[j] && turnNum != j){
                    playerDetail.playerSpace[j] = 0;
                }
            }
        }
    }
    shuffleStatus(gameStatus, output); //Checks the status of drawn and available cards every turn
}
/********************************************************************************/
//Lists all current player locations on the board
void showState(int playAmount, playerInfo pData){
    for(int y = 0; y < playAmount; y++){
        cout << pData.playerName[y] <<" is currently on space " << pData.playerSpace[y] << "." << endl;
    }
}
/********************************************************************************/
//Plays through the game
int play(int amountOfPlay, ofstream &output){

    srand(time(NULL)); //Initializes the rand() function to provide more randomlike outputs
    playerInfo playerStatus; //Creates an object of playerInfo class to store player info
    boardInfo boardStatus; //Creates an object of boardInfo to store Board's Assets
    int initialTurn;


    initialTurn = initializeGame(amountOfPlay, playerStatus, boardStatus, output);
    cout << "Testing. There are: " << amountOfPlay << " players." << endl;
    cout << "the first player will be " << initialTurn + 1;
    for(int turnStart = initialTurn; turnStart < amountOfPlay; turnStart++){
        taketurn(boardStatus, playerStatus, turnStart, amountOfPlay, output);
        for(int z = 0; z < amountOfPlay; z++){
            if(playerStatus.playerSpace[z] == boardStatus.boardSize){
                cout << playerStatus.playerName[z] << " has reached the end of the board!" << endl;
                cout << "Game Over!" << endl;
                output << playerStatus.playerName[z] << " has reached the end of the board!" << endl;
                output << "Game Over!" << endl;
                turnStart = amountOfPlay;
            }
        }
        if(turnStart == amountOfPlay - 1){
             turnStart = -1;
             showState(amountOfPlay, playerStatus); //Displays all current player locations
        }
    }
        return(0); //Ends play function to return back to main then end program
}
/********************************************************************************/
//Runs the prompt and subsequently the play function if prompt is answered with yes
int main(){
    int promptValue;
    ofstream outfile("BoardGameResults3.txt");

    displayRules();
    promptValue = gamePrompt(outfile);

    if(promptValue == 1){
        return(0);
    }
    else{
        play(promptValue, outfile);
        outfile.close(); //Closes output file stream
        return(0); //Ends program
    }
}
