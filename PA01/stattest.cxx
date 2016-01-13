// FILE: stattest.cxx
// An interactive test program for the statistician class
// Written by Michael Main (main@colorado.edu), Aug 2, 1996

#include <cctype>    // Provides toupper
#include <iomanip>   // Provides setw to set the width of an output
#include <iostream>  // Provides cout, cin
#include <cstdlib>   // Provides EXIT_SUCCESS
#include "stats.h"
using namespace main_savitch_2C;
using namespace std;

// PROTOTYPES of functions used in this test program:
void print_menu( );
// Postcondition: A menu of choices for this program has been written to cout.
// Library facilties used: iostream.h

char get_user_command( );
// Postcondition: The user has been prompted to enter a one character command.
// A line of input (with at least one character) has been read, and the first
// character of the input line is returned.

double get_number( );
// Postcondition: The user has been prompted to enter a real number. The
// number has been read, echoed to the screen, and returned by the function.

void print_values(const statistician& s);
// Postcondition: The length, sum, minimum, mean, and maximum of s have been
// written to cout, using a field width of 10 for each of these values.
// (If length is zero, then minimum, mean, and maximum are not written.)

int main( )
{
    statistician s1, s2, s3;  // Three statisticians for us to play with
    char choice;              // A command character entered by the user
    double x;                 // Value for multiplication x*s1

    cout << "Three statisticians s1, s2, and s3 are ready to test." << endl;

    do
    {
        cout << endl;
        print_menu( );
        choice = toupper(get_user_command( ));
        switch (choice)
        {
            case 'R': cout << "Which one should I reset (1, 2, 3) " << endl;
                      choice = get_user_command( );
                      switch (choice)
                      {
			  case '1': s1.reset( );
                                    break;
			  case '2': s2.reset( );
                                    break;
			  case '3': s3.reset( );
                                    break;
                      }
                      cout << "Reset activated for s" << choice << "." << endl;
                      break;
            case '1': s1.next(get_number( ));
                      break;
            case '2': s2.next(get_number( ));
                      break;
            case '3': s3.next(get_number( ));
                      break;
            case 'T': cout << "The values are given in this table:" << endl;
                      cout << "        LENGTH       SUM"
                           << "   MINIMUM      MEAN   MAXIMUM" << endl;
                      cout << "  s1";
                      print_values(s1);
                      cout << "  s2";
                      print_values(s2);
                      cout << "  s3";
                      print_values(s3);
                      break;
            case 'E': if (s1 == s2)
                          cout << "s1 and s2 are equal." << endl;
                      else
                          cout << "s1 and s2 are not equal." << endl;
                      break;
            case '+': s3 = s1 + s2;
                      cout << "s3 has been set to s1 + s2" << endl;
                      break;
            case '*': cout << "Please type a value for x: ";
                      cin >> x;
                      s3 = x * s1;
                      cout << "s3 has been set to " << x << " * s1" << endl;
		      break;
            case 'Q': cout << "Ridicule is the best test of truth." << endl;
                      break;
            default: cout << choice << " is invalid. Sorry." << endl;
        }
    }
    while ((choice != 'Q'));

    return EXIT_SUCCESS;

}

void print_menu( )
{
    cout << endl;
    cout << "The following choices are available: " << endl;
    cout << " R  Activate one of the reset( ) functions" << endl;
    cout << " 1  Add a new number to the 1st statistician s1" << endl;
    cout << " 2  Add a new number to the 2nd statistician s2" << endl;
    cout << " 3  Add a new number to the 3rd statistician s3" << endl;
    cout << " T  Print a table of values from the statisticians" << endl;
    cout << " E  Test whether s1 == s2" << endl;
    cout << " +  Set the third statistician s3 equal to s1 + s2" << endl;
    cout << " *  Set the third statistician s3 equal to x*s1" << endl;
    cout << " Q  Quit this test program" << endl;
}

char get_user_command( )
// Library facilties used: iostream.h
{
    char command;

    cout << "Enter choice: ";
    cin >> command; 
   
    return command;
}

double get_number( )
// Library facilties used: iostream.h
{
    double result;

    cout << "Please enter the next real number for the sequence: ";
    cin  >> result;
    cout << result << " has been read." << endl;
    return result;
}

void print_values(const statistician& s)
// Library facilties used: iostream.h
{
    cout << setw(10) << s.length( );
    cout << setw(10) << s.sum( );
    if (s.length( ) != 0)
    {
        cout << setw(10) << s.minimum( );
        cout << setw(10) << s.mean( );
        cout << setw(10) << s.maximum( );
    }
    else
        cout << "      none      none      none";
    cout << endl;
}
