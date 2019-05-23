#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#ifndef BOARDINFO_H_INCLUDED
#define BOARDINFO_H_INCLUDED

class BoardInfo{
    private:
        int boardSize;
        int numOfObsts;
        int maxObstSize;
        int numOfBonus;
        vector <int> obstacles;
        vector <int> bonusTurns;
    public:
        int getBoardSize() {return(boardSize);}
        void initializeBoard();

        friend class gameInfo;
};


#endif // BOARDINFO_H_INCLUDED
