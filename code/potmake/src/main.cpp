/*

	main.cpp

*/


#include "main.h"
#include "structs.h"
#include "forcecalc.h"
#include "setup.h"
#include "dump.h"

int main(){
	
	bool dumpdownaxes = false;
	bool dumpatpoints = true;
	
	// Setup properties of the grid
	GRID box;
	box.h = 0.05;
	box.imax = 1000;
	box.jmax = 1000;

	int nshapes = 50;
	
	ofstream dump;
	dump.open("size.dat");
	
	OBJECT object;
	object.type = "ellipse";
	object.mass = 1.0;
	
	double elparam2_start = 2.0;
	double elparam1_start = elparam2_start;
	double maxratio = 8.0;
	double dep1 = elparam1_start * ( maxratio - 1.0 ) / (double)nshapes;
	
	BOOKKEEPING strs;
	strs.outDIR = "data/";
	strs.mainID = "run_";
	strs.fileSUFFIX = ".dat";
	strs.icsPROTO = "partpos";
	strs.trail = 1000;
	ofstream dummyout;
	
	for(int shape = 0; shape <= nshapes; shape++){
	
		// Setup properties of the source object
		
		object.ep1 = elparam1_start + shape * dep1;
		object.ep2 = elparam2_start;
		
		// Compute the area of the source
		object.area = object.ep1 * object.ep2 * PI;
		
		// Pick the density of each "particle"
		// so that the mass is fixed
		object.dns = object.mass / object.area;
	
		// Set the ID of the object
		object.ID = Int2String(strs.trail + shape);
	
		// Setup the particles
		vector<PARTICLE> particles = SetupParticles(object, box, strs);		

		// If required, dump the forces down the axes
		if(dumpdownaxes)
			DumpForceDownAxes(particles, box);
	
		// These are the coordinates we want the forces at	
		vector<COORDS> points;
		COORDS coord;
	
		coord.loc.push_back(object.ep1+0*box.h);
		coord.loc.push_back(0.0);
		points.push_back(coord);
		coord.loc.clear();
	
		coord.loc.push_back(0.0);
		coord.loc.push_back(object.ep2+0*box.h);
		points.push_back(coord);
		coord.loc.clear();
		
		if(dumpatpoints){
			vector<double> modfpoints = DumpForceAtPoints(particles, box, points, dummyout);
			dump << object.ep2/object.ep1 << " " << modfpoints[1]/modfpoints[0] << endl;
			cout << "np = " << particles.size() << " ";
		//	cout << "den = " << object.dns << " ";
			cout << "ep1 = " << object.ep1 << ", ep2 = " << object.ep2 << " ";
	 	//	cout << "aspect ratio = " << object.ep2/object.ep1 << ", ";
			cout << "f1 = " << modfpoints[1] << ", f2 = " << modfpoints[0] << ", ";
			cout << "ratio = " << modfpoints[1]/modfpoints[0] << endl;
//			cout << endl;
		}
		points.clear();		
				
	}
	
	dump.close();
	
} // END main()




