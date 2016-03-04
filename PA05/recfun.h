// recfun.h - defines four functsions from Main's Fun with Recursion projects
// Do not change this file - you will not turn it in.

#ifndef RECFUN_H
#define RECFUN_H

#include <iostream>
#include <string>
using std::ostream;
using std::string;

void triangle(ostream& outs, unsigned int m, unsigned int n);
// Precondition: m <= n
// Postcondition: The function has printed a pattern of 2*(n-m+1) lines
// to the output stream outs. The first line contains m asterisks, the next
// line contains m+1 asterisks, and so on up to a line with n asterisks.
// Then the pattern is repeated backwards, going n back down to m.
/* Example output:
     triangle(cout, 3, 5) will print this to cout:
     ***
     ****
     *****
     *****
     ****
     ***
 */

void numbers(ostream& outs, const string& prefix, unsigned int levels);
// Postcondition: The function prints output to the ostream outs.
// The output consists of the string prefix followed by "section numbers"
// of the form 1.1., 1.2., 1.3., and so on. The levels argument determines
// how many levels the section numbers have. For example, if levels is 2,
// then the section numbers have the form x.y. If levels is 3, then
// section numbers have the form x.y.z. The digits permitted in each
// level are always '1' through '9'.
/* As an example, if prefix is the string "THERBLIG" and levels is 2,
   then the function would start by printing:

   THERBLIG1.1.
   THERBLIG1.2.
   THERBLIG1.3.

   and end (after 75 intervening lines) by printing:

   THERBLIG9.7.
   THERBLIG9.8.
   THERBLIG9.9.
*/

bool bears(int n);
// Postcondition: A true return value means that it is possible to win
// the bear game by starting with n bears. A false return value means that
// it is not possible to win the bear game by starting with n bears.
// Examples:
//   bear(250) is true, decided by recursion as follows:
//      bear(250) -> divisible by 5, so give back 42, leaving 208
//          bear(208) -> is even, so give back half, leaving 104
//              bear(104) -> is even, so give back half, leaving 52
//                  bear(52) -> divisible by 4, so give back 5*2, leaving 42
//                      bear(42) -> done!
//   bear(42) is true
//   bear(84) is true
//   bear(53) is false
//   bear(41) is false

void pattern(ostream& outs, unsigned int n, unsigned int i);
// Precondition: n is a power of 2 greater than zero.
// Postcondition: A pattern based on the example below has been
// printed to the ostream outs. The longest line of the pattern has
// n stars beginning in column i of the output. For example,
// the pattern below is produced by the call pattern(cout, 8, 0).
/* Example pattern:
 
*
* *
  *
* * * *
    *
    * *
      *
* * * * * * * *
        *
        * *
          *
        * * * *
            *
            * *
              *

*/

#endif
