// poly2.cxx - implements poly2.h version of class polynomial
// Brandon Lo, 2/21/16

// INVARIANT for the polynomial class:
//   1. head_ptr and tail_ptr are the head and tail pointers for a
//      doubly-linked list of nodes that contain the polynomial's terms in
//      order from smallest to largest exponent. To simplify certain operations,
//      we always keep a node for the zero-order term (x^0), but other nodes are
//      kept only if the coefficient is non-zero.
//   2. We always maintain recent_ptr as a pointer to some node in the
//      list--preferably the most recently used node. If the list is null,
//      then we set recent_ptr to null.
//   3. The degree of the polynomial is stored in current_degree
//      (using zero for the case of all zero coefficients).
// INVARIANT for the polynomial class:
//   1. head_ptr and tail_ptr are the head and tail pointers for a
//      doubly-linked list of nodes that contain the polynomial's terms in
//      order from smallest to largest exponent. To simplify certain operations,
//      we always keep a node for the zero-order term (x^0), but other nodes are
//      kept only if the coefficient is non-zero.
//   2. We always maintain recent_ptr as a pointer to some node in the
//      list--preferably the most recently used node. If the list is null,
//      then we set recent_ptr to null.
//   3. The degree of the polynomial is stored in current_degree
//      (using zero for the case of all zero coefficients).


#include "poly2.h"
#include <cmath>
#include <climits>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include "poly2.h"
#include <limits>
using namespace std;

namespace main_savitch_5
{
double EPSILON; //creates a global epsiolon value
polynomial::polynomial(const polynomial& source){
	head_ptr = new polynode();
	tail_ptr = head_ptr;
	recent_ptr = head_ptr;
	current_degree = 0;
	*this = source;
}

polynomial::~polynomial(){
    //deconstructor used to delete the head pointers and set to null
	clear();
	current_degree = 0;
	delete head_ptr;
	head_ptr = NULL;
	tail_ptr = NULL;
	recent_ptr = NULL;
}

polynomial::polynomial(double c, unsigned int exponent){
	double EPSILON = std::numeric_limits<double>::epsilon();
	if(fabs(c) < EPSILON){ //if value is very small then as start of list
		head_ptr = new polynode();
		tail_ptr = head_ptr;
		recent_ptr = head_ptr;
		current_degree = 0;
	}
	else{
		if(exponent == 0){ //if new exponent has nothing so like 3
			tail_ptr = new polynode(c, exponent);
			tail_ptr = head_ptr; //sets first pointer
			recent_ptr = head_ptr;
			current_degree = 0;
		}
		else{ //create a polynomial with expoenent
			head_ptr = new polynode();
			tail_ptr = new polynode(c, exponent, NULL, head_ptr);
			head_ptr->set_fore(tail_ptr);
			recent_ptr = tail_ptr;
			current_degree = exponent;
		}
	}
}

//     POSTCONDITION: All coefficients of this polynomial are set to zero.
void polynomial::clear(){
	polynode* temp = head_ptr;
	while (head_ptr->fore() != NULL) { //while loop to go through everything
		temp = head_ptr->fore();
		head_ptr->set_fore(temp->fore());
		delete temp; //clears everything
	}
	head_ptr->set_coef(0); //Set coefficient to 0
	head_ptr->set_exponent(0); //Also set expoenent to 0 just in case
	tail_ptr = head_ptr;
	recent_ptr = head_ptr;
	current_degree = 0;
}

//     POSTCONDITION: Returns coefficient at specified exponent of this
//     polynomial.
double polynomial::coefficient(unsigned int exponent) const{
    polynode *temp = head_ptr;
		while (temp != NULL){ //returns all the coef as long as not empty
			if (temp->exponent() == exponent){
				return temp->coef(); //sets head_ptr as coef
			}
			temp = temp->fore();
	}
	return 0;
}

//     POSTCONDITION: Adds the given amount to the coefficient of the
//     specified exponent.

void polynomial::add_to_coef(double amount, unsigned int exponent){
	set_recent(exponent);
	if(recent_ptr->exponent() == exponent){ //cehcks for expoenent
		double current = recent_ptr->coef();
		assign_coef((current + amount), exponent); //if there is something already there, then you add
	}
	else{ //if nothing is there then you just default assign
		assign_coef(amount, exponent);
	}
}
//     POSTCONDITION: Sets the coefficient for the specified exponent.
/*
Implement the new assign_coef function. After calling set_recent(exponent), my [Professor Main's] implementation had these cases:
If there is a zero coefficient and exponent greater than current degree
(return with no further work).
Else if there is currently no node for the given exponent
(so that recent_ptr->exponent( ) is less than the new exponent),
then a new node is created with the given exponent and inserted here
 (with special handling if this new node becomes the end of the list)
 .
Else if the coefficient is non-zero or the exponent is zero
(in both these cases, we just change the coefficient of a node).
Else if the exponent equals the current degree. In this case,
the coefficient is zero (otherwise we would have hit the previous case),
so we remove the tail node, set the recent_ptr to the new tail, and
 reduce the current degree.
Else...in this last case we must have a new zero coefficient for a
 node that is neither the head nor the tail. We just remove this
 node and set the recent_ptr to the next node in the list.Implement
  the new assign_coef function. After calling set_recent(exponent),
  my [Professor Main's] implementation had these cases:
If there is a zero coefficient and exponent greater than current degree
(return with no further work).
Else if there is currently no node for the given exponent
(so that recent_ptr->exponent( ) is less than the new exponent),
then a new node is created with the given exponent and inserted
here (with special handling if this new node becomes the end of the list).
Else if the coefficient is non-zero or the exponent is zero
(in both these cases, we just change the coefficient of a node).
Else if the exponent equals the current degree. In this case,
the coefficient is zero (otherwise we would have hit the previous case),
so we remove the tail node, set the recent_ptr to the new tail, and reduce
the current degree.
Else...in this last case we must have a new zero coefficient
 for a node that is neither the head nor the tail. We just remove
  this node and set the recent_ptr to the next node in the list.
*/

void polynomial::assign_coef(double coefficient, unsigned int exponent){
	EPSILON = std::numeric_limits<double>::epsilon();
	set_recent(exponent);
    if (coefficient == 0 && exponent > current_degree){
			return; //first if loop
        }
	else if(fabs(coefficient) >= EPSILON){
		if(recent_ptr->exponent() == exponent){ //looks for the exponent
			recent_ptr->set_coef(coefficient);
		}
		else{
			if(recent_ptr->fore() != NULL){ //checks to see if list is new/empty
				polynode *temp = new polynode(coefficient, exponent, recent_ptr->fore(), recent_ptr);
				recent_ptr->fore()->set_back(temp);
				recent_ptr->set_fore(temp);
			}
			else{ //
				polynode *temp = new polynode(coefficient, exponent, NULL, recent_ptr);
				recent_ptr->set_fore(temp);
				tail_ptr = temp;
			}
		}
	}
	else if(recent_ptr->exponent() == exponent){// looks for exponent
			if(head_ptr != recent_ptr){ //searches for correct pointer
				if(recent_ptr->fore() != NULL){ //moves the pointer up
					recent_ptr->back()->set_fore(recent_ptr->fore());
					recent_ptr->fore()->set_back(recent_ptr->back());
					delete recent_ptr;
				}
				else{ //sets the trail as the pointer
					set_recent(recent_ptr->back()->exponent());
					delete recent_ptr->fore();
					recent_ptr->set_fore(NULL); //recent_ptr is at end of list
					tail_ptr = recent_ptr;
				}
			}
			else{
				head_ptr->set_coef(0.0);
			}
		}
	current_degree = tail_ptr->exponent(); //sets current degree
}
//     POSTCONDITION: The return value is the next exponent n which is LARGER
//     than e such that coefficient(n) != 0.
//     If there is no such term, then the return value is zero.
/*Hint for next_term: Start by calling set_recent(e).
Normally, the right answer is then in the node after
recent_ptr (but there is one exception that you should handle).
*/
unsigned int polynomial::next_term(unsigned int exponent) const{
	set_recent(exponent);
	if(recent_ptr->fore() != NULL){ //checks exception
		return recent_ptr->fore()->exponent();
	}
	return 0; //no such term
}
//     POSTCONDITION: The return value is the next exponent n which is SMALLER
//     than e such that coefficient(n) != 0.
//     If there is no such term, then the return value is UINT_MAX
//     from <climits>.
/*Hint for previous_term:
Start by checking the special case where e is zero.
Then call set_recent(e-1). Normally, the right answer is
then in the recent_ptr node (but again, there is one exception that
you need to handle--the case where the node has exponent and coefficient of zero).
*/
unsigned int polynomial::previous_term(unsigned int exponent) const{
	if(exponent == 0){ //Checks special case
		return UINT_MAX;
	}
	set_recent(exponent);
	if(recent_ptr->exponent() < exponent){
		if(recent_ptr == head_ptr && fabs(recent_ptr->coef()) >= EPSILON){
			return 0;
		}
		if (recent_ptr == head_ptr && fabs(recent_ptr->coef()) < EPSILON){
			return UINT_MAX;
		}
		return recent_ptr->exponent(); //right answer in recent_ptr node
	}
	else{
		if (recent_ptr->back()->coef() == 0) //special case
			return UINT_MAX;
		return recent_ptr->back()->exponent();
	}
}
//The set_recent function will set the recent_ptr to the node that contains the requested exponent. If there is no such exponent, then recent_ptr should be set to the last node that is still less than the specified exponent. Note that set_recent is a const member function, but that it can still change the mutable recent_ptr member variable. My implementation of set_recent used three cases:
//If the requested exponent is zero, then set recent_ptr to the head of the list.
//Else if the exponent is greater than or equal to the current degree, then set recent_ptr to the tail of the list.
//Else if the exponent is smaller than the exponent in the recent node, then move the recent_ptr backward as far as needed.
//Else move the recent_ptr forward as far as needed.
/* The set_recent function will set the recent_ptr to the node that contains the requested exponent. If there is no such exponent, then recent_ptr should be set to the last node that is still less than the specified exponent. Note that set_recent is a const member function, but that it can still change the mutable recent_ptr member variable. My implementation of set_recent used three cases:
If the requested exponent is zero, then set recent_ptr to the head of the list.
Else if the exponent is greater than or equal to the current degree, then set recent_ptr to the tail of the list.
Else if the exponent is smaller than the exponent in the recent node, then move the recent_ptr backward as far as needed.
Else move the recent_ptr forward as far as needed.
*/
void polynomial::set_recent(unsigned int exponent) const{
	if (exponent == 0){ //If the requested exponent is zero, then set recent_ptr to the head of the list.If the requested exponent is zero, then set recent_ptr to the head of the list.
		recent_ptr = head_ptr;
		return;
	}
	else if (exponent >= current_degree){ //1st elseif
		recent_ptr = tail_ptr;
		return;
	}
	else if (exponent > recent_ptr->exponent()){ // second elseif
		while (recent_ptr->fore()->exponent() <= exponent){
			recent_ptr = recent_ptr->fore();
		}
	}
	else if (exponent < recent_ptr->exponent()){ //third elseif
		while (recent_ptr->back()->exponent() >= exponent){
			recent_ptr = recent_ptr->back();
		}
		if (recent_ptr->exponent() != exponent){// if thing up top
			recent_ptr = recent_ptr->back();
        }
	}
}


double polynomial::eval(double x) const{
	double total = 0;
	set_recent(0);
	while(recent_ptr != NULL){
		total += pow(x, recent_ptr->exponent()) * recent_ptr->coef();
		recent_ptr = recent_ptr->fore();
	}
	return total;
}
//     POSTCONDITION: The return value is the first derivative of this
//     polynomial.//     POSTCONDITION: The return value is the first derivative of this
//     polynomial.
polynomial polynomial::derivative() const{
	polynomial deriv;
	set_recent(0);
	while(recent_ptr != NULL){
		if(recent_ptr->exponent() != 0){
			deriv.assign_coef(recent_ptr->coef() * recent_ptr->exponent(), recent_ptr->exponent()-1);
		}
		recent_ptr = recent_ptr->fore();//rreturns first derivative
	}
	return deriv;
}
//     POSTCONDITION: return-value is a polynomial with each coefficient
//     equal to the sum of the coefficients of p1 & p2 for any given
polynomial operator +(const polynomial& p1, const polynomial& p2) {
	polynomial result(p1);
	for (unsigned int e = 0; e <= p2.degree(); e++)
		if (p2.coefficient(e) != 0.0)
			result.add_to_coef(p2.coefficient(e), e);
	return result;
}

//     POSTCONDITION: return-value is a polynomial with each coefficient
//     equal to the difference of the coefficients of p1 & p2 for any given
//     exponent.
polynomial operator -(const polynomial& p1, const polynomial& p2) {
	polynomial result(p1);
	for (unsigned int e = 0; e <= p2.degree(); e++)
		if (p2.coefficient(e) != 0.0)
			result.add_to_coef(-p2.coefficient(e), e);
	return result;
}

//     POSTCONDITION: Each term of p1 has been multiplied by each term of p2,
//     and the answer is the sum of all these term-by-term products.
//     For example, if p1 is 2x^2 + 3x + 4 and p2 is 5x^2 - 1x + 7, then the
//     return value is 10x^4 + 13x^3 + 31x^2 + 17x + 28.
polynomial operator *(const polynomial& p1, const polynomial& p2) {
    polynomial result;
    for (unsigned int e1 = p1.degree(); e1 != UINT_MAX; e1 = p1.previous_term(e1))
        for (unsigned int e2 = p2.degree(); e2 != UINT_MAX; e2 = p2.previous_term(e2))
            result.add_to_coef(p1.coefficient(e1) * p2.coefficient(e2), e1 + e2);
    return result;
}

// utility prints one term to ostream
//I don't know what this does since it was in the documentation,but was also
// on the website, so i added it in in case it was needed, but its not since there
// is an ostream& oeprator
void print_term(ostream& out, double coef, unsigned int exponent) {
    out << coef;
    if (exponent > 0)
        out << "x";
    if (exponent > 1)
        out << "^" << exponent;
}

//     POSTCONDITION: The polynomial has been printed to ostream out, which,
//     in turn, has been returned to the calling function.
//     [CS 24 Note - std::endl is printed following the polynomial]

std::ostream& operator << (std::ostream& out, const polynomial& p) {
	unsigned int degree = p.degree();
	if (degree == 0)
		out << p.coefficient(0);
	else {
		print_term(out, p.coefficient(degree), degree); // largest term
		unsigned exponent = p.previous_term(degree);
		while (exponent != UINT_MAX) {
			double coef =p.coefficient(exponent);
			out << (coef < 0.0 ? " - " : " + ");
			if (coef < 0.0)
				coef *= -1;
			print_term(out, coef, exponent);
			exponent = p.previous_term(exponent);
		}
	}
	out << std::endl;
	return out;
}


//finds the root
void polynomial::find_root(double& answer,
                            bool& success,
                            unsigned int& iterations,
                            double guess,
                            unsigned int maximum_iterations,
                            double epsilon) const{
	answer = guess;
	iterations = 0;
    success = false; //default success
	while(fabs(eval(answer)) >= epsilon && fabs(derivative().eval(answer)) >= epsilon && iterations < maximum_iterations){
		answer = answer - ((eval(answer)) / (derivative().eval(answer)));
		iterations++;
	}
	if(iterations == maximum_iterations || derivative().eval(answer) < epsilon){
		if(derivative().eval(answer) < epsilon){//flat error
			success = false;
		}
		if(iterations == maximum_iterations){//maximum iterations error
			success = false;
		}
	}
	else{
		success = true;
	}
}
/*The assignment operator first checks for a self-assignment,
then clears out the terms (using the clear function).
 Finally, have a loop (similar to the copy constructor) to copy the terms of the source.
*/
polynomial& polynomial::operator=(const polynomial& source){
    EPSILON = std::numeric_limits<double>::epsilon();
    if(this == &source){
        return *this;
    }
    clear(); //clears out the terms and then next stuff resets the pointers
    polynode *newest = source.recent_ptr;
    head_ptr->set_coef(0.0);
    recent_ptr = head_ptr;
    current_degree = 0;
    source.set_recent(0);
    recent_ptr->set_coef(source.recent_ptr->coef());
    source.recent_ptr = source.recent_ptr->fore();
    polynode *temp;
    while(source.recent_ptr != NULL){ //loop that copies term of the source
        temp = new polynode(source.recent_ptr->coef(), source.recent_ptr->exponent(), NULL, recent_ptr);
        recent_ptr->set_fore(temp);
        recent_ptr = temp;
        tail_ptr = temp;
        source.recent_ptr = source.recent_ptr->fore();
    }
    current_degree =  tail_ptr->exponent();
    source.recent_ptr = newest;
    return *this;
}

}
