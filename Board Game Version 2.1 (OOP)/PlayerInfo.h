#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#ifndef PLAYERINFO_H_INCLUDED
#define PLAYERINFO_H_INCLUDED

class PlayerInfo {
    private:
        int firstTurn;
        int numOfPlayers;
        int* playerSpace;
        string* playerNames;
    public:
        PlayerInfo();
        ~PlayerInfo();
        void setPlayers();
        void printSpaces();
        void setFirstTurn();
        void moveForward(int, int, int, ofstream&);
        void moveBackward(int, int, ofstream&);
        void swapPlaces(int, ofstream&);
        int getNumOfPlayers() const {return(numOfPlayers);}

        friend class gameInfo;
};

#endif // PLAYERINFO_H_INCLUDED
