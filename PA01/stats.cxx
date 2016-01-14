// stats.cxx - implements statistician class as defined in stats.h
// Brandon Lo, 1/7/16

#include <cassert>  // provides assert
#include "stats.h"  // defines what must be implemented

namespace main_savitch_2C
{
  statistician::statistician(){
// CONSTRUCTOR for the statistician class:
//   statistician( );
//     Postcondition: The object has been initialized, and is ready to accept
//     a sequence of numbers. Various statistics will be calculated about the
//     sequence.
    count = 0;
    total = 0;
  }

// adds to the count and moves one over
void statistician::next(double r){
//   void next(double r)
//     The number r has been given to the statistician as the next number in
//     its sequence of numbers.
  if (count < 1){ //if nothing was entered yet, set everything to r
    largest = r;
    tiniest = r;
  }

  if (r < tiniest){ //checks r if is tiny or not
    tiniest = r;
  }
  if (r > largest){ //checks largest
    largest = r;
  }
  total += r; //gives the sum
  count++; //advances count
}

//if next is empty, breaks loop
void statistician::reset ( ){
//   void reset( );
//     Postcondition: The statistician has been cleared, as if no numbers had
//     yet been given to it.
  if (count < 1){ //if nothing inputted, stops.
    return;
  }
  count = 0;
  total = 0;
  tiniest = 0;
  largest = 0;
}

double statistician::mean ( ) const{
//   double mean( ) const
//     Precondition: length( ) > 0
//     Postcondition: The return value is the arithmetic mean (i.e., the
//     average of all the numbers in the statistician's sequence).
  assert (count > 0); //as long as count > 0, continue
  double average = total/count;
  return average;
}
//returns minimum after checking
double statistician::minimum( ) const{
//   double minimum( ) const
//     Precondition: length( ) > 0
//     Postcondition: The return value is the tiniest number in the
//     statistician's sequence.
    assert (count > 0);
    return tiniest;
}

// returns maximum after checking it
double statistician::maximum( )const {
//   double maximum( ) const
//     Precondition: length( ) > 0
//     Postcondition: The return value is the largest number in the
//     statistician's sequence.
   assert (count > 0);
   return largest;
}

statistician operator *(double scale, const statistician& s1){
//   statistician operator *(double scale, const statistician& s)
//     Postcondition: The statistician that is returned contains the same
//     numbers that s does, but each number has been multiplied by the
//     scale number.
  if (s1.length() == 0){
    return statistician();
  }

  statistician s = statistician(); //creates a statistician s and checks it against s1
  s.count = s1.count;              // contains same numbers that s does
  s.total = s1.total * scale;      // each number multiplied by scale number

  if (scale > 0){ 
    s.largest = s1.largest * scale;
    s.tiniest = s1.tiniest * scale;
  }

  else{ //if scale is negative, needs to be switched
  s.largest = s1.tiniest * scale;
  s.tiniest = s1.largest * scale;
  }
  return s;
}

statistician operator +(const statistician& s1, const statistician& s2){
//   statistician operator +(const statistician& s1, const statistician& s2)
//     Postcondition: The statistician that is returned contains all the
//     numbers of the sequences of s1 and s2.
  if (s1.length() ==0){
  return statistician(s2);
  }
  else if (s2.length() ==0){
  return statistician(s1);
  }
  statistician s = statistician();
  s.count = s1.count + s2.count;
  s.total = s1.total + s2.total;

  if(s1.tiniest < s2.tiniest || s1.tiniest == s2.tiniest){
    s.tiniest = s1.tiniest;
    }
  else{
    s.tiniest = s2.tiniest;
    }

  if(s1.largest < s2.largest || s1.largest == s2.largest){
    s.largest = s2.largest;
    }
  else{
    s.largest = s1.largest;
    }
    return s;
  }


bool operator == (const statistician& s1, const statistician& s2){
//   bool operator ==(const statistician& s1, const statistician& s2)
//     Postcondition: The return value is true if s1 and s2 have the zero
//     length. Also, if the length is greater than zero, then s1 and s2 must
//     have the same length, the same  mean, the same minimum,
//     the same maximum, and the same sum.

if( ( s1.length() == 0) && (s2.length() == 0) ){
return true;
}

//Checks all the post conditions
if( !(s1.length() == s2.length() ) ) return false;
else if( !(s1.sum() == s2.sum() ) ) return false;
else if( !(s1.minimum() == s2.minimum() ) ) return false;
else if( !(s1.maximum() == s2.maximum() ) ) return false;
else if( !(s1.mean() == s2.mean() ) ) return false;
return true;
}


}
