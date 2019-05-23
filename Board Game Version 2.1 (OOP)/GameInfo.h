#include <cstdlib>
#include "BoardInfo.h"
#include "CardInfo.h"
#include "PlayerInfo.h"

using namespace std;

#ifndef GAMEINFO_H_INCLUDED
#define GAMEINFO_H_INCLUDED

class gameInfo{
    private:
        PlayerInfo playerData;
        BoardInfo boardData;
        CardInfo cardData;
    public:
        void gamePrompt();
        void initializeGameAssets();
        void playGame();
        int takeTurn(int, ofstream&);
};



#endif // GAMEINFO_H_INCLUDED
