#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

/**********************************************************************************************************/
						/* Michael Lewis */
/**********************************************************************************************************/
//Displays the rules of the game before prompting user
void displayRules(ofstream &outputfile){
    cout << "Welcome to the GoHome! board game. This game may be played with 2 to 4 players." << endl;
    cout << "The objective is to reach or pass the last square on the board. Each player will draw" << endl;
    cout << "a card on their turn and depending on the number on the card will either move forward" << endl;
    cout << "that amount of spaces or lose a turn. After drawing a card and moving the next player" << endl;
    cout << "will go and the process will repeat until someone wins the game." << endl << endl;

    outputfile << "Welcome to the GoHome! board game. This game may be played with 2 to 4 players." << endl;
    outputfile << "The objective is to reach or pass the last square on the board. Each player will draw" << endl;
    outputfile << "a card on their turn and depending on the number on the card will either move forward" << endl;
    outputfile << "that amount of spaces or lose a turn. After drawing a card and moving the next player" << endl;
    outputfile << "will go and the process will repeat until someone wins the game." << endl << endl;
}
/*********************************************************************************************************/
//Checks to see if user wants to begin a game and returns amount of players, otherwise ends program - Change this to an int function
int gamePrompt(){
char val;

cout << "Would you like to play? [Y/N]" << endl;
cin >> val;

if(val == 'Y' || val == 'y'){
    cout << "Beginning The Game" << endl;
    return(0);
}
else if(val == 'N' || val == 'n'){
    cout << "Closing The Game" << endl;
    return(1);
}
else{ //Checks to see if input is a nonvalid entry and keeps in loop until a proper entry is input
    while(val != 'N' || val != 'n' || val != 'y' || val != 'Y'){
        cout << "Invalid Input, Would you like to play? [Y/N]" << endl;
        cin >> val;
        if(val == 'Y' || val == 'y'){
            cout << "Beginning The Game" << endl;
            return(0); //Value of 0 will start the play function in main function
            }
        else if(val == 'N' || val == 'n'){
            cout << "Closing The Game" << endl;
            return(1); //Value of 1 will cause main function to return 0 ending program
            }
        }
    }
}
/**********************************************************************************************************/
//Asks for the amount of players then returns the value to be used in the play and other subsequent functions
int playerNum(ofstream &outputfile){
int players;

cout << "Please enter the amount of players. [2-4]" << endl;
cin >> players;
if(players <= 4 && players >= 2){ //Makes sure input is between minimum of 2 and maximum of 4 players
        cout << players << " Players have been selected." << endl;
        outputfile << players << " Players have been selected." << endl;
        return(players); //Returns amount of players in this game to be passed on to play function
}
else if(players < 2 || players > 4){ //Checks for a valid numerical input or keeps in loop until valid entry
        while(players < 4 && players > 2){
            cout << "Invalid entry, Please select a number between 2 and 4." << endl;
            cin >> players;
            if(players <= 4 && players >= 2){
                cout << players << " Players have been selected." << endl;
                outputfile << players << " Players have been selected." << endl;
                return(players);

            }

        }

    }
}
/**********************************************************************************************************/
//Draws a card to determine where the player will move on the board
void checkShuffle(int cardDeck[], int drawnDeck[]){
int deckCheck = 1;
cout << "Running deck check." << endl;
for(int t = 0; t <= 12; t++){
    if(drawnDeck[t] == 1){
        deckCheck++;
        }
    }
cout << deckCheck << " Cards have been used up" << endl;
 if(deckCheck == 12){
        cout << "The Card Pile has been used up, Shuffling Deck." << endl;
    for(int u = 0; u < 12; u++){
        cardDeck[u] = rand() % 5 + 1;
        drawnDeck[u] = 0;
    }
    cout << "Deck has been shuffled." << endl;
    }


}

/**********************************************************************************************************/

void swapPlaces(int turnNum, int playerLocation[], string players[], int playerAmount, ofstream &outputfile){

int playerpos, placeHold;

cout << "You've earned a chance to swap places!" << endl;
outputfile << "You've earned a chance to swap places!" << endl;
cout << "Enter the number of the player you want to swap places with." << endl;
cin >> playerpos;
if(playerpos > playerAmount || playerpos < 0){
    while(playerpos > playerAmount || playerpos < 0){
        cout << "Invalid Entry, Please choose a player between 1 and " << playerAmount << "." << endl;
        cin >> playerpos;
    }
}
placeHold = playerLocation[playerpos-1];
playerLocation[playerpos-1] = playerLocation[turnNum];
playerLocation[turnNum] = placeHold;
cout << players[turnNum] << " and " << players[playerpos-1] << " have swapped places." << endl;
cout << players[turnNum] << " is now on space " << playerLocation[turnNum] << "." << endl;
cout << players[playerpos-1] << " is now on space " << playerLocation[playerpos-1] << "." << endl;
outputfile << players[turnNum] << " and " << players[playerpos-1] << " have swapped places." << endl;
outputfile << players[turnNum] << " is now on space " << playerLocation[turnNum] << "." << endl;
outputfile << players[playerpos-1] << " is now on space " << playerLocation[playerpos-1] << "." << endl;
}

/**********************************************************************************************************/
//Goes through a turn for a player
void taketurn(int playTurn, string playName[],int position[], int boardObstacle[], int cards[], int drawn[], int numOfPlay, ofstream &outputfile){

int cardHolder, goBack;
cout << playTurn << endl;
cout << "It is " << playName[playTurn] << "'s turn." << endl;
outputfile << "It is " << playName[playTurn] << "'s turn." << endl;
cardHolder = rand() % 11 + 0;

checkShuffle(cards, drawn);
if(drawn[cardHolder] == 1){
    while(drawn[cardHolder] == 1){
        cardHolder = rand() % 11 + 0;
    }
}
position[playTurn] += cards[cardHolder];
drawn[cardHolder] = 1;
cout << playName[playTurn] << " has drawn a " << cards[cardHolder] << "." << endl;
cout << playName[playTurn] << " has advanced " << cards[cardHolder] << " spaces to spot "<< position[playTurn] << "." << endl;
outputfile << playName[playTurn] << " has drawn a " << cards[cardHolder] << "." << endl;
outputfile << playName[playTurn] << " has advanced " << cards[cardHolder] << " spaces to spot "<< position[playTurn] << "." << endl;
for(int n = 0; n < 7; n++){
    if(position[playTurn] == boardObstacle[n]){
        cout << "You've encountered an obstacle!" << endl;
        outputfile << "You've encountered an obstacle!" << endl;
        goBack = rand() % 3 + 1;
        if(goBack == 3){
            swapPlaces(playTurn, position, playName, numOfPlay, outputfile);
        }
        else
            cout << "Go back " << goBack << " spaces." << endl;
            outputfile << "Go back " << goBack << " spaces." << endl;
            position[playTurn] = position[playTurn] - goBack;
            cout << playName[playTurn] << " is now on space " << position[playTurn] << "." << endl;
            outputfile << playName[playTurn] << " is now on space " << position[playTurn] << "." << endl;
            n = 7;
        }
    }

}
/**********************************************************************************************************/

void initializeGame(int board[],int bsize, int cards[], int drawnCards[], int obst[], ofstream &outputfile){

for(int j = 0; j < 12; j++){
    cards[j] = rand() % 5 + 1;
    cout << "Card " << j+1 << " is " << cards[j] << endl;
}
for(int k = 0; k < 12; k++)
    drawnCards[k] = 0;
for(int l = 0; l < bsize; l++){
    board[l] = l;
}
for(int m = 0; m < 7; m++){
        obst[m] = rand() % bsize + 1;
    }
cout << "The Card Pile has been shuffled." << endl;
cout << "There are " << bsize <<" spaces on the board." << endl;
outputfile << "There are " << bsize <<" spaces on the board." << endl;
}

/*********************************************************************************************************/
void showState(int pNum, string pName[], int location[]){

    cout << "Player number " << pNum << "'s turn has finished. Displaying Player Locations." << endl;
    for(int y = 0; y < pNum; y++){
            cout << pName[y] << " is currently on square " << location[y] << "." << endl;
    }
}
/********************************************************************************************************/
//Plays the game
int play(int playeramount, ofstream &outputfile){

srand(time(NULL)); //Initializes rand(0 function to provide more random board spaces each game
int const boardSize = rand()% 29 + 20; //Sets board length between 20 to 50 spaces
int playerList[4] = {0, 0, 0, 0}, gameBoard[boardSize],cardPile[12],drawnPile[12], obstacles[7], turnStart;
int refreshCount;
string playerNames[4];

for(int i = 1; i <= playeramount;i++){
    cout << "Please enter Player " << i << "'s name." << endl;
    cin >> playerNames[i-1];
    cout << playerNames[i-1] << " is Player " << i << "." << endl;
    outputfile << playerNames[i-1] << " is Player " << i << "." << endl;
}
initializeGame(gameBoard, boardSize, cardPile, drawnPile, obstacles, outputfile);
cout << "The first player will  be chosen by random." << endl;

for(turnStart = rand() % playeramount + 0; turnStart < playeramount; turnStart++){
    taketurn(turnStart, playerNames, playerList, obstacles, cardPile, drawnPile, playeramount, outputfile);
        for(int z = 0; z < playeramount; z++){
                if(playerList[z] >= boardSize){
                    cout << playerNames[z] << " has reached the end of the board. Game Over!" << endl;
                    outputfile << playerNames[z] << " has reached the end of the board. Game Over!" << endl;
                    return(0);
                }
        if(turnStart == playeramount - 1){
            showState(playeramount, playerNames, playerList);
            turnStart = -1;
            }
        }
    }
}
/**********************************************************************************************************/
int main(){
    ofstream outfile("BoardGame1Results.txt");

    displayRules(outfile);
    if(gamePrompt() == 1)
        return(0);
    else{
        play(playerNum(outfile), outfile);
        outfile.close();
    }
}
