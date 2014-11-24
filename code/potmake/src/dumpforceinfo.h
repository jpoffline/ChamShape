/*

	dumpforceinfo.h

*/


vector<double> GetPotAtPoints(vector<PARTICLE> particles, vector<COORDS> points){
	
	
	// Vector to hold the gravitational potential (grav.pot) returned from 
	// 
	double gpot;
	
	// Vector to hold grav.pot for each of the locations of interest
	vector<double> gpots;
		
	// Loop over all the locations of interest	
	for(int location = 0; location < points.size(); location++){
		
		// Get the grav.pot at this location
		gpot = getGpot(points[location].loc, particles);
		
		// Dump the computed grav.pot into the vector to be returned
		gpots.push_back( gpot );
		
	}

	return gpots;
	
} // END GetPotAtPoints()

vector<double> GetForceAtPoints(vector<PARTICLE> particles, vector<COORDS> points){
	
	////////////////////////////////////////////////////////////////////////////
	//
	// Function to get the forces at given "interesting" locations.
	// INPUT:  Vector of particles, 
	//         Vector containing the coordinates at which we want the forces at.
	//
	// OUTPUT: Vector whose entries are |F| for each of the input points
	//
	////////////////////////////////////////////////////////////////////////////
	
	// Vector to hold the forces returned from GetForce
	vector<double> force;
	
	// Double to hold |F| for a given location
	double modforce;
	
	// Vector to hold |F| for each of the locations of interest
	vector<double> modforces;
		
	// Loop over all the locations of interest	
	for(int location = 0; location < points.size(); location++){
		
		// Get the force at this location
		force = GetForce(points[location].loc, particles);
		
		// Compute |F| at this location
		modforce = 0.0;
		for(int c = 0; c < force.size(); c++)
			modforce += pow( force[c] , 2.0 );
		modforce = sqrt( modforce );
		
		// Dump the computed |F| into the vector to be returned
		modforces.push_back( modforce );
		
	}

	return modforces;
	
} // END DumpForceAtPoints()

void DumpForceDownAxes(vector<PARTICLE> particles, struct GRID box, struct BOOKKEEPING strs){
	
	/*
	
		Routine to dump the gravitational force down the x- and y-axes
	
	*/
	
	vector<double> loc;
	vector<double> force;
	double modF, gpot;
	ofstream dumpFx, dumpFy;
	string filename;
	filename = strs.outDIR + strs.mainID + strs.ID + strs.filexPROTO + strs.fileSUFFIX;	
	dumpFx.open(filename);
	filename = strs.outDIR + strs.mainID + strs.ID + strs.fileyPROTO + strs.fileSUFFIX;	
	dumpFy.open(filename);
	double pos;
	double h = box.h;
	int imax = box.imax;
	int di = box.di;
	for(int i = 0; i < imax; i = i + di){
		pos = (i - 0.5 * imax) * h;
		
		// Compute F(x,0)
		loc.push_back(pos);
		loc.push_back(0.0);
		force = GetForce(loc, particles);
		gpot = getGpot(loc,particles);
		loc.clear();
		
		modF = 0.0;
		for(int c = 0; c < force.size(); c++)
			modF += force[c] * force[c];
		modF = sqrt(modF);
		
		// Check the force for sanity (mainly, if nan)
		modF = checkFieldSanity(modF);
		gpot = checkFieldSanity(gpot);
		dumpFx << pos << " " << modF << " " << gpot << endl;
		
		
		// Compute F(0,y)
		loc.push_back(0.0);
		loc.push_back(pos);
		force = GetForce(loc, particles);
		gpot = getGpot(loc,particles);
		loc.clear();
		
		modF = 0.0;
		for(int c = 0; c < force.size(); c++)
			modF += force[c] * force[c];
		modF = sqrt(modF);
		
		// Check the force for sanity (mainly, if nan)
		modF = checkFieldSanity(modF);
		gpot = checkFieldSanity(gpot);
		dumpFy << pos << " " << modF <<  " " << gpot << endl;
		
		
	}
	
	dumpFx.close();
	dumpFy.close();
	
} // END DumpForceDownAxes()

void DumpForcePlane(vector<PARTICLE> particles, struct GRID box, struct BOOKKEEPING strs){
	
	/*
	
		Routine to dump the gravitational force in a plane
	
	*/
	
	vector<double> loc;
	vector<double> force;
	double modF, gpot;
	ofstream dumpF;
	string filename;
	filename = strs.outDIR + strs.mainID + strs.ID + strs.filepPROTO + strs.fileSUFFIX;	
	dumpF.open(filename);

	double x, y;
	double h = box.h;
	int imax = box.imax;
	int jmax = box.jmax;
	int di = box.di;
	
	for(int i = 0; i < imax; i = i + di){
		x = (i - 0.5 * imax) * h;
		for(int j = 0; j < jmax; j = j + di){
			y = (j - 0.5 * jmax) * h;	
			
			// Compute F(x,y)
			loc.push_back(x);
			loc.push_back(y);
			force = GetForce(loc, particles);
			gpot = getGpot(loc,particles);
			loc.clear();
			
			modF = 0.0;
			for(int c = 0; c < force.size(); c++)
				modF += force[c] * force[c];
			
			modF = sqrt(modF);
			
			// Check the force for sanity (mainly, if nan)
			modF = checkFieldSanity(modF);
			gpot = checkFieldSanity(gpot);
			dumpF << x << " " << y << " " << modF <<  " " << gpot << endl;
			
			
		}
		
		dumpF << endl;
		
	}
	
	dumpF.close();
	
} // END DumpForcePlane()


// EOF