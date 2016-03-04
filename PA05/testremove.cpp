// testremove.cpp
// For testing StringBST remove function for CS 24 PA5

#include "stringbst.h"

#include <iostream>
#include <cctype>
using namespace std;

// lets user insert and remove strings on a StringBST
int main() {

    StringBST bst;
    char choice;
    string word;
    void getUserInput(char &choice, string &word); // helper function below main

    do {
        getUserInput(choice, word);
        if (choice != 'q') {
            if (choice == 'i') {
                if (bst.insert(word))
                    cout << "inserted \"" << word << "\"\n";
                else
                    cout << "did not insert duplicate \"" << word << "\"\n";
            }
            else if (choice == 'r') {
                bst.remove(word);
                cout << "attempted to remove \"" << word << "\"\n";
            }
            cout << "   current pre-order: ";
            bst.printPreOrder();
            cout << endl;
        }
    } while (choice != 'q');
    
    return 0;
}

void getUserInput(char &choice, string &word) {
    choice = ' ';
    do {
        cout << "\n--------- Choices ---------\n";
        cout << " I - insert a word\n";
        cout << " R - remove a word\n";
        cout << " Q - quit this test program\n";
        cout << "---------------------------\n";
        cin >> choice;
        choice = tolower(choice);
        if (choice == 'i') {
            cout << "enter word to insert\n";
            cin >> word;
        }
        else if (choice == 'r') {
            cout << "enter word to remove\n";
            cin >> word;
        }
    } while (choice != 'i' && choice != 'r' && choice != 'q');
}
