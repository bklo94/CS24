// stringbst.cpp
// Implements class StringBST
// YOUR NAME(S), DATE

#include "stringbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
StringBST::StringBST() : root(0) { }

// destructor deletes all nodes
StringBST::~StringBST() {
    clear(root);
}

// recursive helper for destructor
void StringBST::clear(Node *n) {
    if (n) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

// insert value in tree; return false if duplicate
bool StringBST::insert(string value) {
    // handle special case of empty tree first
    if (!root) {
        root = new Node(value);
        return true;
    }
    // otherwise use recursive helper
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool StringBST::insert(string value, Node *n) {
    if (value == n->info)
        return false;
    if (value < n->info) {
        if (n->left)
            return insert(value, n->left);
        else {
            n->left = new Node(value);
            return true;
        }
    }
    else {
        if (n->right)
            return insert(value, n->right);
        else {
            n->right = new Node(value);
            return true;
        }
    }
}

// print tree data pre-order
void StringBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void StringBST::printPreOrder(Node *n) const {
    if (n) {
        cout << n->info << " ";
        printPreOrder(n->left);
        printPreOrder(n->right);
    }
}

// remove value from tree
void StringBST::remove(string value) {
    // IMPLEMENT
    // (add helpers below if you use recommended recursive technique)
}
