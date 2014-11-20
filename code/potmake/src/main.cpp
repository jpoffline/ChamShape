/*

	main.cpp

*/


#include "main.h"
#include "myparamreader.h"
#include "structs.h"
#include "setupparams.h"
#include "sanity.h"
#include "forcecalc.h"
#include "potcalc.h"
#include "setup_particles.h"
#include "dumpforceinfo.h"
#include "dump.h"

int main(int argc, char* argv[]) {

	// Read the input parameters file, named "params.ini" by default.
	// If there is a command line argument, assume that it is the filename for the parameters file.
	string inifileName;
	
	if (argc > 1)
		inifileName = argv[1];
	else
		inifileName = "params.ini";	
	
	// Initialise various useful structs
	GRID box;
	OBJECT object;
	BOOKKEEPING strs;
	RUNPARAMS runparams;
	
	// Setup various parameters, based on the inifile
	setuparams(inifileName,box,strs,object,runparams);	

	// Put an underscore after the mainID string
	strs.mainID+="_";
	
	double elparam2_start = 2.0;
	double elparam1_start = elparam2_start;
	double dep1 = elparam1_start * ( runparams.maxratio - 1.0 ) / (double)runparams.nshapes;
	
	
	// Setup stream to dump force ratios info
	ofstream ratioinfo;
	string filename = strs.outDIR + strs.mainID + strs.ratiosPROTO + strs.fileSUFFIX;
	ratioinfo.open(filename);
	
	// Vector which will contain all the info about the shape under consideration
	vector<double> shapeinfo;
	
	// Vector which will contain |F| and grav.pots at various locations for the given shape
	vector<double> modfpoints, gravpots;
	
	// Compute the maximum distance the grid can support
	box.xmax = 0.5 * box.imax * box.h;
	
	// Shape number counter
	int shape = 0;	
	
	while(true){
	
		// Setup properties of the source object
		
		object.ep1 = elparam1_start + shape * dep1;
		object.ep2 = elparam2_start;
		
		if( !sanity(object, box) )
			break;
		
		
		// Set the ID of the object
		object.ID = Int2String(strs.trail + shape) + "_";
		
		// Put the ID into the strs struct too
		strs.ID = object.ID;
		
		// :: Setup the particles ::
		// This also sets the mass of the particles, so that
		// the total mass of the object is the same as the user-defined
		// value in params.ini
		vector<PARTICLE> particles = SetupParticles(object, box, strs);		


		// If require, dump force in the plane
		if(runparams.dumpplane)
			DumpForcePlane(particles, box, strs);

		// If required, dump the forces down the axes
		if(runparams.dumpdownaxes)
			DumpForceDownAxes(particles, box, strs);
		
		// If required, compute the forces at specific locations
		if(runparams.dumpatpoints){
			
			/*
			
				Routine to dump the forces at given locations,
				for each shape.
			
			*/
			
			// These are the coordinates we want the forces at	
			vector<COORDS> points;
			COORDS coord;
			
			// This "default" is the closest we can get to the surface
			// of the shape; not that we actually compute force at
			// measureshift * h AWAY from the surface
			if(object.type == "ellipse"){
				
				coord.loc.push_back( object.ep1 + object.measureshift * box.h );
				coord.loc.push_back( 0.0 );
				points.push_back( coord );
				coord.loc.clear();
	
				coord.loc.push_back( 0.0 );
				coord.loc.push_back( object.ep2 + object.measureshift * box.h );
				points.push_back( coord );
				coord.loc.clear();
				
				coord.loc.push_back( 50.0 );
				coord.loc.push_back( 0.0 );
				points.push_back( coord );
				coord.loc.clear();
				
				coord.loc.push_back( 0.0 );
				coord.loc.push_back( 50.0 );
				points.push_back( coord );
				coord.loc.clear();
				
			}
			
			if(object.type=="legply"){
				
				coord.loc.push_back( -10.0 );
				coord.loc.push_back( 0.0 );
				points.push_back( coord );
				coord.loc.clear();
				
				coord.loc.push_back( 10.0 );
				coord.loc.push_back( 0.0 );
				points.push_back( coord );
				coord.loc.clear();
				
				coord.loc.push_back( 0.0 );
				coord.loc.push_back( 10.0 );
				points.push_back( coord );
				coord.loc.clear();
				
			}
			
			// Get the vector of |F|'s at the required locations
			modfpoints = GetForceAtPoints(particles, points);
			
			// Get vector of grav.pots at the required locations
			gravpots = GetPotAtPoints(particles, points);
			
			shapeinfo.push_back(shape);
			shapeinfo.push_back(particles.size());
			shapeinfo.push_back(object.measureshift * box.h);
			shapeinfo.push_back(object.ep1);
			shapeinfo.push_back(object.ep2);
			shapeinfo.push_back(object.ep2/object.ep1);
			
			for(int f = 0; f < modfpoints.size(); f++ )
				shapeinfo.push_back(modfpoints[f]);	
			
			for(int g = 0; g < gravpots.size(); g++ )
				shapeinfo.push_back(gravpots[g]);	
			
			shapeinfo.push_back(modfpoints[1]/modfpoints[0]);
				
			// Send all this info to the screen			
			dumpshapeinfo(shapeinfo,cout);	
			
			// Send all this info to the "ratioinfo" file		
			dumpshapeinfo(shapeinfo,ratioinfo);			
			
			// Clean up these vectors			
			modfpoints.clear();
			points.clear();		
			shapeinfo.clear();	
			
		}
		
		if(runparams.RunAxesRatiosSquash){
		
			/*
			
				Routine: 
					For each shape, compute |F| down each axis.
					At each fixed distance from the surface, compute F_y/F_y;
					Prints this ratio to file; different files for each shape.
				This is a useful experiment to perform.
			
			*/
			
			vector<COORDS> points;
			COORDS coord;
			
			ofstream dumpJ;
			dumpJ.open(strs.outDIR + strs.mainID + strs.ID + "_J_" + strs.fileSUFFIX);
			
			double moffset = 10.0;
			int Nlocs = 50;
			for(int locI = 0; locI < Nlocs; locI++){
				
				// Where are we doing the measurement?
				object.measureshift = moffset + locI * 40.0;
				if(object.type == "ellipse"){
				
					coord.loc.push_back( object.ep1 + object.measureshift * box.h );
					coord.loc.push_back( 0.0 );
					points.push_back( coord );
					coord.loc.clear();
	
					coord.loc.push_back( 0.0 );
					coord.loc.push_back( object.ep2 + object.measureshift * box.h );
					points.push_back( coord );
					coord.loc.clear();
				
				}
				
				// Get the vector of |F|'s at the required locations
				modfpoints = GetForceAtPoints(particles, points);
				
				// Dump this info into "shapeinfo"
				shapeinfo.push_back( shape );
				shapeinfo.push_back( object.measureshift * box.h );
				shapeinfo.push_back( object.ep2 / object.ep1 );
				shapeinfo.push_back( modfpoints[1] / modfpoints[0] );
				
				// Send all this info to the screen			
				dumpshapeinfo(shapeinfo,cout);	
				// Send all this info to the "ratioinfo" file		
				dumpshapeinfo(shapeinfo,dumpJ);			
			
				// Clean up these vectors			
				modfpoints.clear();
				points.clear();		
				shapeinfo.clear();	
				
			}
			
			dumpJ.close();
			
		} // END testJ

		shape++;
		if( shape + 1 > runparams.nshapes ){
			cout << "done all shapes" << endl;
			break;
		}

	} // END shape-loop

	// Close ratioinfo file	
	ratioinfo.close();
	
} // END main()




