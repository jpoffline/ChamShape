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


string Int2String(int Number) {
	
    return static_cast<ostringstream*>( &(ostringstream() << Number) )->str();
	
} // END Int2String()