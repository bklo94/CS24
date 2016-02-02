//Danny Truong, Brandon Lo, Jan 12, 2015
//poly1.cxx for PA03

#include<iostream>
#include<climits>
#include<math.h>
#include "poly1.h"
#include <cassert>

namespace main_savitch_4
{

  polynomial::polynomial(double c, unsigned int exponent)
    {


      if(exponent <= DEFAULT_CAPACITY)
    {
      coef = new double[DEFAULT_CAPACITY];
      size = DEFAULT_CAPACITY;
      for(int index = 0 ; index < DEFAULT_CAPACITY ; index++)
    *(coef + index) = 0;

      *(coef + exponent) = c;

      if(coef[exponent] != 0)
    current_degree = exponent;
      else
    current_degree = 0;
    }

      else
    {
    coef = new double[exponent * 2];
    size = exponent * 2;
    for(int index = 0 ; index < exponent * 2 ; index++)
      *(coef + index) = 0;

    *(coef + exponent) = c;

    if(coef[exponent] != 0)
      current_degree = exponent;
    else
      current_degree = 0;

    }
    }

  polynomial::polynomial( const polynomial& source)
    {
    coef = new double[size + source.current_degree];

       for(int i = 0 ; i <= source.current_degree ; i++)
     {
       *(coef + i) = source.coef[i];
     }

       size = size + source.degree();
       current_degree = source.current_degree;

       //delete [] coef;

       //coef = new_coef;


    }

  polynomial::~polynomial()
  {
    delete [] coef;
  }

 void polynomial::add_to_coef(double amount, unsigned int exponent)
 {

      if(exponent >= size)
     {
       double *new_coef = new double[size + exponent];

       for(int i = 0 ; i < size ; i++)
     {
       *(new_coef + i) = *(coef + i);
     }

       size = exponent + size;

       delete [] coef;

       coef = new_coef;
     }



   coef[exponent] += amount;

   if(coef[exponent] != 0)
     {
       if(exponent > current_degree)
     current_degree = exponent;
     }
   else
     {
       int index = degree();
       bool FoundEX = false;
       while(index >= 0 && !FoundEX)
     {
       if(coef[index] != 0)
         FoundEX = true;
       else
       index--;
     }
       if(FoundEX)
     current_degree = index;
       else
     current_degree = 0;
     }
 }

 void polynomial::assign_coef(double coefficient, unsigned int exponent)
 {
   if(exponent >= size)
     {
       double *new_coef = new double[exponent + size];

       for(int i = 0 ; i < size ; i++)
     {
       *(new_coef + i) = *(coef + i);
     }

       size = exponent + size;

       delete [] coef;

       coef = new_coef;
     }


   coef[exponent] = coefficient;

   if(coef[exponent] != 0)
     {
       if(exponent > current_degree)
	 current_degree = exponent;
     }
     else
     {
       int index = degree() + 1;
       bool FoundEX = false;
       while(index >= 0 && !FoundEX)
     {
       if(coef[index] != 0)
         FoundEX = true;
       else
       index--;
     }
       if(FoundEX)
     current_degree = index;
       else
     current_degree = 0;
     }

 }

 void polynomial::clear()
 {
   for(int l = 0 ; l < size ; l++)
     coef[l] = 0;

   current_degree = 0;
 }

  /* void reserve(unsigned int number)
  {
   double *new_coef = new double[size + NU];

       for(int i = 0 ; i < size ; i++)
     {
       *(new_coef + i) = *(coef + i);
     }

       size = exponent;

       delete [] coef;

       coef = new_coef;
 }

  */

 double polynomial::coefficient(unsigned int exponent) const
 {
   if(exponent > size || exponent < 0)
     return 0;

   else
     {
       return coef[exponent];
     }

 }


 polynomial polynomial::derivative() const
 {
   polynomial result;
   int coefficient;
   coefficient = current_degree;

   while(coefficient > 0)
     {

       result.assign_coef(coefficient * coef[coefficient], coefficient - 1);
       coefficient--;
     }

   if(degree() > 0)
     result.current_degree = degree() - 1;
   else
     result.current_degree = 0;

   return result;

 }

  double polynomial::eval(double x) const
 {
   int coel = current_degree;
   double total = 0;

   while(coel >= 0)
     {
     total += coef[coel] * pow(x, coel);
     coel--;
     }

   return total;

 }

  unsigned int polynomial::next_term(unsigned int e) const
 {
   int index = e + 1;
   bool foundEX = false;

   while(index < size && !foundEX)
     {
       if(coef[index] != 0)
     foundEX = true;
       else
     index++;
     }
   if(!foundEX)
     return 0;
   else
     return index;
 }

  unsigned int polynomial::previous_term(unsigned int e) const
  {
    int index;

    if(e == 0)
      return UINT_MAX;

    index = e - 1;


    if(index > current_degree)
      return current_degree;

    for(index = e - 1 ; index >= 0 ; index--)
      {if(coef[index] != 0)
      return index;
      }

    return UINT_MAX;

}

  polynomial operator +(const polynomial &p1, const polynomial &p2)
  {
    polynomial result;
    int HighestDegree;
    int index = 0;
    double coefTotal;

    HighestDegree = p1.degree();

    if(HighestDegree < p2.degree())
      HighestDegree = p2.degree();

    while(index <= HighestDegree)
      {coefTotal = p1.coefficient(index) + p2.coefficient(index);
    if(coefTotal != 0)
      {result.assign_coef(coefTotal, index);}
       index++;
      }

    return result;
  }

  polynomial operator -(const polynomial &p1, const polynomial &p2)
  {
    polynomial result;
    int HighestDegree;
    int index = 0;
    double coefTotal;

    HighestDegree = p1.degree();

    if(HighestDegree < p2.degree())
      HighestDegree = p2.degree();

    while(index <= HighestDegree)
      {coefTotal = p1.coefficient(index) - p2.coefficient(index);
    if(coefTotal != 0)
      {result.assign_coef(coefTotal, index);}
       index++;
      }

    return result;
  }

  polynomial operator *(const polynomial &p1, const polynomial &p2)
  {

    polynomial result;
    int HighestDegree;


    HighestDegree = p1.degree() + p2.degree();
    double Cof[HighestDegree];


    for(int index = 0 ; index <= HighestDegree ; index++)
      Cof[index] = 0;

    int CurrentIndex;

    for(int index1 = 0 ; index1 <= HighestDegree ; index1++)
      {
    for(int index2 = 0 ; index2 <= HighestDegree ; index2++)
      { CurrentIndex = index1 + index2;
        Cof[CurrentIndex] += p1.coefficient(index1) * p2.coefficient(index2);
      }
      }

    for(int index = 0 ; index <= HighestDegree ; index++)
      {
    result.assign_coef(Cof[index], index);
      }

    return result;
  }

std::ostream& operator << (std::ostream& out, const polynomial& p)
{

  int index;
  bool empty = true;
  bool first = true;

   for(index = p.degree() ; index >= 0 ; index--)
    {
      if(p.coefficient(index) != 0)
      	{empty = false;
      if(first)
        { out << p.coefficient(index);
          first = false;

           if(p.coefficient(index) > 0)
        {
          if(index > 1)
            out << "x^" << index;
          if(index == 1)
            out << "x";
        }
          if(p.coefficient(index) < 0)
        {
          if(index > 1)
            out << "x^" << index;
          if(index == 1)
            out << "x";
        }


        }
      else
        {

          if(p.coefficient(index) > 0)
        {
          out << " + ";

          if(index > 1)
            out << p.coefficient(index) << "x^" << index;
          if(index == 1)
            out << p.coefficient(index) << "x";
          if(index < 1)
            out << p.coefficient(index);
        }
          if(p.coefficient(index) < 0)
        {
          out << " - ";

          if(index > 1)
            out << p.coefficient(index) * (-1) << "x^" << index;
          if(index == 1)
            out << p.coefficient(index) * (-1) << "x";
          if(index < 1)
            out << p.coefficient(index) * (-1);
        }


        }

    }
    }

  if(empty)
    out << 0;

  out << "\n";


}


  polynomial& polynomial::operator =(const polynomial& source)
  {
    //polynomial result;

    if(this == &source)
      {
        return *this;
      }
    else
      {
	for(int index = 0; index <= source.size ; index++)
	  {
	    assign_coef(source.coefficient(index), index);
	  }

      }
      return *this;
  }


  void polynomial::find_root(
           double& answer,
           bool& success,
           unsigned int& iterations,
           double guess,
           unsigned int maximum_iterations,
           double epsilon
           )
    const

  {
    assert(epsilon > 0);

    polynomial derive;
    derive = derivative();

    answer = guess;

    double f, fprime;

    f = eval(answer);
    fprime = derive.eval(answer);

    double fabs;
    double fprimeabs;

    if(f < 0)
      fabs = f * (-1);
    else
      fabs = f;

    if(fprime < 0)
      fprimeabs = fprime * (-1);
    else
      fprimeabs = fprime;

    success = false;

    bool flatFailure = false;


    if(coef[0] == 0 && guess == 0)
      {
    answer = 0;
      }

    else
      {
    polynomial derive;
    derive = derivative();

    answer = guess;

    double f, fprime;

    f = eval(answer);
    fprime = derive.eval(answer);

    double fabs;
    double fprimeabs;

    if(f < 0)
      fabs = f * (-1);
    else
      fabs = f;

    if(fprime < 0)
      fprimeabs = fprime * (-1);
    else
      fprimeabs = fprime;


    if(fprime < epsilon)
      flatFailure = true;

    if(fabs < epsilon)
      success = true;

    iterations = 0;

    while(iterations < maximum_iterations && !success && !flatFailure)
      {

	f = eval(answer);
	fprime = derive.eval(answer);


	answer = answer - ( f / fprime );




	if(f < 0)
	  fabs = f * (-1);
	else
	  fabs = f;

	if(fprime < 0)
	  fprimeabs = fprime * (-1);
	else
	  fprimeabs = fprime;

	if(fprimeabs < epsilon)
	  {
	    flatFailure = true;
	  }

	if(fabs <= epsilon)
	  {
	    success = true;
	  }

	iterations++;

      }

      }

  }


}
