// FILE: poly2.h
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
//      a doubly-linked list with each node holding the coefficient and
//      exponent for one term. The terms are kept in order from smallest
//      to largest exponent. Each polynomial also maintains a pointer to the
//      most recently accessed node.
//   2. Note that two functions have been implemented as inline functions
//      in this file (the degree and operator() functions).
//   3. An implementation of the make_gif function is available for
//      students to use at www.cs.colorado.edu/~main/projects/polygif.cxx.
//
// CONSTRUCTOR for the polynomial class
//     POSTCONDITION: This polynomial has been create with all zero
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
// NON-MEMBER OUTPUT FUNCTIONS for the polynomial Class
//   ostream& operator << (ostream& out, const polynomial& p)
//     POSTCONDITION: The polynomial has been printed to ostream out, which,
//     in turn, has been returned to the calling function.
//
// DYNAMIC MEMORY 
//   Since this class uses dynamic memory, the copy constructor and assignment
//   operator are overridden, and there is a destructor implemented. Also,
//   if there is insufficient dynamic memory, the following functions throw
//   a bad_alloc exception: the constructors, assignment, reserve, add_to_coef,
//   assign_coef, and any function that returns a polynomial.

#ifndef POLY2_H
#define POLY2_H
#include <cstdlib>   // Provides nullptr
#include <iostream>  // Provides ostream
#include <cmath>	 // provides pow()
#include <climits>   // Provides UINT_MAX
#include <limits>	 // provides machine epsilon

// If your compiler does not support namespaces, then please delete the
// following line and the set of brackets that follow.
namespace main_savitch_5
{
    class polynode
    {
		public:
		// CONSTRUCTOR: Creates a node containing a specified initial
		// coefficient (init_coef), initial exponent (init_exponent), and
		// initial links forward and backward (init_fore and init_back).
		polynode(
			double init_coef = 0.0,
			unsigned int init_exponent = 0,
			polynode* init_fore = NULL,
			polynode* init_back = NULL
	    )
	    {
			coef_field = init_coef;
			exponent_field = init_exponent;
			link_fore = init_fore;
			link_back = init_back;
	    }

		// Member functions to set the fields: 
    	void set_coef(double new_coef)
	    { coef_field = new_coef; }
    	void set_exponent(unsigned int new_exponent)
	    { exponent_field = new_exponent; }
    	void set_fore(polynode* new_fore)
	    { link_fore = new_fore; }
    	void set_back(polynode* new_back)
	    { link_back = new_back; }

		// Const member functions to retrieve current coefficient or exponent:
		double coef( ) const { return coef_field; }
		unsigned int exponent( ) const { return exponent_field; }

		// Two slightly different member functions to retrieve each link:
		const polynode* fore( ) const { return link_fore; }
		polynode* fore( )             { return link_fore; }
		const polynode* back( ) const { return link_back; }
    	polynode* back( )             { return link_back; }
	
    private:
		double coef_field;
		unsigned int exponent_field;
		polynode *link_fore;
		polynode *link_back;
    };

    class polynomial
    {
		public:
			// CONSTRUCTORS and DESTRUCTOR
			polynomial(double c = 0.0, unsigned int exponent = 0);
			polynomial(const polynomial& source);
			~polynomial( );

			// MODIFICATION MEMBER FUNCTIONS
			polynomial& operator =(const polynomial& source);
			void add_to_coef(double amount, unsigned int exponent);
			void assign_coef(double coefficient, unsigned int exponent);
			void clear( );
	
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
			) const;
			unsigned int next_term(unsigned int e) const;
			unsigned int previous_term(unsigned int e) const;
	
			// CONSTANT OPERATORS
			double operator( ) (double x) const { return eval(x); }
	
		private:
			double EPSILON;
			
			polynode *head_ptr;             // Head pointer for list of terms
			polynode *tail_ptr;             // Tail pointer for list of terms
			mutable polynode *recent_ptr;   // Most recently used term
			unsigned int current_degree;    // Current degree of the polynomial
			// A private member function to aid the other functions:
			void set_recent(unsigned int exponent) const;
    };
    
    // NON-MEMBER BINARY OPERATORS
    polynomial operator +(const polynomial& p1, const polynomial& p2);
    polynomial operator -(const polynomial& p1, const polynomial& p2);
    polynomial operator *(const polynomial& p1, const polynomial& p2);
    
    // NON-MEMBER OUTPUT FUNCTIONS
    std::ostream& operator << (std::ostream& out, const polynomial& p);
}

    

#endif
