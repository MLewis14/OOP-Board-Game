/*
 * Michael Lewis
 * mlewis
 * Section: EWQ6
 * HW #4
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

/***************************************************************/
//Class to store players names and their board locations
class playerInfo{
    public:
        int playerSpace;
        string playerName;
};
/***************************************************************/
//Class to store board assets and information such as cards and obstacles
class boardInfo{
    public:
        int cardPile[12];
        int drawnPile[12];
        int boardSize;
        int boardObstacles;
};
/***************************************************************/
//Displays the rules of the game
void displayRules(){
    cout << "Welcome to the GoHome! board game. This game may be played with 2 to 6 players." << endl;
    cout << "The objective is to reach the last square on the board. Each player will draw a card" << endl;
    cout << "on their turn and depending on the number on the card will either move forward that" << endl;
    cout << "amount of spaces or lose a turn. After drawing a card and moving the next player will" << endl;
    cout << "go and the process will repeat until someone wins the game." << endl << endl;
}
/***************************************************************/
//Prompts user for the amount of players in this game
int playerAmountPrompt(){
    int numOfPlayers;

    cout << "Please enter the amount of players. [2-6]" << endl;
    cin >> numOfPlayers;

    while(cin.fail() || numOfPlayers > 6 || numOfPlayers < 2){
        cout << "Invalid entry, Please enter a number between 2 and 6." << endl;
        cin.clear();
        cin.ignore();
        cin >> numOfPlayers;
    }
    cout << numOfPlayers << " players have been selected." << endl;
    return(numOfPlayers); //Returns the amount of players for this game
}
/***************************************************************/
int boardSetUp(boardInfo* &boardSet ){
    int boardSpaces;
    int numOfObstacles;

    cout << "How many spaces would you like there to be on the board?" << endl;
    cout << "Please enter a value between 20 and 100." << endl;
    cin >> boardSpaces;

    while(cin.fail() || boardSpaces < 20 || boardSpaces > 100){
        cout << "Invalid entry, Please enter a number between 20 and 100." << endl;
        cin.clear();
        cin.ignore();
        cin >> boardSpaces;
    }
}
/***************************************************************/
int* initializeGame(playerInfo* &pInfo, boardInfo* &bInfo){

    int playerSize = playerAmountPrompt();

    try{
        pInfo = new playerInfo[playerSize];
        for(int a = 0; a < playerSize; a++){
            cout << "Please enter player " << a + 1 << "'s name." << endl;
            cin >> *pInfo.playerName[a];
        }
        //Creates an array of player amount to store player
        //names and locations
    }
    catch(bad_alloc){
        cout << "Unable to allocate space, ending program." << endl;
        system("PAUSE");
    }
}
/***************************************************************/
//Checks whether or not the user wishes to begin a game, otherwise ends program
//Also Initializes the game board through initializeGame function if response is yes
int gameStartPrompt(){
    char response;
    int result; //Change or remove this variable if you need to

    cout << "Would you like to play? [Y/N]" << endl;
    cin >> response;
    //Checks userResponse for valid type input and accepted char input
    while(cin.fail() || (response != 'Y' && response != 'y' && response != 'N' && response != 'n')){
        cout << "Incorrect entry, Would you like to play? [Y/N]" << endl;
        cin.clear();
        cin.ignore();
        cin >> response;
    }
    if(response == 'Y' || response == 'y'){
        cout << "Beginning the game." << endl;
        result = playerAmountPrompt();

    }
    else if(response == 'N' || response == 'n'){
        cout << "Closing the game." << endl;
        result = 1;
    }
    return(result);
}
/***************************************************************/
int play(){
    playerInfo* playerData;
    boardInfo* boardData;

    initializeGame(playerData, boardData);
}
/***************************************************************/

int main(){
    int gameStartValue;

    displayRules(); //Displays the rules of the game
    gameStartValue = gameStartPrompt(); //Holds integer that determines if game starts

    if(gameStartValue == 1){
        cout << "Ending Program." << endl;
        return(0);
    }
    else{

    }
}
