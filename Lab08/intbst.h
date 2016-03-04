// intbst.h
// Binary search tree header file for CS 24 lab

#ifndef INTBST_H
#define INTBST_H

class IntBST {

public:
    // ctor, dtor, insert and one print method already done in intbst.cpp:
    IntBST();                   // constructor
    ~IntBST();                  // destructor
    bool insert(int value);     // insert value; return false if duplicate
    void printPreOrder() const; // prints tree data pre-order to cout

    // 5 METHODS YOU MUST IMPLEMENT in intbst.cpp:
    void printInOrder() const;       // print tree data in-order to cout
    void printPostOrder() const;     // print tree data post-order to cout
    int sum() const;                 // sum of all values
    int count() const;               // count of values
    bool contains(int value) const;  // true if value is in tree

    // suggested signature of optional challenge method:
    //   void remove(int value);  // remove value from the tree

private:

    // DO NOT CHANGE DEFINITION OF struct Node:
    struct Node {
        int info;
        Node *left, *right;
        // useful constructor:
        Node(int v=0) : info(v), left(0), right(0) { }
    };

    // just one instance variable (pointer to root node):
    Node *root;

    // recursive utility functions for use by public methods above
    void clear(Node *n); // for destructor
    bool insert(int value, Node *n); // note overloading names for simplicity
    void printPreOrder(Node *n) const;
    void printInOrder(Node *n) const;
    void printPostOrder(Node *n) const;
    int sum(Node *n) const;
    int count(Node *n) const;
    bool contains(int value, Node *n) const; // not used for iterative solution

    // suggested signatures of utility functions for optional challenge:
    // void remove(int value, Node* &n); // uses removeThis below too
    // void removeThis(Node* &n); // in turn, uses maxValue below
    // int maxValue(Node *n) const;
};

#endif
