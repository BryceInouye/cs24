#include "Errors.h"
#include "Board.h"
#include <iostream>

// Space for implementing Board functions.
size_t Board::getGameState() {
    return gameState;
}

int Board::getTurnNumber() {
    return turnNumber;
}

char Board::getPlayerTurn() {
    return (playerTurn == true) ? 'X':'O';
}

void Board::winCheck() {
    // set of all winning combinations
    std::bitset<9>winCombinations[8] = {std::bitset<9>("001001001"), std::bitset<9>("010010010"), std::bitset<9>("100100100"),
                                        std::bitset<9>("000000111"), std::bitset<9>("000111000"), std::bitset<9>("111000000"),
                                        std::bitset<9>("100010001"), std::bitset<9>("001010100")};
    if (playerTurn == true) { // check X board 
        for (size_t i = 0; i < 8; i++) {
            if ((boardX & winCombinations[i]) == winCombinations[i]) {
                gameState = 2;
                break;
            }
        }
    } else { // check O board
        for (size_t i = 0; i < 8; i++) {
            if ((boardO & winCombinations[i]) == winCombinations[i]) {
                gameState = 3;
                break;
            }
        }
    }
    return;

}

Board::Board() {
    gameState = 0;
    turnNumber = 0;
    boardX.reset();
    boardO.reset();
}

void Board::turn(const Move& input) {
    turnNumber++;
    // Move move(input);
    if (turnNumber == 1) { // set who starts for future turns
        gameState = 1;
        if (input.player == 'X') {
            playerTurn = true;
        } else {
            playerTurn = false;
        }
    }
    bool x;
    x = (input.player == 'X'); // x is the inputted player

    std::bitset<9>tempBoard; 
    if (playerTurn == true) {
        tempBoard |= std::bitset<9>(1U << ((input.row * 3) + input.column)); // tempBoard is the proposed changes to board
    } else {                                                                         // to prevent identical moves on itself
        tempBoard |= std::bitset<9>(1U << ((input.row * 3) + input.column));
    }

    checkTurn(x, input.number, tempBoard); // checks if everything makes sense logically

    if (playerTurn == true) { // putting input on the board if all checkTurn tests pass
        boardX |= (1U << ((input.row * 3) + input.column));
    } else {
        boardO |= (1U << ((input.row * 3) + input.column));
    }     
    
    winCheck();
    playerTurn = !playerTurn; // swaps for next turn, will be compared in checkTurn
    if (turnNumber == 9 && gameState == 1) { // if no winner, then tie
        gameState = 4;
    } 
    return;
}

void Board::checkTurn(const bool player, size_t turnNum, const std::bitset<9>tempBoard) {
    if ((tempBoard & boardO).any() || (boardX & tempBoard).any()) { // throws error if space already exists on itself or opposite board
        // std::cout << "tempboard: " << tempBoard << std::endl;
        throw InvalidMove("space already occupied error");
    }
    if (player != playerTurn) {
        throw InvalidMove("same player consecutive turn error");
    }
    if (turnNum != turnNumber) {
        std::cout << "input turn: " << turnNum << std::endl;
        std::cout << "expected turn: " << turnNumber << std::endl;
        throw InvalidMove("turn is not equal to expected error");
    }
    return;
}
