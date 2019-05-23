#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include "BoardInfo.h"

using namespace std;

/*************************/
/*initializeBoardFunction*/
/*************************/
void BoardInfo::initializeBoard(){
    int boardCapacity, bonusTurnCapacity, largestObst, matches, obstacleCapacity;
    bool matchTest = true;

    /*                      BoardSize Setup                          */
    cout << "Please enter the number of spaces you would like on the board." << endl;
    cout << "You may pick a number between 20 and 100." << endl;
    cin >> boardCapacity;

    while(cin.fail() || boardCapacity > 100 || boardCapacity < 20){
        cout << "Invalid entry, please enter a number between 20 and 100." << endl;
        cin.clear();
        cin.ignore();
        cin >> boardCapacity;
    }
    boardSize = boardCapacity; //Sets board size inside class
    cout << "This board will have " << boardSize << " spaces." << endl;
    /*                   Obstacle Setup                                             */
    cout << "How many obstacles would you like on the board?" << endl;
    cout << "You may pick a number between 7 and 12." << endl;
    cin >> obstacleCapacity;

    while(cin.fail() || obstacleCapacity < 7 || obstacleCapacity > 12){
        cout << "Invalid entry, please enter a number between 7 and 12." << endl;
        cin.clear();
        cin.ignore();
        cin >> obstacleCapacity;
    }
    numOfObsts = obstacleCapacity; //Sets number of obstacles in class
    obstacles.resize(numOfObsts); //Sets size of obstacle vector in class
    cout << "There will be " << numOfObsts << " obstacles on this board." << endl;
    for(int obstFill = 0; obstFill < numOfObsts; obstFill++){
        obstacles[obstFill] = rand() % (boardSize - 1) + 1;
        cout << "Obstacle " << obstFill + 1 << " is located on space " << obstacles[obstFill] << "." << endl;
    }
    /*                          Set Largest Obstacle                    */
    cout << "What would you like the largest obstacle to be? You may choose a value between 1 and 5." << endl;
    cin >> largestObst;

    while(cin.fail() || largestObst < 1 || largestObst > 5){
        cout << "Invalid entry, please enter a number between 1 and 5." << endl;
        cin.clear();
        cin.ignore();
        cin >> largestObst;
    }
    maxObstSize = largestObst; //Sets the maximum obstacle size
    cout << "The largest obstacle will be of size " << maxObstSize << "." << endl;
    /*                      Bonus Turns Setup                       */
    cout << "How many extra turns would you like on the board?" << endl;
    cout << "You may enter a number between 1 and 3." << endl;
    cin >> bonusTurnCapacity;

    while(cin.fail() || bonusTurnCapacity < 1 || bonusTurnCapacity > 3){
        cout << "Invalid entry, please enter a number between 1 and 3." << endl;
        cin.clear();
        cin.ignore();
        cin >> bonusTurnCapacity;
    }
    numOfBonus = bonusTurnCapacity; //Sets the maximum amount of bonus turns
    bonusTurns.resize(numOfBonus); //resizes the vector to have the proper amount of bonus turns
    //Loops around and checks if at LEAST one value from the obstacles array coincides
    //with a value in the bonusTurn array, and if it does then it keeps giving the bonus new
    //values until none of them match preventing error
    while(matchTest == true){
        matches = 0;
        for(int bonusFill = 0; bonusFill < bonusTurnCapacity; bonusFill++){
            bonusTurns[bonusFill] = rand() % (boardSize - 1) + 1;
        }
        for(int overCheck = 0; overCheck < numOfBonus; overCheck++){
            for(int doubleCheck = 0; doubleCheck < numOfObsts; doubleCheck++){
                if(bonusTurns[overCheck] == obstacles[doubleCheck]){
                    matches++;
                }
            }
        }
    if(matches > 0){
        matchTest = true;
    }
    else if(matches <= 0){
        matchTest = false;
        }
    }
}
