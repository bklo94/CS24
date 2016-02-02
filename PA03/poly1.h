// FILE: poly1.h
// CLASS PROVIDED:
//   class polynomial (in the namespace main_savitch_3)
//     A polynomial has one variable x, real number coefficients, and
//     non-negative integer exponents. Such a polynomial can be viewed
//     as having the form:
//       A[n]*x^n + A[n-1]*x^(n-1) + ... A[2]*x^2 + A[1]*x + A[0]
//     where the A[n] are the real number coefficients and x^i represents
//     the variable x raised to the i power. The coefficient A[0] is
//     called the "constant" or "zeroth" term of the polynomial.
//   
// NOTES TO STUDENT:
//   1. This version works by storing the coefficients in
//      a dynamic array. The coefficient for the x^k term is stored
//      in location [k] of the dynamic array. When a new term is
//      added beyond the current size of the array, then the
//      dynamic array is replaced by a new, larger array.
//   2. Note that two functions have been implemented as inline functions
//      in this file (the degree and operator() functions).
//
// MEMBER CONSTANTS
//   const static size_t DEFAULT_CAPACITY
//     The size of the initial array to store the coefficients.
//
// CONSTRUCTOR for the polynomial class
//     POSTCONDITION: This polynomial has been created with all zero
//     coefficients, except for coefficient c for the specified exponent.
//     When used as a default constructor (using default values for
//     both arguments), the result is a polynomial with all zero
//     coefficients.
//
// MODIFICATION MEMBER FUNCTIONS for the polynomial class
//   void add_to_coef(double amount, unsigned int exponent)
//     POSTCONDITION: Adds the given amount to the coefficient of the
//     specified exponent.
//
//   void assign_coef(double coefficient, unsigned int exponent)
//     POSTCONDITION: Sets the coefficient for the specified exponent.
//
//   void clear( )
//     POSTCONDITION: All coefficients of this polynomial are set to zero.
//
//   void reserve(unsigned int number)
//     POSTCONDITION: The size of the array for coefficients has been changed 
//     to the requested number (but not less that the size needed to store the
//     current non-zero coefficients). In effect, this guarantees that member
//     functions will not need to allocate new memory for exponents through
//     at least number-1.
//
// CONSTANT MEMBER FUNCTIONS for the polynomial class
//   double coefficient(unsigned int exponent) const
//     POSTCONDITION: Returns coefficient at specified exponent of this
//     polynomial.
//
//   unsigned int degree( ) const
//     POSTCONDITION: The function returns the value of the largest exponent
//     with a non-zero coefficient.
//     If all coefficients are zero, then the function returns zero.
//
//   polynomial derivative( ) const
//     POSTCONDITION: The return value is the first derivative of this 
//     polynomial.
//
//   double eval(double x) const
//     POSTCONDITION: The return value is the value of this polynomial with the
//     given value for the variable x.
//
//   void find_root(
//     double& answer,
//     bool& success,
//     unsigned int& iterations,
//     double starting_guess = 0,
//     unsigned int maximum_iterations = 100,
//     double epsilon = 1e-8
//     )
//     const
//     PRECONDITION: epsilon > 0.
//     POSTCONDITION: This function uses Newton's method to search for a root
//     of the polynomial (i.e., a value of x for which the polynomial is zero).
//     The method requires some starting guess for the value of the root. This
//     guess is improved over a series of iterations (with the maximum allowed
//     iterations defined by the parameter maximum_iterations). There are three
//     possible outcomes:
//     1. SUCCESS:
//        The method hits a near-root (a value of x for which the absolute
//        value of the polynomial is no more than epsilon). In this case, the
//        function sets answer to equal this near-root, success is set to true,
//        and iterations is set to the number of iterations required.
//     2. FLAT FAILURE:
//        Newton's method fails because the guess hits a very flat area of the
//        polynomial (a point where first derivative is no more than epsilon).
//        In this case, the function sets answer equal to the guess that caused
//        flat failure, success is set to false, and iterations is the number
//        of iterations carried out (which will be less than
//        maximum_iterations).
//     3. MAXIMUM ITERATIONS REACHED:
//        The maximum number of iterations is reached without success or flat
//        failure. In this case, the function sets answer to the last guess 
//        tried, success is set to false, and iterations is set to
//        maximum_iterations.
//
//   unsigned int next_term(unsigned int e) const
//     POSTCONDITION: The return value is the next exponent n which is LARGER
//     than e such that coefficient(n) != 0.
//     If there is no such term, then the return value is zero.
//
//   unsigned int previous_term(unsigned int e) const
//     POSTCONDITION: The return value is the next exponent n which is SMALLER
//     than e such that coefficient(n) != 0.
//     If there is no such term, then the return value is UINT_MAX
//     from <climits>.
//
// CONSTANT OPERATORS for the polynomial class
//   double operator( ) (double x) const
//     Same as the eval member function.
//
// NON-MEMBER BINARY OPERATORS for the polynomial Class
//   polynomial operator -(const polynomial& p1, const polynomial& p2)
//     POSTCONDITION: return-value is a polynomial with each coefficient
//     equal to the difference of the coefficients of p1 & p2 for any given
//     exponent.
//
//   polynomial operator +(const polynomial& p1, const polynomial& p2)
//     POSTCONDITION: return-value is a polynomial with each coefficient
//     equal to the sum of the coefficients of p1 & p2 for any given
//     exponent.
//
//   polynomial operator *(const polynomial& p1, const polynomial& p2)
//     POSTCONDITION: Each term of p1 has been multiplied by each term of p2,
//     and the answer is the sum of all these term-by-term products.
//     For example, if p1 is 2x^2 + 3x + 4 and p2 is 5x^2 - 1x + 7, then the
//     return value is 10x^4 + 13x^3 + 31x^2 + 17x + 28.
//
// NON-MEMBER OUTPUT FUNCTION for the polynomial Class
//   ostream& operator << (ostream& out, const polynomial& p)
//     POSTCONDITION: The polynomial has been printed to ostream out, which,
//     in turn, has been returned to the calling function.
//     [CS 24 Note - std::endl is printed following the polynomial]
//
// DYNAMIC MEMORY 
//   Since this class uses dynamic memory, the copy constructor and assignment
//   operator are overridden, and there is a destructor implemented. Also,
//   if there is insufficient dynamic memory, the following functions throw
//   a bad_alloc exception: the constructors, assignment, reserve, add_to_coef,
//   assign_coef, and any function that returns a polynomial.

#ifndef POLY1_H
#define POLY1_H
#include <iostream>  // Provides ostream

namespace main_savitch_4
{
    
    class polynomial
    {
    public:
	// CONSTANTS
	static const unsigned int DEFAULT_CAPACITY = 30;
	
        // CONSTRUCTORS and DESTRUCTOR
	polynomial(double c = 0.0, unsigned int exponent = 0);
	polynomial(const polynomial& source);
	~polynomial( );

	// MODIFICATION MEMBER FUNCTIONS
	polynomial& operator =(const polynomial& source);
	void add_to_coef(double amount, unsigned int exponent);
	void assign_coef(double coefficient, unsigned int exponent);
	void clear( );
    void reserve(unsigned int number);
	
	// CONSTANT MEMBER FUNCTIONS
	double coefficient(unsigned int exponent) const;
	unsigned int degree( ) const { return current_degree; }
	polynomial derivative( ) const;
	double eval(double x) const;
	void find_root(
	    double& answer,
	    bool& success,
	    unsigned int& iterations,
	    double guess = 0,
	    unsigned int maximum_iterations = 100,
	    double epsilon = 1e-8
	    )
	    const;
	unsigned int next_term(unsigned int e) const;
	unsigned int previous_term(unsigned int e) const;
	
	// CONSTANT OPERATORS
	double operator( ) (double x) const { return eval(x); }
	
    private:
	double *coef;                 // Pointer to the dynamic array
	unsigned int size;            // Current size of the dynamic array
	unsigned int current_degree;  // Current degree of the polynomial
    };
    
    // NON-MEMBER BINARY OPERATORS
    polynomial operator +(const polynomial& p1, const polynomial& p2);
    polynomial operator -(const polynomial& p1, const polynomial& p2);
    polynomial operator *(const polynomial& p1, const polynomial& p2);
    
    // NON-MEMBER OUTPUT FUNCTION
    std::ostream& operator << (std::ostream& out, const polynomial& p);

}
#endif
