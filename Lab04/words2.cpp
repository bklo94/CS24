// words2.cpp -dynamic array version
// (fixed size array version)
// Brandon Lo, 1/26/15

#include <iostream>
#include <cassert>
#include <string>
#include <algorithm>
#include <cstdlib>
#include "words2.h"
using namespace std;

using std::string;

namespace lab04_2
{

    Words::Words(unsigned int initial_capacity){ 	
	data = new string[initial_capacity];
	capacity = initial_capacity;
        used = 0;
    }

    Words::Words(const Words &source){
	data = new string[source.capacity];
	capacity = source.capacity;
	used = source.used;
	copy(source.data, source.data + used, data);
   }

    
  void Words::append(string word) {
     if (used == capacity){
        string *data2 = new string[used*2];
        copy(data, data + used, data2);
	delete [] data;
        data = data2;
	capacity = used *2;
      }
        data[used] = word;
        used++;;	
  }
    
    string& Words::operator[] (unsigned int index) {
        return data[index];
    }
    
    unsigned int Words::size() const {
        return used;
    }
    
    unsigned int Words::get_capacity() const {
        return capacity;
    }
    
    string Words::operator[] (unsigned int index) const {
        return data[index];
    }
	
    void Words::operator=(const Words & source){
	string *new_data;
	if (this == &source){
		return;
    }
	if (capacity != source.capacity){
	new_data = new string[source.capacity];
	delete [ ] data;
	data = new_data;
	capacity = source.capacity;
    }
	used = source.used;
	copy(source.data, source.data + used, data);
    }	

    Words::~Words() {
	delete [] data;
    }   
}
