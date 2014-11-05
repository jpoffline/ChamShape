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

	// Read the input parameters file, named "params.ini" by default.
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
    checkdirexists(cout,outDIR);
	
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
		double phi_bg = sqrt(1.0/obj_rhobg);
		double totmass = initialconditions(phi_bg);
		cout << "Object's total mass = " << totmass << endl;
		
		// (1) solve 
		solve();	
	
		// Stop timing
		clock_t endTime = clock();
		// Compute elapsed time in ms
		double timeinMS = (endTime - startTime) / (double) CLOCKS_PER_SEC * 1000.0;
		// Send elapsed time to be printed, along with a polite message	
		printfinalmessage(cout,timeinMS);
		// Print the elapsed time to log file
		printlog("end",timeinMS,0.0);
		
	}
	else
		printerror(cout,isok);
		
} // END main




/// EOF

