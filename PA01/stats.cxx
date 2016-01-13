// stats.cxx - implements statistician class as defined in stats.h
// Brandon Lo, 1/7/16

#include <cassert>  // provides assert
#include "stats.h"  // defines what must be implemented



namespace main_savitch_2C
{
//global variables
int count = 0;
int variable = 0;
int total = 0;
double r;
int tiniest = 0;
int largest = 0;
double temp = 0;

// adds to the count and moves one over
void next(double r){
  do{
  variable = r;
  count++;
  r = temp;
}while (r >= 0);
}
//if next is empty, breaks loop
void reset ( ){
  count = 0;
  variable = 0;
  total = 0;
}
//not sure if length needed since stats.h has a return count++;
int length ( ){
  count++;
  return count;
}
//accumaltor of total with r
double sum ( ){
  total = total + r;
  return total;
}
//takes total and divides by count to give mean
double mean ( ){
  double average = total/count;
  return average;
}
//returns minimum after checking
double minimum( ){
  if (variable >= temp){
    return 22;
  }
}
// returns maximum after checking it
double maximum( ){
  if (variable <= temp){
    return 10;
  }
}

}
