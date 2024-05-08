#include "AST.h"
#include "Nodes.h"
#include "Stack.h"
#include <sstream>

AST* AST::parse(const std::string& expression) {
    std::string token;
    std::istringstream stream(expression);
    Stack stack; // declare stack
    size_t numNodes = 0;
    while(stream >> token) {
        if(token == "+") {
            // 1. check if can pop twice
            // 2. pop twice
            // 3. declare new operation node
            // 4. update stack and stack count
            if (numNodes < 2) {
                throw std::runtime_error("Not enough operands");
            }
            AST* right = stack.pop();
            AST* left = stack.pop();
            additionNode* addNode = new additionNode(right, left);

            stack.push(addNode);
            numNodes--;
        } else if (token == "-") {
            if (numNodes < 2) {
                throw std::runtime_error("Not enough operands");
            }
            AST* right = stack.pop();
            AST* left = stack.pop();
            subtractionNode* subNode = new subtractionNode(right, left);

            stack.push(subNode);
            numNodes--;
        } else if (token == "*") {
            if (numNodes < 2) {
                throw std::runtime_error("Not enough operands.");
            }
            AST* right = stack.pop();
            AST* left = stack.pop();
            multiplicationNode* multNode = new multiplicationNode(right, left);

            stack.push(multNode);
            numNodes--;
        } else if (token == "/") {
            if (numNodes < 2) {
                throw std::runtime_error("Not enough operands");
            }
            AST* right = stack.pop();
            AST* left = stack.pop();
            divisionNode* divNode = new divisionNode(right, left);

            stack.push(divNode);
            numNodes--;
        } else if (token == "%"){
            if (numNodes < 2) {
                throw std::runtime_error("Not enough operands");
            }
            AST* right = stack.pop();
            AST* left = stack.pop();
            moduloNode* modNode = new moduloNode(right, left);

            stack.push(modNode);
            numNodes--;
        } else if (token == "~"){
            if (numNodes < 1) {
                throw std::runtime_error("Not enough operands");
            }
            AST* right = stack.pop();
            negationNode* negateNode = new negationNode(right);

            stack.push(negateNode);
        } else { // if it is not a valid operand, then it is either a valid number of invalid input
            bool decimalExists = false;
            for (size_t i = 0; i < token.size(); i++) { // check decimal, leading sign, and if it is a number
                if (token[i] == '.') {
                    if (decimalExists) {
                        throw std::runtime_error("Invalid token: " + token);
                    } else {
                        decimalExists = true; // throws error if extra decimal was found in the token
                    }
                } else if (token[i] == '+' || token[i] == '-') {
                    if (i > 0) { // if optional +/- is found anywhere else than the beginning of the token
                        throw std::runtime_error("Invalid token: " + token);
                    }
                } else if (token[i] < '0' || token[i] > '9') { 
                    // anything outside this range is invalid character. +/- and '.' have already been checked
                    throw std::runtime_error("Invalid token: " + token);
                } 
            }
            // only valid inputs can get to here
            double data = stod(token);
            numberNode* number = new numberNode(data);
            stack.push(number);
            numNodes++;
        }
            
        // switch case by operand type
        // put on the stack if not operator. if operator, pop 2 things from the stack, pop 1 if operation is specifically '~'
    }
    switch (numNodes) {
        case 0: // 0 nodes
            throw std::runtime_error("No input");
            break;
        case 1: // 1 node
            break;
        default: // more than 2 nodes
            throw std::runtime_error("Too many operands.");
    }
    // if the compiler reaches here, then there is only one node in the stack
    // this node already points to its children so all we do is pop and return
    AST* root = stack.pop();
    return root;
}
