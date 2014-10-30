/*

	Simple code to find chameleon shapes
		- sweeper
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
		
	// Check that the output directory exists; if not, it gets created
    checkdirexists(cout,outDIR);
	
	// Do a quick sanity check
	int isok = checksanity();
	
	
	////////////////////////////////////////
	// Stuff specific to the sweeper
	int maxshapes=10;
	double elparam2_start = elparam2;
	double elparam2_end = elparam1;
	double delparam2 = (elparam2_end-elparam2_start)/(double)maxshapes;
	string fileprefix_proto=filePREFIX;
	int trail=1000;
	vector<double> FI;
	ofstream dumpforce;
	string filename = outDIR+"forceinfo.dat";
	dumpforce.open(filename);
	////////////////////////////////////////
	
	// If all is ok folowing the sanity check, keep going
	if(isok==0){
		
		// Start timing all shapes
		clock_t startTimeALL = clock();
		
		int counter=0;
		while(true){
		
			// Start timing this shape
			clock_t startTime = clock();
		
			// Get the file prefix title
			filePREFIX=fileprefix_proto+"_"+Int2String(trail+counter);
		
			// Routine for changing the shape:
			// Here, just changing one of the side lengths
			// - creates squased ellipses, or squashed rectangles.
			elparam2=elparam2_start+(double)counter*delparam2;
		
			// Print top-matter (run info)
			printtopmatter(cout);
		
			// Print properties of the object
			printobjectproperties(cout);
			
			// Print a logfile with all parameter info & simulation conditions
			printlog("start",0.0,0.0);

			////////////////////////////////////////
			// Run the solver:
	 
			// (0) set the initial conditions
			// argument = phi_bg (calculate)
			double totmass = initialconditions(sqrt(M*Lambda5/obj_rhobg));
			cout << "Total mass of the source = " << totmass << endl;
		
			// (1) solve 
			// Returns all the force info
			FI=solve();				
			////////////////////////////////////////
			
			// Now we've found some profiles, extract information about them
			// passed back by solve()
			
			// Dump the total mass into the FI vector
			FI.push_back(totmass);
			
			// (2) Dump force ratio info to file
			for(int n=0; n < FI.size(); n++)
				dumpforce << FI[n] << " ";
			dumpforce << endl;		
			
			// Stop timing for this shape
			clock_t endTime = clock();
			
			// Compute elapsed time in ms
			double timeinMS = (endTime - startTime) / (double) CLOCKS_PER_SEC * 1000.0;
			
			// Send elapsed time to be printed, along with a polite message	
			printfinalmessage(cout,timeinMS);
			
			// Print the elapsed time to log file
			printlog("end",timeinMS,0.0);
			
			if(counter-1 > maxshapes)
				break;
			else
				counter++;
			
		}
		
		// Stop timing for the entire run
		clock_t endTimeALL = clock();
		// Compute elapsed time in ms
		double timeinMSALL = (endTimeALL - startTimeALL) / (double) CLOCKS_PER_SEC * 1000.0;
		cout << endl;
		cout << "Total elapsed time = " << timeinMSALL << "ms" << endl;
		cout << endl;
	}
	else
		printerror(cout,isok);
		
		
	// Close the dump-file	
	dumpforce.close();	
		
} // END main




/// EOF

