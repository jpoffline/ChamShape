/*

	main.cpp

*/


#include "main.h"
#include "myparamreader.h"
#include "structs.h"
#include "forcecalc.h"
#include "setup_particles.h"
#include "dumpforceinfo.h"
#include "dump.h"
#include "sanity.h"

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
	
	// Read in the parameter file
	ifstream paramsfile;
	paramsfile.open(inifileName);
	box.h = getiniDouble(paramsfile,"h", 0.25);
	box.imax = getiniInt(paramsfile,"imax", 1000);
	box.jmax = getiniInt(paramsfile,"jmax", 1000);
	box.di = getiniInt(paramsfile,"di", 100);
	object.type = getiniString(paramsfile,"objecttype","ellipse");
	object.mass = getiniDouble(paramsfile,"mass", 1.0);
	object.measureshift = getiniDouble(paramsfile,"measureshift", 4.0);
	strs.outDIR = getiniString(paramsfile,"outDIR","data/");
	strs.mainID = getiniString(paramsfile,"mainID","run");
	int nshapes = getiniInt(paramsfile,"nshapes", 10);
	bool dumpdownaxes = getiniBool(paramsfile,"dumpdownaxes",false);
	bool dumpatpoints = getiniBool(paramsfile,"dumpatpoints",false);
	double maxratio = getiniDouble(paramsfile,"maxratio", 8.0);
	paramsfile.close();	

	// Put an underscore after the mainID string
	strs.mainID+="_";
	
	
	double elparam2_start = 2.0;
	double elparam1_start = elparam2_start;
	double dep1 = elparam1_start * ( maxratio - 1.0 ) / (double)nshapes;
	strs.fileSUFFIX = ".dat";
	strs.icsPROTO = "partpos";
	strs.forcexPROTO = "Fx";
	strs.forceyPROTO = "Fy";
	strs.ratiosPROTO = "ratios";
	strs.trail = 1000;
	
	// Setup stream to dump force ratios info
	ofstream ratioinfo;
	string filename = strs.outDIR + strs.mainID + strs.ratiosPROTO + strs.fileSUFFIX;
	ratioinfo.open(filename);
	
	// Vector which will contain all the info about the shape under consideration
	vector<double> shapeinfo;
	// Vector which will contain |F| at various locations for the given shape
	vector<double> modfpoints;
	
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
		
		// Compute the area of the source
		object.area = object.ep1 * object.ep2 * PI;

		// Pick the density of each "particle"
		// so that the mass is fixed
		object.dns = object.mass / object.area;
		
		// Set the ID of the object
		object.ID = Int2String(strs.trail + shape) + "_";
		
		// Put the ID into the strs struct too
		strs.ID = object.ID;
		
		// Setup the particles
		vector<PARTICLE> particles = SetupParticles(object, box, strs);		

		// If required, dump the forces down the axes
		if(dumpdownaxes)
			DumpForceDownAxes(particles, box, strs);
		
		// If required, compute the forces at specific locations
		if(dumpatpoints){
			
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
				
			}
			
			// Get the vector of |F|'s at the required locations
			modfpoints = GetForceAtPoints(particles, points);
			
			shapeinfo.push_back(shape);
			shapeinfo.push_back(particles.size());
			shapeinfo.push_back(object.dns);
			shapeinfo.push_back(object.ep1);
			shapeinfo.push_back(object.ep2);
			shapeinfo.push_back(object.ep2/object.ep1);
			shapeinfo.push_back(modfpoints[0]);
			shapeinfo.push_back(modfpoints[1]);			
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

		shape++;
		if(shape > nshapes)
			break;

	} // END shape-loop

	// Close ratioinfo file	
	ratioinfo.close();
	
} // END main()




