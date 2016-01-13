// FILE: statexam.cxx
// Written by Michael Main (main@colorado.edu) - date unknown
// (new main function and test point distribution for UCSB CS 24,
//  by cmc, 10/23/2015)
// This program calls five test functions to test the statisitician class.
// Maximum number of points from this program is 90.

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>    // Provides memcpy function
#include "stats.h"
using namespace main_savitch_2C;
using namespace std;

bool close(double a, double b)
{
    const double EPSILON = 1e-5;
    return (fabs(a-b) < EPSILON);
}

int test1( )
{
    // Test program for basic statistician functions.
    // Returns 60 if everything goes okay; otherwise returns 0.

    statistician s, t;
    int i;
    double r = 0;

    if (s.length( ) || t.length( )) return 0;
    if (s.sum( ) || t.sum( )) return 0;

    for (i = 1; i <= 10000; i++)
    {
	s.next(i);
	r += i;
    };

    if (t.length( ) || t.sum( )) return 0;
    if (s.length( ) != 10000) return 0;
    if (!close(s.sum( ), r)) return 0;
    if (!close(s.mean( ), r/10000)) return 0;
    
    // Reset and then retest everything
    s.reset( );
    t.reset( );
    r = 0;
    
    if (s.length( ) || t.length( )) return 0;
    if (s.sum( ) || t.sum( )) return 0;

    for (i = 1; i <= 10000; i++)
    {
	s.next(i);
	r += i;
    };

    if (t.length( ) || t.sum( )) return 0;
    if (s.length( ) != 10000) return 0;
    if (!close(s.sum( ), r)) return 0;
    if (!close(s.mean( ), r/10000)) return 0;

    return 60;
}

int test2( )
{
    // Test program for minimum/maximum statistician functions.
    // Returns 10 if everything goes okay; otherwise returns 0.

    statistician s, t, u;
    double r = 1000;
    char n[15] = "10000000000000";

    if (s.length( ) || t.length( )) return 0;
    if (s.sum( ) || t.sum( )) return 0;

    memcpy(&r, n, sizeof(double));
    r = 1/r;
    s.next(r);
    if ((s.minimum( ) != r) || (s.maximum( ) != r)) return 0;
    r *= -1;
    t.next(r);
    if ((t.minimum( ) != r) || (t.maximum( ) != r)) return 0;

    u.next(100); u.next(-1); u.next(101); u.next(3);
    if ((u.minimum( ) != -1) || (u.maximum( ) != 101)) return 0;

    return 10;
}

int test3( )
{
    // Test program for + operator of the statistician
    // Returns 10 if everything goes okay; otherwise returns 0.

    statistician s, t, u, v;

    if (s.length( ) || t.length( )) return 0;
    if (s.sum( ) || t.sum( )) return 0;

    t.next(5);
    u.next(0); u.next(10); u.next(10); u.next(20);

    v = s + s;
    if (v.length( ) || v.sum( )) return 0;
    v = s + u;
    if (!(u == v)) return 0;
    v = t + s;
    if (!(t == v)) return 0;
    v = t + u;
    if (v.length( ) != 5) return 0;
    if (!close(v.sum( ), 45)) return 0;
    if (v.minimum( ) != 0) return 0;
    if (v.maximum( ) != 20) return 0;
    if (!close(v.mean( ), 45.0/5)) return 0;
    v = v + t;
    if (v.length( ) != 6) return 0;
    if (!close(v.sum( ), 50)) return 0;
    if (v.minimum( ) != 0) return 0;
    if (v.maximum( ) != 20) return 0;
    if (!close(v.mean( ), 50.0/6)) return 0;
    return 10;
}

int test4( )
{
    // Test program for * operator of the statistician
    // Returns 10 if everything goes okay; otherwise returns 0.

    statistician s, t, u;

    if (s.length( ) || t.length( )) return 0;
    if (s.sum( ) || t.sum( )) return 0;

    u.next(0); u.next(10); u.next(10); u.next(20);
    s = 2*u;
    if (s.length( ) != 4) return 0;
    if (!close(s.sum( ), 80)) return 0;
    if (s.minimum( ) != 0) return 0;
    if (s.maximum( ) != 40) return 0;
    if (!close(s.mean( ), 80.0/4)) return 0;

    s = -2*u;
    if (s.length( ) != 4) return 0;
    if (!close(s.sum( ), -80)) return 0;
    if (s.minimum( ) != -40) return 0;
    if (s.maximum( ) != 0) return 0;
    if (!close(s.mean( ), -80.0/4)) return 0;

    s = 0*u;
    if (s.length( ) != 4) return 0;
    if (!close(s.sum( ), 0)) return 0;
    if (s.minimum( ) != 0) return 0;
    if (s.maximum( ) != 0) return 0;
    if (!close(s.mean( ), 0)) return 0;

    s = 10 * t;
    if (s.length( ) != 0) return 0;
    if (s.sum( ) != 0) return 0;

    return 10;
}

int test5( )
{
    // Test program for == operator of the statistician.
    // Returns 10 if everything goes okay; otherwise returns 0.

    statistician s, t, u, v, w, x;

    if (s.length( ) || t.length( )) return 0;
    if (s.sum( ) || t.sum( )) return 0;

    t.next(10);
    u.next(0); u.next(10); u.next(10); u.next(20);
    v.next(5); v.next(0); v.next(20); v.next(15);
    w.next(0);
    x.next(0); x.next(0);
    
    if (!(s == s)) return 0;
    if (s == t) return 0;
    if (t == s) return 0;
    if (u == t) return 0;
    if (!(u == v)) return 0;
    if (w == x) return 0;

    return 10;
}

// **************************************************************************
// int main(int argc, char *argv[])
//   This is the UCSB CS 24 version.
//   The main program calls one test and prints test ID, and the points
//   earned from that test.
// **************************************************************************
int main(int argc, char *argv[]) {
    
    // Descriptions and points for each of the tests:
    const size_t MANY_TESTS = 5;
    const int POINTS[MANY_TESTS+1] = {
       100,  // Total points for all tests.
        60,  // Test 1 points
        10,  // Test 2 points
        10,  // Test 3 points
        10,  // Test 4 points
        10,  // Test 5 points
    };
    const char DESCRIPTION[MANY_TESTS+1][256] = {
        "tests for statistician class",
        "Testing basic statistician functions",
        "Testing minimum/maximum statistician functions",
        "Testing + operator of the statistician",
        "Testing * operator of the statistician",
        "Testing == operator of the statistician"
    };
    
    int run_a_test(int number, const char message[], int test_function( ), int max);
    
    int result = 0;
    
    typedef int (*testfunc)();
    testfunc tests[5] =  // array of function pointers
    {test1, test2, test3, test4, test5};
    
    if (argc > 1) {
        int testnum = argv[1][0] - '0';
        if (testnum > 0 && testnum <= MANY_TESTS)
            result = run_a_test(testnum, DESCRIPTION[testnum],
                                tests[testnum-1], POINTS[testnum]);
        else {
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

// helper function borrowed from a different exam program by Michael Main
int run_a_test(int number, const char message[], int test_function( ), int max)
{
    int result;
    
    cout << endl << "START OF TEST " << number << ":" << endl;
    cout << message << " (" << max << " points)." << endl;
    result = test_function( );
    if (result > 0)
    {
        cout << "Test " << number << " got " << result << " points";
        cout << " out of a possible " << max << "." << endl;
    }
    else
        cout << "Test " << number << " failed." << endl;
    cout << "END OF TEST " << number << "." << endl << endl;
    
    return result;
}

// Original main function by Michael Main is removed.
