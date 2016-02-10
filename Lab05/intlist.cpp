// intlist.cpp
// Implements class IntList
// Brandon Lo  2/2/15

#include "intlist.h"

#include <iostream>
using std::cout;

// return sum of values in list
int IntList::sum() const {
    int sum = 0;
    Node *n = first;
    while (n != 0){
        sum += n -> info;
        n = n -> next;
    }
    return sum;
}

// returns true if value is in the list; false if not
bool IntList::contains(int value) const {
    Node *n = first;
    while (n != 0){
        if (n -> info == value)
            return true;
            n = n -> next;
    }
    return false;
}

// returns maximum value in list, or 0 if empty list
int IntList::max() const {
    Node *n = first;
    int max = 0;
    while (n !=0){
        if (n -> info > max){
            max = n -> info;
            n = n -> next;
        }
        else{
            n = n -> next;
        }
    }
    return max;
}

// returns average (arithmetic mean) of all values, or
// 0 if list is empty
double IntList::average() const {
    Node *n = first;
    if (n == 0)
        return 0;
    else;
        return (static_cast <double>(sum())/count());
}

// inserts value as new node at beginning of list
void IntList::insertFirst(int value) {
    Node *n = new Node();
	n->info = value;
    if (first == 0) {
       first = n;
    } else {
		n->next = first;
		first = n;
}
}

// DO NOT CHANGE ANYTHING BELOW (READ IT THOUGH)

// constructor sets up empty list
IntList::IntList() : first(0) { }

// destructor deletes all nodes
IntList::~IntList() {
    Node *n = first;
    while (n) {
        Node *garbage = n;
        n = n->next;
        delete garbage;
    }
}

// append value at end of list
void IntList::append(int value) {
    if (first == 0) { // empty list
        first = new Node;
        first->info = value;
        first->next = 0;
    }
    else {
        Node *n = first;
        while (n->next) // not last node yet
            n = n->next;
        n->next = new Node;
        n->next->info = value;
        n->next->next = 0;
    }
}

// print values enclose in [], separated by spaces
void IntList::print() const {
    Node *n = first;
    cout << '[';
    while (n) {
        cout << n->info;
        if (n->next)
            cout << " ";
        n = n->next;
    }
    cout << ']';
}

// return count of values
int IntList::count() const {
    int result = 0;
    Node *n = first;
    while (n) {
        ++result;
        n = n->next;
    }
    return result;
}
