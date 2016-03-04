//recfun.cpp 
// Brandon Lo, 2/24/15

#include <iostream>
#include "recfun.h"
using namespace std;

int reset = 0;
int compare = 0;

void triangle (ostream& outs, unsigned m, unsigned int n){
	if (outs == NULL){
		compare = n;
		n = 0;
		}
	outs << std::string(n, '*');
	outs << endl;
	outs << n << m << compare << endl;
	if (n < compare){
		triangle(outs, m, n + 1);
		}
	if (m < compare){
		triangle(outs, m , n-1);
		}
	}

void numbers(ostream& outs, const string& prefix, unsigned int levels){
	outs << prefix;
	for (int i = 0;i < 10; i++)
		outs << "." << i;
	if ( levels <= 1)
		numbers (outs, prefix, levels - 1);
	outs << endl;
	}

bool bears (int n){
	bool answer = false;
	if (n % 42 == 0)
		answer = true;
	if (n % 2 == 0)
		if (n/2 % 42 == 0)
			answer = true;
	if (n % 5 == 0)
		if ((n-42) % 2 == 0)
			if ((n-42)/2 % 42 == 0)
				answer = true;
	else
		answer = false;
	return answer;
	}

void pattern ( ostream& outs, unsigned int n, unsigned int i){
	}



