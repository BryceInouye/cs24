#ifndef BOARD_H
#define BOARD_H


#include "Move.h"
#include <bitset>

// I recommended writing a Board class to manage your game state.
// Here's some space for the class definition; member functions go in Board.cpp.
class Board {
    std::bitset<9>player;
    Board();
};

#endif
