// wordsexam.cpp
// Examines implementation of class Words
// cmc, 10/16/2015

#include <iostream>
#include <string>
#include "words2.h"
using namespace std;
using namespace lab04_2;

// PROTOTYPES for functions used by this test program:
string test1(); // tests basic features
string test2(); // tests copy constructor
string test3(); // tests assignment operator

int main(int argc, char *argv[])
{
    string result;
    if (argc > 1) {
        switch (argv[1][0]) {
            case '1':
                result = test1(); break;
            case '2':
                result = test2(); break;
            case '3':
                result = test3(); break;
            default:
                cout << "bad test id: " << argv[1] << endl;
                return 1;
        }
        cout << "Completed test " << argv[1]
            << "; result: " << result << endl;
    }
    else {
        cout << "error: missing command line argument" << endl;
        cout << "usage: " << argv[0] << " test_id" << endl;
        return 2;
    }
    return 0;
}

// test1 - basic features
string test1() {
    cout << "I am creating object with capacity of 5 words.\n";
    Words test(5);
    if (test.size() == 0 && test.get_capacity() == 5)
        cout << "Passed constructor test, size and capacity.\n";
    else
        return "FAILed size or capacity test of new object";
    
    cout << "Now I am appending 10 words (should resize) ...";
    string strings[10] = {"apple","bobcat","cork","dog","echo",
        "fox","gorge","hop","icky","jack"};
    for (int i=0; i<10; i++)
        test.append(strings[i]);
    if (test.size() == 10 && test.get_capacity() >= 10)
        cout << " OK. Passed.\n";
    else
        return "FAILed resize for append past capacity test";
    
    cout << "Verifying correct data ...";
    for (int i=0; i<10; i++)
        if (test[i] != strings[i]) {
            cout << "mismatch at index " << i << endl;
            return string("FAILed correct data appended test");
        }
    cout << "OK. Passed.\n";

    return string("PASS ALL");
}

// test2 - copy constructor
string test2() {
    Words original;

    cout << "I am appending 10 words to a new Words object.\n";
    string strings[10] = {"apple","bobcat","cork","dog","echo",
        "fox","gorge","hop","icky","jack"};
    for (int i=0; i<10; i++)
        original.append(strings[i]);

    cout << "Now I will make new Words object as a copy.\n";
    Words copy(original);
    cout << "Verifying size and capacity of copy ...";
    if (copy.size() == 10 && copy.get_capacity() == 10)
        cout << "OK. Passed.\n";
    else
        return string("FAILed size/capacity test of copy.");

    cout << "Verifying correct data in copy before changes ...";
    for (int i=0; i<10; i++)
        if (copy[i] != original[i]) {
            cout << "mismatch at index " << i << endl;
            return string("FAILed basic copy constructor test");
        }
    cout << "OK. Passed.\n";
    
    cout << "Changing all words in original.\n";
    for (int i=0; i<10; i++)
        original[i] = string("");
    cout << "Now verifying words in copy were not changed ...";
    for (int i=0; i<10; i++)
        if (copy[i] == original[i]) {
            cout << "still matches at index " << i << endl;
            return string("FAILed copy constructor deep copy test");
        }
    cout << "OK. Passed.\n";

    return string("PASS ALL");
}

// test3 - assignment operator
string test3() {
    Words original;
    
    cout << "I am appending 10 words to a new Words object.\n";
    string strings[10] = {"apple","bobcat","cork","dog","echo",
        "fox","gorge","hop","icky","jack"};
    for (int i=0; i<10; i++)
        original.append(strings[i]);
    
    cout << "Now I will make new empty Words object,\n"
        << " and then use assignment to make it a copy.\n";
    Words copy;
    copy = original;
    cout << "Verifying size and capacity of copy ...";
    if (copy.size() == 10 && copy.get_capacity() == 10)
        cout << "OK. Passed.\n";
    else
        return string("FAILed size/capacity test of copy.");
    
    cout << "Verifying correct data in copy before changes ...";
    for (int i=0; i<10; i++)
        if (copy[i] != original[i]) {
            cout << "mismatch at index " << i << endl;
            return string("FAILed assignment operator test");
        }
    cout << "OK. Passed.\n";
    
    cout << "Changing all words in original.\n";
    for (int i=0; i<10; i++)
        original[i] = string("");
    cout << "Now verifying words in copy were not changed ...";
    for (int i=0; i<10; i++)
        if (copy[i] == original[i]) {
            cout << "still matches at index " << i << endl;
            return string("FAILed assignment deep copy test");
        }
    cout << "OK. Passed.\n";
    
    return string("PASS ALL");
}

