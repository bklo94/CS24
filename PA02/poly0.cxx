//FILE poly0.cxx
//Brandon Lo, 1/13/15


//BETTER DOCUMENTATION HERE
// SAME DOCUMENTATION. BEST DOCUMENTATION.
//https://webcache.googleusercontent.com/search?q=cache:1GSV7Y-oDgEJ:https://www.cs.colorado.edu/~main/projects/chap03b.html+&cd=2&hl=en&ct=clnk&gl=us&client=ubuntu
// PROBABLY TOO ADVANCED. BUT SIMILAR
// https://webcache.googleusercontent.com/search?q=cache:vr2hFHzTcOcJ:https://www.cs.colorado.edu/~main/projects/chap03c.html+&cd=3&hl=en&ct=clnk&gl=us&client=ubuntuhttps://webcache.googleusercontent.com/search?q=cache:vr2hFHzTcOcJ:https://www.cs.colorado.edu/~main/projects/chap03c.html+&cd=3&hl=en&ct=clnk&gl=us&client=ubuntu

#include <climits>   // Provides UINT_MAX
#include <cmath>     // Provides fabs
#include <cstdlib>   // Provides rand
#include <cstring>   // Provides memcpy
#include <iostream>  // Provides cout
#include <cassert>  // provides assert
#include <algorithm> //provides fill_n
#include <string>    // provides string
#include <sstream>
#include "poly0.h"  // defines what must be implemented

//   class polynomial (in the namespace main_savitch_3)
//     A polynomial has one variable x, real number coefficients, and
//     non-negative integer exponents. Such a polynomial can be viewed
//     as having the form:
//       A[n]*x^n + A[n-1]*x^(n-1) + ... A[2]*x^2 + A[1]*x + A[0]
//     where the A[n] are the real number coefficients and x^i represents
//     the variable x raised to the i power. The coefficient A[0] is
//     called the "constant" or "zeroth" term of t  wwhe polynomial.

namespace main_savitch_3
{

// NEEDED GLOBALS
const unsigned int polynomial::CAPACITY;
const unsigned int polynomial::MAX_EX;

// CONSTRUCTOR for the polynomial class
//   polynomial(double c = 0.0, unsigned int exponent = 0)
//     PRECONDITION: exponent <= MAX_EX.
//     POSTCONDITION: This polynomial has been create with all zero
//     coefficients, except for coefficient c for the specified exponent.
//     When used as a default constructor (using default values for
//     both arguments), the result is a polynomial with all zero
//     coefficients.

//THIS WORKS
polynomial::polynomial (double c, unsigned int exponent){
  assert(exponent <= MAX_EX);
  clear (); //THE ORDER COUNT FOR CLEAR
  current_degree = 0;
  assign_coef(c,exponent);
}

// NOTES TO STUDENT:
//   1. This version works by storing the coefficients in
//      a fixed array. The coefficient for the x^k term is stored
//      in location [k] of the fixed-size array. Later we will modify
//      the implementation to use a dynamic array.
//   2. Note that two functions have been implemented as inline functions
//      in this file (the degree and operator() functions).
//
// MEMBER CONSTANTS
//   const static size_t CAPACITY
//     The size of the fixed array to store the coefficients.
//   const static size_t MAX_EX = CAPACITY - 1;
//     The maximum exponent permitted.

// MEMBER CONSTANTS ALREADY CALLED

// MODIFICATION MEMBER FUNCTIONS for the polynomial class
//   void add_to_coef(double amount, unsigned int exponent)
//     PRECONDITION: exponent <= MAX_EX.
//     POSTCONDITION: Adds the given amount to the coefficient of the
//     specified exponent.

// THIS WORKS
void polynomial::add_to_coef (double amount, unsigned int exponent){
  assert(exponent <= MAX_EX);
  assign_coef((amount + coefficient(exponent)), exponent);
}

//   void assign_coef(double coefficient, unsigned int exponent)
//     PRECONDITION: exponent <= MAX_EX.
//     POSTCONDITION: Sets the coefficient for the specified exponent.


// SETS CURRENT_DEGREE AND ALSO SETS COEFFICIENT
//THIS WORKS
void polynomial::assign_coef(double coefficient, unsigned int exponent){
  assert(exponent <= MAX_EX);
  coef[exponent] = coefficient;

  //SETS THE CURRENT_DEGREE
  if (exponent > current_degree && coefficient != 0)
    current_degree = exponent;
  if(current_degree == exponent && coefficient == 0 && current_degree != 0){
     if(previous_term(current_degree) == UINT_MAX){
       current_degree = 0;
     }
     else{
       current_degree = previous_term(current_degree);
     }
  }
}

//   void clear( )
//     POSTCONDITION: All coefficients of this polynomial are set to zero.


//PROBABLY CORRECT.(PROBLEM???CORRECT??? ONLY CLEARS CURRENT POLYNOMIAL)
//THIS WORKS ACCORDING TO TEST
void polynomial::clear(){
  std::fill_n(coef,CAPACITY,0.0); //FILL ARRAY COEF WITH 0.0 AKA CLEARING IT
  current_degree = 0;
}

// CONSTANT MEMBER FUNCTIONS for the polynomial class
//   double coefficient(unsigned int exponent) const
//     POSTCONDITION: Returns coefficient at specified exponent of this
//     polynomial.
//     NOTE: for exponents > MAX_EX, the return value is always zero.


// PROBABLY CORRECT. CALLS THE COEFFICIENT UNLESS THE IF ACTIVATED
double polynomial::coefficient(unsigned int exponent) const{
  if (exponent > MAX_EX){
    return 0.0;
  }
  else{
    return coef[exponent];
  }
}

//   unsigned int degree( ) const
//     POSTCONDITION: The function returns the value of the largest exponent
//     with a non-zero coefficient.
//     If all coefficients are zero, then the function returns zero.

// THIS DEGREE IS SET IN THE HEADER FILE

//   polynomial derivative( ) const
//     POSTCONDITION: The return value is the first derivative of this
//     polynomial.

//USED POWER RULE. NEEDS A FOR LOOP.
// THIS WORKS.
polynomial polynomial::derivative() const{
  polynomial p(0.0,0);
		int n = 0;
		while ((n = this->next_term(n)) != 0){
			double c = coefficient(n);
			p.assign_coef(c * (n), n - 1); //POWER RULE. COEFICCIENT TIMES N, AND EXPONENT MINUS 1.
		}
		return p;
}

//   double eval(double x) const
//     POSTCONDITION: The return value is the value of this polynomial with the
//     given value for the variable x.


//THIS WORKS
double polynomial::eval(double x) const{
  double value = 0.0;
   int n = 0;
   value +=  coefficient(n); //adds up all the coefficients
   while ((n = next_term(n)) != 0){
     value += coefficient(n) * pow(x, n); //returns value is the value of the polynomial in c * x ^n form.
   }
   return value;
}

//   unsigned int next_term(unsigned int e) const
//     POSTCONDITION: The return value is the next exponent n which is LARGER
//     than e such that coefficient(n) != 0.
//     If there is no such term, then the return value is zero.


//WORKING NOW
unsigned int polynomial::next_term(unsigned int e) const{
  unsigned int n;
  if(e < degree()){
  for(n = e+1; n <= degree(); n++) // Goes forward until it hits the exponent
    if(coefficient(n) != 0.0) // POSTCONDITION
      return n;
    }
    return 0; //if coefficient (n) == 0; it has found the next term
}

//   unsigned int previous_term(unsigned int e) const
//     POSTCONDITION: The return value is the next exponent n which is SMALLER
//     than e such that coefficient(n) != 0.
//     If there is no such term, then the return value is UINT_MAX
//     from <climits>.


//WORKING NOW
unsigned int polynomial::previous_term (unsigned int e) const{
  unsigned int n = e;
  if (e == 0){
    return UINT_MAX; //UINTMAX IS MAX UNSIGNED INT
  }
  do{
  if( n > degree()){
      return degree();
    }
    n--; // goes backwards 1 term
  if(coefficient(n) != 0.0){
      return n;
    }
  }while(n>0);
  return UINT_MAX;
  }

// CONSTANT OPERATORS for the polynomial class
//   double operator( ) (double x) const
//     Same as the eval member function.
// NON-MEMBER BINARY OPERATORS for the polynomial Class
//   polynomial operator -(const polynomial& p1, const polynomial& p2)
//     POSTCONDITION: return-value is a polynomial with each coefficient
//     equal to the difference of the coefficients of p1 & p2 for any given
//     exponent.


//WORKING
polynomial operator -(const polynomial& p1, const polynomial& p2){
  polynomial p(0.0,0);
		int n1 = 0,
		    n2 = 0,
		    n = 0;
		do{ //DOES THE OPERATOR AND FINDS THE DIFFERENCE AND PUTS IT INTO NEW POLYNOMIAL P
			double q1 = p1.coefficient(n);
			double q2 = p2.coefficient(n);
			if (q1 - q2 != 0){
				p.assign_coef(q1 - q2, n);
			}

			n1 = p1.next_term(n);
			n = p2.next_term(n);

      //Assigns for exponent. Finds the exponent because p1 & p2 passes by reference
			if (n1 == 0){
				n = n2;
			}
      else if (n2 == 0){
				n = n1;
			}
      else{
				n = n1;
			if (n > n2){
					n = n2;
				}
			}
		}while (n != 0); //if both the coefficients aren't 0, q-q2 !=0 is another check.

		return p;
}

//   polynomial operator +(const polynomial& p1, const polynomial& p2)
//     POSTCONDITION: return-value is a polynomial with each coefficient
//     equal to the sum of the coefficients of p1 & p2 for any given
//     exponent.


//WORKING
polynomial operator +(const polynomial& p1, const polynomial& p2){
  polynomial p(0.0,0);
		int n1 = 0,
        n2 = 0,
		    n = 0;
		do{
			double q1 = p1.coefficient(n);
			double q2 = p2.coefficient(n);
			if (q1 + q2 != 0){
				p.assign_coef(q1 + q2, n); //SUMS OPERATOR AND SETS AS NEW P.
			}
			n1 = p1.next_term(n);
			n2 = p2.next_term(n);

      // LOOKS FOR THE COEFFICIENT
      if (n1 == 0){
        n = n2;
      }
      else if (n2 == 0){
        n = n1;
      }
      else{
        n = n1;
      if (n > n2){
          n = n2;
        }
      }
      }while (n != 0);

		return p;
}

//   polynomial operator *(const polynomial& p1, const polynomial& p2)
//     PRECONDITION: p1.degree( ) + p2.degree( ) <= polynomial::MAX_EX.
//     POSTCONDITION: Each term of p1 has been multiplied by each term of p2,
//     and the answer is the sum of all these term-by-term products.
//     For example, if p1 is 2x^2 + 3x + 4 and p2 is 5x^2 - 1x + 7, then the
//     return value is 10x^4 + 13x^3 + 31x^2 + 17x + 28.


//WORKING
polynomial operator *(const polynomial& p1, const polynomial&p2){
  assert(p1.degree() + p2.degree() <= polynomial::MAX_EX);
  polynomial p(0.0, 0);
		int n1 = 0;
		do{
			double q1 = p1.coefficient(n1); //GRABS P1 COEFFICIENT
			int n2 = 0;
			do{
				double q2 = p2.coefficient(n2); // GRABS P2 COEFFICIENT
				double result = q1 * q2; // MULTIPLIES COEFFICIENTS
				p.add_to_coef(result, n1 + n2); // COEFFICIENT SET
				n2 = p2.next_term(n2); //GOES TO NEXT TERM
			}while(n2 != 0);
			n1 = p1.next_term(n1); //GOES TO NEXT TERM
		}while(n1 != 0);

		return p;
}

// NON-MEMBER OUTPUT FUNCTION for the polynomial Class
//   ostream& operator << (ostream& out, const polynomial& p)
//     POSTCONDITION: The polynomial has been printed to ostream out, which,
//     in turn, has been returned to the calling function


//WORKING
std::ostream& operator << (std::ostream& out, const polynomial& p){
	unsigned int i = p.degree( );
	double number;

	// Each iteration of this loop prints one term of the polynomial:
	do
	{
	    // Get the coefficient:
	    number = p.coefficient(i);

	    // Print a sign
      /*      ...there are three possibilities:
            "-"   in front of the first term if it is negative
            " - " in front of other negative terms
            " + " in front of positive terms (except if it is first term)
      */
      if(i == p.degree() && number<0)
  		    out << "-";
  		else if(number < 0)
  		    out << " - ";
  		else if(number > 0 && i != p.degree())
  		    out << " + ";
	    // Get rid of any negative sign in the number:
	    number = fabs(number);

	    // Print the number, variable x, and exponent
      /*      ...print the number only when it is not 1.0 or it is the
               constant term
            ...print the letter x only when the exponent is above zero
            ...print the exponent only when it is above one
      */

  		if(number != 1.0 || i == 0){
  		    out << number;
        }
  		if(i > 1){
  		    out << "x^" << i;
        }
  		if(i == 1){
  		    out << "x";
        }

	    // Move to the next lowest term:
	    i = p.previous_term(i);
	}   while (i != UINT_MAX);

	return out << '\n';     //return the output stream
}

}
