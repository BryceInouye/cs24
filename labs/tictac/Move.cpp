#include "Errors.h"
#include "Move.h"
#include <cctype>


Move::Move(const std::string& input) {
    size_t index = 0;
    if (isdigit(input[index]) && input[index] <= '9' && input[index] >= '1') {
        number = input[index] - '0';
    } else {
        throw ParseError("move number error (1-9)");
    }
    index++;
    checkSpace(input, index);
    if (input[index] == 'X' || input[index] == 'O' || input[index] == 'x' || input[index] == 'o') {
        player = toupper(input[index]);
    } else {
        throw ParseError("player error");
    }
    index++;
    checkSpace(input, index);
    if ((input[index] >= 'A' && input[index] <= 'C') || (input[index] >= 'a' && input[index] <= 'c')) {
        row = toupper(input[index]) - 65;
    } else {
        throw ParseError("invalid row error (A-C)");
    }
    index++;

    //column check
    if (input[index] >= '1' && input[index] <= '3') {
        column = input[index] - '1';
    } else {
        throw ParseError("invalid column error (1-3)");
    }
    index++;
    if (index == input.size()) {
        return;
    } else if (!isblank(input[index])) {
        throw ParseError("invalid character after column (whitespace)");
    }
    checkSpace(input, index);
    if (isblank(input[index - 1]) || input[index] == '#') {
        return;
    } else {
        throw ParseError("invalid character after optional whitespace (#)");
    }
}
void Move::checkSpace(const std::string& input, size_t& index) {
    if (!isblank(input[index])) {
        throw ParseError("no space error");
    }
    while (index < input.size() && isblank(input[index])) {
        index++;
    }
    return;
}
std::string Move::to_string() const{
    std::string move;
    char rowToLetter = row + 'A';
    move = std::to_string(number) + " " + player + " " + rowToLetter + std::to_string(column + 1);
    return move;
}