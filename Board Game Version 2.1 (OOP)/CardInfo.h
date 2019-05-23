#include <cstdlib>
#include <iostream>
#include <fstream>

#ifndef CARDINFO_H_INCLUDED
#define CARDINFO_H_INCLUDED

class CardInfo{
    private:
        int cardDeck[12];
        int drawnPile[12];
    public:
        CardInfo();
        void initializeDecks();
        void printCardValues();
        void deckShuffle();
        int drawCard();
};


#endif // CARDINFO_H_INCLUDED
