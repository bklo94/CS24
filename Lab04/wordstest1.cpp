// wordstest1.cpp
// An interactive test program for class Words
// mostly adapted by cmc from Professor Main's
// sequence_test.cxx, 10/16/2015

#include <cctype>
#include <iostream>
#include "words2.h"
using namespace std;
using namespace lab04_2;

// PROTOTYPES for functions used by this test program:
void print_menu( );
char get_user_command( );
void show_words(Words display);
string get_word( );
unsigned int get_index(const char *why);

int main( )
{
    Words test;
    char choice;
    unsigned int index;

    cout << "I have initialized an empty Words object." << endl;

    do
    {
        print_menu( );
        choice = toupper(get_user_command( ));
        switch (choice)
        {
            case 'P': show_words(test);
                      break;
            case 'S': cout << "Size is " << test.size( ) << '.' << endl;
                      break;
            case 'C': cout << "Capacity is " << test.get_capacity( )
                      << '.' << endl;
                      break;
            case 'A': test.append(get_word( ));
                      break;
            case 'G': index = get_index("get");
                      cout << "The word at index " << index <<
                          " is " << test[index] << "." << endl;
                      break;
            case 'M': index = get_index("modify");
                      test[index] = get_word();
                      cout << "The word at index " << index <<
                          " was modified." << endl;
                      break;
            case 'Q': cout << "Bye." << endl;
                      break;
            default:  cout << choice << " is invalid." << endl;
        }
    }
    while ((choice != 'Q'));

    return 0;
}

void print_menu( )
{
    cout << endl;
    cout << "The following choices are available: " << endl;
    cout << " P   Print a copy of all words" << endl;
    cout << " S   Print the result from the size( ) function" << endl;
    cout << " C   Print the result from get_capacity function" << endl;
    cout << " A   Append a new word with the append(...) function" << endl;
    cout << " G   Get a word with constant operator[] function" << endl;
    cout << " M   Modify a word with mutable operator[] function" << endl;
    cout << " Q   Quit this test program" << endl;
}

char get_user_command( )
{
    char command;

    cout << "Enter choice: ";
    cin >> command;

    return command;
}

void show_words(Words display)
{
    for (int i=0; i < display.size(); i++)
        cout << display[i] << endl;
}

string get_word( )
{
    string result;

    cout << "Enter a word: ";
    cin  >> result;
    cout << result << " has been read." << endl;
    return result;
}

unsigned int get_index(const char *why)
{
    unsigned int result;
    cout << "Enter index to " << why << ": ";
    cin >> result;
    return result;
}
