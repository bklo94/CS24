// testlist.cpp
// Tests intlist.cpp

#include "intlist.h"

#include <cstdlib> // provides atoi
#include <iostream>
using namespace std;

// creates two lists (one empty), and does simple tests of list methods
int main(int argc, char *argv[]) {

    IntList list1, list2;
    int first = 0, second = 0, last = 0, initial_size;

    // append command line arguments to list1
    if (argc < 2) {
        cout << "error: need at least one int arg on command line" << endl;
        cout << "usage: " << argv[0] << " int [int ...]" << endl;
        return 1;
    }
    initial_size = argc - 1;
    for (int i = 1; i < argc; i++) {
        int value = atoi(argv[i]);
        list1.append(value);
        if (i == 1)
            first = value;
        if (i == 2)
            second = value;
        if (i == initial_size)
            last = value;
    }

    // print and test methods for list1
    cout << "List 1: \n   ";
    list1.print();
    cout << endl << "   count: " << list1.count() << endl;
    int sum = list1.sum();
    cout << "   sum: " << sum << endl;
    cout << "   contains " << first << " ? "
        << (list1.contains(first)? "yes" : "no") << endl;
    cout << "   contains " << second << " ? "
        << (list1.contains(second)? "yes" : "no") << endl;
    cout << "   contains " << last << " ? "
        << (list1.contains(last)? "yes" : "no") << endl;
    cout << "   contains " << sum << " ? "
        << (list1.contains(sum)? "yes" : "no") << endl;
    cout << "   max: " << list1.max() << endl;
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(3);
    cout << "   average: " << list1.average() << endl;
    cout << "   List after insertFirst(sum): \n   ";
    list1.insertFirst(sum);
    list1.print();
    cout << endl;

    // test methods for empty list2 (just need one contains test though)
    cout << "Empty list 2: \n   ";
    list2.print();
    cout << endl << "   count: " << list2.count() << endl;
    cout << "   sum: " << list2.sum() << endl;
    cout << "   contains 1 ? "
        << (list2.contains(1)? "yes" : "no") << endl;
    cout << "   max: " << list2.max() << endl;
    cout << "   average: " << list2.average() << endl;
    cout << "   List 2 after insertFirst(3), then insertFirst(1): \n   ";
    list2.insertFirst(3);
    list2.insertFirst(1);
    list2.print();
    cout << endl;

    return 0;
}
