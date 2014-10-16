/*
	Simple code to evolve domain wall networks
		J. Pearson (Durham/Nottingham 2014)
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
	IniReader inifile;
	if (argc > 1)
		inifile.read(argv[1]);
	else
		inifile.read("params.ini");

	// Start timing!
    boost::timer::cpu_timer myTimer;
	
	// Setup parameters
	setuparams(inifile);
	
	// Print welcome message to screen
	printwelcome(cout);
		
	// Check that the output directory exists; if not, code will create it
    checkdirexists(cout,outDIR);
	
	// Do a quick sanity check
	int isok = checksanity();
	
	if(isok==0){
		// Print top-matter (run info)
		printtopmatter(cout);
		
		// Print properties of the object
		printobjectproperties(cout);
		// Print a logfile with all parameter info & simulation conditions
		printlog();

		// Run the solvers:
	 
		// (0) set the initial conditions
		// argument = phi_bg
		initialconditions(1.0/sqrt(obj_rhobg));
	
		// (1) solve 
		solve();	
	
		cout << "Completed" << endl;
	
		// Stop timing
	    myTimer.stop();
		// Send final time to be printed, along with a polite message	
		printfinalmessage(cout,myTimer.elapsed().wall / 1e6);
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

