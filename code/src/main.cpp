/*
	Simple code to find chameleon shapes
		J. Pearson (Nottingham 2014)
		j.pearson@nottingham.ac.uk
*/

// NOTES
// Not the cleverest code (i.e., many arrays & variables are globally defined
// ... and most definitely not object oriented) but the code is pretty quick!
// 

#include "main.h"
#include "setup.h"
#include "ics.h"
#include "pot.h"
#include "solve.h"

int main(int argc, char* argv[]) {

	// Read the input parameters file, named "newparam.txt" by default.
	// If there is a command line argument, assume that it is the filename for the parameters file.
	string inifileName;
	if (argc > 1)
		inifileName = argv[1];
	else
		inifileName = "params.ini";

	
	
	// Setup parameters
	setuparams(inifileName);
	
	// Print welcome message to screen
	printwelcome(cout);
		
	// Check that the output directory exists; if not, code will create it
    mycheckdir(cout,outDIR);
	
	// Do a quick sanity check
	int isok = checksanity();
	
	if(isok==0){
		
		// Start timing!
		clock_t startTime = clock();
		
		// Print top-matter (run info)
		printtopmatter(cout);
		
		// Print properties of the object
		printobjectproperties(cout);
		// Print a logfile with all parameter info & simulation conditions
		printlog("start",0.0,0.0);

		// Run the solvers:
	 
		// (0) set the initial conditions
		// argument = phi_bg
		initialconditions(1.0/sqrt(obj_rhobg));
	
		// (1) solve 
		solve();	
	
		cout << "Completed" << endl;
	
		// Stop timing
		clock_t endTime = clock();
		// Compute elapsed time in ms
		double timeInms = (endTime - startTime) / (double) CLOCKS_PER_SEC * 1000.0;
		// Send elapsed time to be printed, along with a polite message	
		printfinalmessage(cout,timeInms);
		// Print the elapsed time to log file
		printlog("end",timeInms,0.0);
		
	}
	else{
		if(isok==1)
			cout << "imax and/or jmax not chosen sensibly" << endl;
		if(isok==2)
			cout << "time-step size bigger than space step-size" << endl;
		cout << "terminating" << endl;
		cout << endl;
	}
} // END main




/// EOF

