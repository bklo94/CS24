// testfun.cpp - for testing recursive functions of recfun.cpp

#include "recfun.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

void test1() {
    unsigned int m, n;
    cout << "test1: testing function triangle.\n";
    cout << "enter m and n\n";
    cin >> m >> n;
    cout << "results for m = " << m << ", n = " << n << ":\n";
    triangle(cout, m, n);
}

void test2() {
    unsigned int levels;
    string prefix;
    cout << "test2: testing function numbers.\n";
    cout << "enter levels and prefix\n";
    cin >> levels >> prefix;
    cout << "results for levels = " << levels <<
        " prefix = " << prefix << ":\n";
    numbers(cout, prefix, levels);
}

void test3() {
    unsigned int n;
    cout << "test3: testing function bears.\n";
    cout << "enter n\n";
    cin >> n;
    cout << "bears(" << n << ") returns ";
    if (bears(n))
        cout << "true\n";
    else
        cout << "false\n";
}

void test4() {
    unsigned int n, i;
    cout << "test4. testing function pattern.\n";
    cout << "enter n and i\n";
    cin >> n >> i;
    cout << "results for n = " << n << ", i = " << i << ":\n";
    pattern(cout, n, i);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "usage: " << argv[0] << " test#\n";
        return 1;
    }
    int t = atoi(argv[1]);
    switch (t) {
        case 1: test1(); break;
        case 2: test2(); break;
        case 3: test3(); break;
        case 4: test4(); break;
        default:
            cout << "test# can be 1, 2, 3 or 4 only\n";
            return 2;
    }
    return 0;
}
