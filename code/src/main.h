

#include <stdio.h>
#include <string.h>
#include <cmath>  
#include <math.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/filesystem.hpp>
#include <boost/timer/timer.hpp>
#include <sstream>

using namespace boost::property_tree;
using namespace std;
//#include "inireader.h"

using namespace std;
const double PI=4.0*atan(1.0);

#include "options.h"
#include "inireader.h"
#include "typesinfo.h"
////////////////////////////////////////////////
// The field definition
double      fld[2][nflds][itot][jtot];
double		matterdensity[itot][jtot];
////////////////////////////////////////////////

// Some useful auxiliary functions


// Function to check if a directory exists; if not it'll get created
void checkdirexists(ostream& whereto, string dir){
    
    using namespace boost::filesystem;
    
    if (!exists(dir)) {
        whereto << endl;
        whereto << " --> Creating output directory" << endl;
        whereto << endl;
        
        create_directory(dir);
    }
    
} // END checkdirexists()


// Function to return uniform random number on unit interval
double unitrand(){
	
	return rand()/(double)RAND_MAX;
	
} // END unitrand()

// Print a welcome message
void printwelcome(ostream& whereto){
	
	whereto << endl;
	whereto << "------------------------------------------" << endl;
	whereto << "Simple code to solve for Chameleon shapes" << endl;
	whereto << "J. Pearson (Nottingham 2014)" << endl;
	whereto << "------------------------------------------" << endl;
	whereto << endl;
	
} // END printwelcome()


// Print top matter -- mainly info about current run
void printtopmatter(ostream& whereto){
	
	whereto << endl;
	whereto << "Simulation conditions/parameters:" << endl;
	whereto << "output dir: " << outDIR << endl;	
	whereto << "(imax, jmax) = (" << imax << ", " << jmax << ")" << endl;
	whereto << "(h, ht) = (" << h << ", " << ht << ")" << endl;
	whereto << "boundary layer = " << bl << " grid-points" << endl;
	
	printinfo(whereto,"Potential",pottype);	
	printinfo(whereto,"InitialConditions",inittype);
		
	whereto << "Begin solving" << endl;
	whereto << endl;
		
} // END printtopmatter()

void printobjectproperties(ostream& whereto){
	
	whereto << endl;
	whereto << "Object parameters:" << endl;
	whereto << "mattdisttype = " << mattdisttype;
	if(mattdisttype == 1)
		whereto << " :: spherical" <<endl;
	if(mattdisttype == 2){
		whereto << " :: ellipse " << endl;
		whereto << "(a, b) = (" << elparam1 << ", " << elparam2 << ")" << endl;
	}
	else
		whereto << endl;
	whereto << "size = " << objsize << endl;
	whereto << "density = " << objdensity << endl;
	whereto << "skin depth = " << objskindepth << endl;
	whereto << "bg density = " << obj_rhobg << endl;
	whereto << endl;
}

// Print final message
void printfinalmessage(ostream& whereto, double te){
	
	string tu="ms";
	if(te>1e3){
		te=te/1e3;
		tu="sec";
	}
	whereto << endl;
	whereto << "------------------------------------------" << endl;
	whereto << "Complete in " << te << tu << endl;
	whereto << "------------------------------------------" << endl;
	whereto << endl;
	
} // END printfinalmessage()

int checksanity(){
	
	if(imax > itot || jmax > jtot)
		return 1;
	if(ht>h)
		return 2;
	else
		return 0;
	
} // END checksanity()


// Print info to logfile
void printlog(string when, double v1,double v2){
	
	if(when=="start"){
		string filename = outDIR+filePREFIX+".log";
		ofstream dumplog;
		dumplog.open(filename);
		printwelcome(dumplog);
		printtopmatter(dumplog);
		printobjectproperties(dumplog);
		dumplog.close();
	}
	
	if(when=="maxFs"){
		string filename = outDIR+filePREFIX+".log";
		ofstream dumplog;
		dumplog.open(filename,ios::app);
		dumplog << endl;
		dumplog << "Max force in x-direction = " << v1 << endl;
		dumplog << "Max force in y-direction = " << v2 << endl;		
		dumplog << endl;
		dumplog.close();
	}
	
	if(when=="end"){
		string filename = outDIR+filePREFIX+".log";
		ofstream dumplog;
		dumplog.open(filename,ios::app);
		printfinalmessage(dumplog, v1);
		dumplog.close();
	}
	
} // END printlog()