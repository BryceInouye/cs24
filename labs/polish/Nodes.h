#ifndef NODES_H
#define NODES_H

#include "AST.h"

// Declare your AST subclasses here.
// Implement their member functions in Nodes.cpp.


class numberNode : public AST {
    public: 
        numberNode(double num) : data(num) {}
        
        std::string prefix()  const; // pre/post fix is simply returning the string
        std::string postfix() const;
        double      value()   const;
    private:
        double data;
};

class additionNode : public AST {
    public:
        additionNode(AST* rightNode, AST* leftNode) : right(rightNode), left(leftNode) {}
        ~additionNode();

        std::string prefix()  const;
        std::string postfix() const;
        double      value()   const;
    private:
        AST* right;
        AST* left;
};

class subtractionNode : public AST {
    public:
        subtractionNode(AST* rightNode, AST* leftNode) : right(rightNode), left(leftNode) {}
        ~subtractionNode();

        std::string prefix()  const;
        std::string postfix() const;
        double      value()   const;
    private:
        AST* right;
        AST* left;
};

class multiplicationNode : public AST {
    public:
        multiplicationNode(AST* rightNode, AST* leftNode) : right(rightNode), left(leftNode) {}
        ~multiplicationNode();

        std::string prefix()  const;
        std::string postfix() const;
        double      value()   const;
    private:
        AST* right;
        AST* left;
};

class divisionNode : public AST {
    public:
        divisionNode(AST* rightNode, AST* leftNode) : right(rightNode), left(leftNode) {}
        ~divisionNode();

        std::string prefix()  const;
        std::string postfix() const;
        double      value()   const;
    private:
        AST* right;
        AST* left;
};

class moduloNode : public AST {
    public:
        moduloNode(AST* rightNode, AST* leftNode) : right(rightNode), left(leftNode) {}
        ~moduloNode();

        std::string prefix() const;
        std::string postfix() const;
        double value() const;
    private:
        AST* right;
        AST* left;
};

class negationNode : public AST {
    public:
        negationNode(AST* rightNode) : right(rightNode) {}
        ~negationNode();

        std::string prefix() const;
        std::string postfix() const;
        double value() const;     
    private:
        AST* right; 
};
#endif
