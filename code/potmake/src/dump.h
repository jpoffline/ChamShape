/*

	dump.h

*/


void DumpForceDownAxes(vector<PARTICLE> particles, struct GRID box){
	
	vector<double> loc;
	vector<double> force;
	double modF;
	ofstream dumpFx, dumpFy;
	dumpFx.open("fileFx.dat");
	dumpFy.open("fileFy.dat");
	double pos;
	double h = box.h;
	int imax = box.imax;
	for(int i = 0; i < imax; i++){
		pos = (i - 0.5 * imax) * h;
		
		// Compute F(x,0)
		loc.push_back(pos);
		loc.push_back(0.0);
		force = GetForce(loc, particles);
		loc.clear();
		modF = 0.0;
		for(int c = 0; c < force.size(); c++)
			modF += force[c] * force[c];
		modF = sqrt(modF);
		
		dumpFx << pos << " " << modF << endl;
		
		// Compute F(0,y)
		loc.push_back(0.0);
		loc.push_back(pos);
		force = GetForce(loc, particles);
		loc.clear();
		modF = 0.0;
		for(int c = 0; c < force.size(); c++)
			modF += force[c] * force[c];
		modF = sqrt(modF);
		
		dumpFy << pos << " " << modF << endl;
		
	}
	
	dumpFx.close();
	dumpFy.close();
	
} // END DumpForceDownAxes()

vector<double> DumpForceAtPoints(vector<PARTICLE> particles, struct GRID box, vector<COORDS> points, ostream& whereto){
	
	// Get the forces at given "interesting" locations
	whereto << "Force at" << endl;
	
	// Vector to hold the forces returned from GetForce
	vector<double> force;
	
	// Double to hold |F| for a given location
	double modforce;
	
	// Vector to hold |F| for each of the points of interest
	vector<double> modforces;
		
	for(int c = 0; c < points.size(); c++){
		
		// Get the force at this location
		force = GetForce(points[c].loc, particles);
		
		// Compute |F| at this location
		cout << force[0] << " " << force[1] << endl;
		modforce = sqrt( pow( force[0] , 2.0 ) + pow( force[1] , 2.0 ) );
		
		whereto << "(";
		
		for(int cc = 0; cc < points[c].loc.size(); cc++){
			whereto << points[c].loc[cc];
			if(cc != points[c].loc.size()-1)
				whereto << ", ";
		}
		
		whereto << ") = " << modforce;
		
		if( c != points.size() - 1 )
			whereto << endl;
		else
			whereto << " ";
		
		modforces.push_back(modforce);
		
	}

	for(int c = 1; c < modforces.size(); c++)
		whereto << modforces[c] / modforces[c-1] << " " ;
	whereto << endl;
	
	
	return modforces;
	
} // END DumpForceAtPoints()


// EOF