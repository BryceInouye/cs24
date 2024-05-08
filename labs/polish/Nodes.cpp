#include "Nodes.h"

#include <sstream>
#include <string>
#include <cmath>

// This creates the number format the autograder expects:
std::string format(double number) {
  std::ostringstream stream;
  stream << number;
  return stream.str();
}

// Implement your AST subclasses' member functions here.

// number subclass:
std::string numberNode::prefix()  const {
  return format(data);
}
std::string numberNode::postfix() const{
  return format(data);
}
double numberNode::value() const {
  return data;
}

// addition subclass:
additionNode::~additionNode() { // destructor. works by calling child destructor which calls its child destructor etc.
  delete left;
  delete right;
}

std::string additionNode::prefix() const {
  // print data
  // if can move left, move left
  // if can move right, move right
  std::string prefixString = "+ ";
  prefixString += left->prefix();
  prefixString += " ";
  prefixString += right->prefix();

  return prefixString;
}
std::string additionNode::postfix()  const {
  // if can move left, move left
  // print data
  // if can move right, move right
  std::string postfixString;
  postfixString += left->postfix();
  postfixString += " ";
  postfixString += right->postfix();
  postfixString += " +";

  return postfixString;
}
double additionNode::value() const {
  double sum = 0;
  sum += left->value() + right->value();

  return sum;
}

// subtraction subclass:
subtractionNode::~subtractionNode() {
  delete right;
  delete left;
}

std::string subtractionNode::prefix() const {
  std::string prefixString = "- ";
  prefixString += left->value();
  prefixString += " ";
  prefixString += right->value();

  return prefixString;
}
std::string subtractionNode::postfix() const {
  std::string postfixString;
  postfixString += left->value();
  postfixString += " ";
  postfixString += right->value();
  postfixString += " -";

  return postfixString;
}
double subtractionNode::value() const {
  double difference = 0;
  difference = left->value() - right->value();

  return difference;
}

// multiplication subclass:
multiplicationNode::~multiplicationNode() {
  delete right;
  delete left;
}

std::string multiplicationNode::prefix()  const {
  std::string prefixString = "* ";
  prefixString += left->value();
  prefixString += " ";
  prefixString += right->value();

  return prefixString;
}
std::string multiplicationNode::postfix() const {
  std::string postfixString;
  postfixString += left->value();
  postfixString += " ";
  postfixString += right->value();
  postfixString += " *";

  return postfixString;
}
double multiplicationNode::value() const {
  double product;
  product = left->value() * right->value();

  return product;
}

// division subclass:
divisionNode::~divisionNode() {
  delete right;
  delete left;
}

std::string divisionNode::prefix()  const {
  std::string prefixString = "/ ";
  prefixString += left->value();
  prefixString += " ";
  prefixString += right->value();

  return prefixString;
}
std::string divisionNode::postfix() const {
  std::string postfixString;
  postfixString += left->value();
  postfixString += " ";
  postfixString += right->value();
  postfixString += " /";

  return postfixString;
}
double      divisionNode::value()   const {
  double quotient;
  quotient = left->value() / right->value();

  return quotient;
}

// modulo subclass:
moduloNode::~moduloNode() {
  delete right;
  delete left;
}

std::string moduloNode::prefix() const {
  std::string prefixString = "% ";
  prefixString += left->value();
  prefixString += " ";
  prefixString += right->value();

  return prefixString;
}
std::string moduloNode::postfix() const {
  std::string postfixString;
  postfixString += left->value();
  postfixString += " ";
  postfixString += right->value();
  postfixString += " %";

  return postfixString;
}
double moduloNode::value() const {
  double remainder;
  remainder = fmod(left->value(), right->value());

  return remainder;
};

// negation subclass
negationNode::~negationNode() {
  delete right;
}

std::string negationNode::prefix() const {
  std::string prefixString = "~ ";
  prefixString += right->value();

  return prefixString;
}
std::string negationNode::postfix() const {
  std::string postfixString;
  postfixString += right->value();
  postfixString += " ~";

  return postfixString;
}
double negationNode::value() const {
  double negatedValue;
  negatedValue = right->value() * (-1.0);

  return negatedValue;
} 