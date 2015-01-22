// main.h: where the guts of the code is brought together
// NOTE: quite a lot of variables and arrays are globally defined. This is to increase speed

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
#include <stdlib.h>
#include <sys/stat.h>   // For stat().
#include <vector>
using namespace std;

// include GSL library for computing Legendre polynomials
#include "gsl/gsl_sf_legendre.h"

// include GSL library for solving cubic equations
#include "gsl/gsl_poly.h"

const double PI = 4.0 * atan(1.0);

// Includes
// (1) useful auxiliary functions (conversions etc)
#include "auxfunc.h"
// (2) globally defined variables
#include "globals.h"
// (3) information about types
#include "printinfo.h"
// (4) software to read in parameter file (needs to be included after globals!)
#include "myparamreader.h"


////////////////////////////////////////////////
// The field definition
double      fld[2][nflds][itot][jtot];
double		matterdensity[itot][jtot];
////////////////////////////////////////////////


// Routine to check sanity of user defined variables

int checksanity(){
	
	if(imax > itot || jmax > jtot)
		return 1;
	if(ht>h)
		return 2;
	else
		return 0;
	
} // END checksanity()
