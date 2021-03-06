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
#include "baretts_apple.h"
#include "ics.h"
//#include "pot.h"
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
	 
	 	double s1_b,s2_b,s3_b,s1_o,s2_o,s3_o,phi_bg,phi_obj;
		
		/*
		
		Need to solve a cubic to obtain phi's value inside and outside object.
		In the homogeneous regime, the scalar satisfies
		
			phi * phi * phi + 6 * mphi2 * phi / lambda - 6 * beta * rho / Mpl / lambda = 0.
		
		For a cubic of the form
		
			x^3 + ax^2 + bx + c = 0,
		
		the GSL function
		
			gsl_poly_solve_cubic(a,b,c, root_1, root_2, root_3)
		
		returns the roots.
		
		*/
		
		int getroots_bg = gsl_poly_solve_cubic(0.0, 6.0 * mphi2 / lambda, - 6.0 * beta * obj_rhobg / lambda / Mpl, &s1_b, &s2_b, &s3_b);
		int getroots_obj = gsl_poly_solve_cubic(0.0, 6.0 * mphi2 / lambda, - 6.0 * beta * obj_density / lambda / Mpl, &s1_o, &s2_o, &s3_o);		
		cout << "Roots:" << endl;
		cout << "inside object: " << s1_o << " " << s2_o << " " << s3_o << endl;
		cout << "outside object: " << s1_b << " " << s2_b << " " << s3_b << endl;
		phi_bg = s1_b;
		phi_obj = s1_o;
		// (0) set the initial conditions
		icRETS = initialconditions(phi_bg, phi_obj);
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

