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
#include "solve_chamonly.h"

int main(int argc, char* argv[]) {

	// Read the input parameters file, named "params.ini" by default.
	// If there is a command line argument, assume that it is the filename for the parameters file.
	string inifileName;
	if (argc > 1)
		inifileName = argv[1];
	else
		inifileName = "params.ini";

	vector<double> icRETS,FI;
	
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

		// Run the solver:
	 
	 	// zero the background density of the source
	 	obj_rhobg = 0.0;
	 
	 	double s1, s2, s3, phi_bg;
	 	//cout << gsl_poly_solve_cubic(-phi_inf, 0.0, -Lparam/phi_mass/phi_mass, &s1, &s2, &s3) << endl;
		int getroots = gsl_poly_solve_cubic(-phi_inf, 0.0, -Lparam/phi_mass/phi_mass, &s1, &s2, &s3);
		cout << "nroots for bg = " << getroots << " ";
		cout << s1 << " " << s2 << " " << s3 << endl;
		if(Lparam > 0)
			phi_bg = s1;
		else
			phi_bg = s3;
		// (0) set the initial conditions
		// argument = phi_bg
		//double phi_bg = phi_inf;
		icRETS = initialconditions(phi_bg);
		totmass = icRETS[0];
		cout << "Object's total mass = " << totmass << endl;
		cout << "Biggest sphere mass = " << icRETS[1] << endl;
		
		// (1) solve 
		// Returns all the force info
		FI = solve();				
		////////////////////////////////////////
		
		// Now we've found some profiles, extract information about them
		// passed back by solve()
		
		// Dump the total mass into the FI vector
		FI.push_back(totmass);	
	
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

