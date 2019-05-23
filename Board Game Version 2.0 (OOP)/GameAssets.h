/* Name: Michael Lewis
 * Username: mlewis
 * Section: EWQ6
 * DueDate: Wednesday April 26, 2017
 * Assignment #7
*/
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

#ifndef GAMEASSETS_H_INCLUDED
#define GAMEASSETS_H_INCLUDED

class playerInfo{
    private:
        int playerSpace; //Players position on the board
        char cNames[25]; //C String holding players name
    public:
        playerInfo();
        void setPlayerSpace(int);
        void setPlayerName(int); //Sets the players name
        void moveForward(int, int, ofstream&); //moves the player forward
        void moveBackward(int, ofstream&);
        char* getName(); //Returns the players name
        int getPlayerSpace(); //Returns player current position

};

class cardInfo{
    private:
        int cardPile[12]; //Set of 12 cards that may be drawn from
        int drawnPile[12]; //Set of cards that have already been drawn
    public:
        cardInfo(); //Initializes the card values between 1 and 10
        void getCardValues(); //Displays the values of all the cards in cardPile
        void shuffleDeck (); //Checks if the cardPile has been used up then shuffles
        int drawCard(); //Draws a random card and returns its value
};

class boardInfo{
    private:
        int numOfPlayers; //Amount of players in this game
        int boardSize; //Size of the board for the current game
        int numObsts; //Number of obstacles on the board
        int obstSize; //Largest obstacle that can be placed on the board
        int numAgain; //Number of extra turn spaces on board
        vector <int> obstacles; //Pointer to array of obstacles
        vector <int> goAgain; //Points to array of board spaces with an extra turn
    public:
        void playerPrompt(); //Prompts the user for how many players will be in the game
        void initializeBoard(); //Sets up the board obstacles and cards for the game
        int firstTurn(playerInfo*);
        int getNumOfPlayers();
        int getBoardSize();
        int getNumObsts();
        int getObstSize();
        int getNumAgain();
        int getObstacles(int);
        int getGoAgain(int);
};





#endif // GAMEASSETS_H_INCLUDED
