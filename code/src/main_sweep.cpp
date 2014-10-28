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
	
	if(isok==0){
		
		// Start timing!
		clock_t startTimeALL = clock();
		
		int counter=0;
		while(true){
		
			// Start timing!
			clock_t startTime = clock();
		
			// Get the file prefix title
			filePREFIX=fileprefix_proto+"_"+Int2String(trail+counter);
		
			elparam2=elparam2_start+(double)counter*delparam2;
		
			// Print top-matter (run info)
			printtopmatter(cout);
		
			// Print properties of the object
			printobjectproperties(cout);
			// Print a logfile with all parameter info & simulation conditions
			printlog("start",0.0,0.0);

			// Run the solvers:
	 
			// (0) set the initial conditions
			// argument = phi_bg
			double totmass = initialconditions(sqrt(M*Lambda5/obj_rhobg));
			cout << "total mass = " << totmass << endl;
		
			// (1) solve 
			FI=solve();	
			
			// (2) Dump force ratio info
			for(int n=0; n < FI.size(); n++)
				dumpforce << FI[n] << " ";
			dumpforce << endl;		
			
			// Stop timing
			clock_t endTime = clock();
			// Compute elapsed time in ms
			double timeinMS = (endTime - startTime) / (double) CLOCKS_PER_SEC * 1000.0;
			// Send elapsed time to be printed, along with a polite message	
			printfinalmessage(cout,timeinMS);
			// Print the elapsed time to log file
			printlog("end",timeinMS,0.0);
			
			if(counter>maxshapes)
				break;
			else
				counter++;
			
		}
		
		// Stop timing
		clock_t endTimeALL = clock();
		// Compute elapsed time in ms
		double timeinMSALL = (endTimeALL - startTimeALL) / (double) CLOCKS_PER_SEC * 1000.0;
		cout << "total elapsed time = " << timeinMSALL << "ms" << endl;
	}
	else
		printerror(cout,isok);
		
	dumpforce.close();	
		
} // END main




/// EOF

