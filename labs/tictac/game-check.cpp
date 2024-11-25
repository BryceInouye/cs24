#include "Board.h"
#include "Errors.h"
#include "Move.h"
#include <iostream>

int main() {
    Board board;
    while (board.getGameState() <= 1) {
        std::string line;
        std::getline(std::cin, line);
        if (line.empty()) {
            break;
        }
        try {
            Move move(line);
            board.turn(move);
        }
        catch (const ParseError& e) {
            std::cout << "Parse error.\n";
            return 1;
        }
        catch (const InvalidMove& e) {
            std::cout << "Invalid move.\n";
            return 2;
        }
    }
    try {
        std::string line;
        std::getline(std::cin, line);
        if (!line.empty()) {
            throw InvalidMove("extra lines");
        }
    } catch (const InvalidMove& e) {
        std::cout << "Invalid move.\n";
        return 2;
    }
    
    size_t result = board.getGameState();
    switch (result) {
        case 0: 
            std::cout << "Game in progress: New game." << std::endl;
            break;
        case 1:
            std::cout << "Game in progress: " << board.getPlayerTurn() << "'s turn." << std::endl;
            break;
        case 2:
            std::cout << "Game over: X wins." << std::endl;
            break;
        case 3:
            std::cout << "Game over: O wins." << std::endl;
            break;
        case 4:
            std::cout << "Game over: Draw." << std:: endl;
            break;
        default:
            std::cout <<"something went wrong" << std::endl;
    }
    return 0;
}
