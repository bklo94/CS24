// stringbst.h
// Binary search tree header file for CS 24 programming assignment

#ifndef STRINGBST_H
#define STRINGBST_H

#include <string>
using std::string;

class StringBST {

public:
    // ctor, dtor, insert and one print method already done in stringbst.cpp:
    StringBST();                   // constructor
    ~StringBST();                  // destructor
    bool insert(string value);     // insert value; return false if duplicate
    void printPreOrder() const;    // prints tree data pre-order to cout

    // METHOD YOU MUST IMPLEMENT in stringbst.cpp:
    void remove(string value);
        // Postcondition: if the tree currently contains an exact copy of value,
        // then the tree node contain that copy is removed from the tree, and
        // the tree remains a valid binary search tree. In the case where the
        // removed node has both a left and right child, the rule is that the
        // greatest value in the left subtree will take its place. If there is
        // no exact copy of the value in the tree, then nothing is done.

private:

    // DO NOT CHANGE DEFINITION OF struct Node:
    struct Node {
        string info;
        Node *left, *right;
        // useful constructor:
        Node(string v="") : info(v), left(0), right(0) { }
    };

    // just one instance variable (pointer to root node):
    Node *root;

    // recursive utility functions used by public methods above:
    void clear(Node *n); // for destructor
    bool insert(string value, Node *n);
    void printPreOrder(Node *n) const;

    // (optional) utility functions to help implement public remove:
    void remove(string value, Node* &n);
    void removeThis(Node* &n);        // helper for remove(int, Node *&)
    string maxValue(Node *n) const;   // helper for removeThis
};

#endif
