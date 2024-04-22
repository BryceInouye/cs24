#include "Errors.h"
#include "Move.h"
#include <cctype>


Move::Move(const std::string& input) {
    if (isdigit(input[0]) && input[0] <= '9' && input[0] >= '1') {
        number = input[0] - '0';
    } else {
        throw ParseError("move number error (1-9)");
    }
    checkSpace(input[1]);
    if (input[2] == 'X' || input[2] == 'O' || input[2] == 'x' || input[2] == 'o') {
        player = toupper(input[2]);
    } else {
        throw ParseError("player error");
    }
    checkSpace(input[3]);
    if (((input[4] >= 'A' && input[4] <= 'C') || (input[4] >= 'a' && input[4] <= 'c')) && (input[5] >= '1' && input[5] <= '3')) {
        row = toupper(input[4]) - 65;
        column = input[5] - '1';
    } else if ((input[4] >= 'A' && input[4] <= 'C') && !(input[5] >= '1' && input[5] <= '3')) {
        throw ParseError("invalid column error (1-3)");
    } else if (!(input[4] >= 'A' && input[4] <= 'C') && (input[5] >= '1' && input[5] <= '3')) {
        throw ParseError("invalid row error (A-C)");
    } else {
        throw ParseError("column & row error");
    }
    if (input.size() == 6) {
        return;
    }
    if (!isspace(input[6])){
        throw ParseError("random character after coordinate");
    }
    if (input.size() == 7){
        return;
    }
    if (input[7] != '#') {
        throw ParseError("random character after space");
    }
    return; //return happens since comment is discarded, we only care if comment is formatted properly
}
void Move::checkSpace(char x) {
    if (!isspace(x)) {
        throw ParseError("space error: " + std::to_string(x));
    }
}
std::string Move::to_string() const{
    std::string move;
    char rowToLetter = row + 'A';
    move = std::to_string(number) + " " + player + " " + rowToLetter + std::to_string(column + 1);
    return move;
}