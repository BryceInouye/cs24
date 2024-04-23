#ifndef BOARD_H
#define BOARD_H


#include "Move.h"
#include <bitset>

// I recommended writing a Board class to manage your game state.
// Here's some space for the class definition; member functions go in Board.cpp.
class Board {
    public:
        Board();
        void winCheck();
        size_t getGameState();
        int getTurnNumber();
        char getPlayerTurn();
        void turn(const Move& input);
        void checkTurn(const bool player, size_t turnNum);
    
    private:
        size_t gameState; // 0 for not started, 1 for in progress, 2/3 for X/Y win, 4 for tie
        std::bitset<9>boardX;
        std::bitset<9>boardO;
        size_t turnNumber;
        bool playerTurn; // check to see whose turn it is, True for X and False for O


};

#endif
