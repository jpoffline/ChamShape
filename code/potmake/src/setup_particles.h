/*

	setup.h

*/


bool CheckInsideObject(struct OBJECT obj, double x, double y){
	
	// Function to check whether the given spatial coordinates is
	// inside the object
	
	if(obj.type=="ellipse" && abs(x) < obj.ep1 * sqrt(1.0 - pow( y / obj.ep2, 2.0 )))
		return true;
	else
		return false;
	
} // END CheckInsideObject()


vector<PARTICLE> SetupParticles(struct OBJECT object, struct GRID box, struct BOOKKEEPING strs){
	
	// Setup particles
	
	vector<PARTICLE> particles;
	int imax = box.imax;
	int jmax = box.jmax;
	double h = box.h;
	double x, y;
	
	vector<double> locs;
	PARTICLE particle;
	bool putparticle = false;
	for(int i = 0; i < imax; i++){
		x = (i - 0.5 * imax) * h;
		for(int j = 0; j < jmax; j++){
			y = (j - 0.5 * jmax) * h ;		
			
			// If we are inside the ellipse, then put a particle here
			if( CheckInsideObject(object,x,y) )
				putparticle = true;
			
			if( putparticle ){
				particle.mass = object.dns;
				locs.push_back(x);
				locs.push_back(y);
				particle.location = locs;
				particles.push_back(particle);
				locs.clear();
			}
			
			putparticle = false;

		}
	}
	
	// Dump particle positions to file
	ofstream dump;
	string filename = strs.outDIR + strs.mainID + object.ID + strs.icsPROTO + strs.fileSUFFIX;
	dump.open(filename);
	for(int n = 0; n < particles.size(); n ++){	
		dump << n << " ";
		for(int c = 0; c < particles[n].location.size(); c ++)
			dump << particles[n].location[c] << " ";
		dump << particles[n].mass;
		dump << endl;
	}		
	dump.close();
	
	return particles;
	
} // END SetupParticles()