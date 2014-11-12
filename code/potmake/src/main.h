/*

	main.h

*/


#include <stdio.h>
#include <string.h>
#include <cmath>  
#include <math.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
const double PI = 4.0*atan(1.0);

////////////////////////////////////////////////////////////////////////
//
//	Useful auxiliary functions
//
////////////////////////////////////////////////////////////////////////

string Int2String(int Number) {
	
    return static_cast<ostringstream*>( &(ostringstream() << Number) )->str();
	
} // END Int2String()

double String2Double(string s) {
     
	 double d;
     stringstream ss(s); //turn the string into a stream
     ss >> d; //convert
     return d;
	 
} // END String2Double()

int String2Int(string s) {
     
	 int d;
     stringstream ss(s); //turn the string into a stream
     ss >> d; //convert
     return d;
	 
} // END String2Int()