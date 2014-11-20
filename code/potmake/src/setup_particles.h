/*

	setup.h

*/

vector<double> GetCoeffs(struct OBJECT obj){
	
	/*
	
		Coefficients, a_l, to construct Barrett's apple
	
	*/
	
	vector<double> coeff;
	
	if(obj.type=="legpoly"){
		if(obj.type2=="apple"){
			// Coefficients to create an "apple",
			// as in the Barrett's 1989 Nature paper
			
			coeff.push_back(0.3482169);
			coeff.push_back(0.0969634);
			coeff.push_back(-0.0450812);
			coeff.push_back(0.0346095);
		 	coeff.push_back(-0.0304927);
			coeff.push_back(0.0276200);
			coeff.push_back(-0.0245809);
			coeff.push_back(0.0209728);
			coeff.push_back(-0.0168116);
			coeff.push_back(0.0123419);
			coeff.push_back(-0.0079524);
			coeff.push_back(0.0041198);
			coeff.push_back(-0.0013419);
			
		}
	}
	
	return coeff;
	
} // END GetCoeffs()

double computeLEGS(struct OBJECT obj, double x, double y){
	
	/*
		
		Use a sum over Legendre polynomials to define
		the shape of the source object.
	
	*/
	
	// Compute theta = arctan(y/x)
	double theta = atan2(y,x);
	
	// Compute cos(theta)
	double costheta = cos(theta);
	
	// Go get the coefficients
	vector<double> coeff = GetCoeffs(obj);
	
	// Zero the returned profile
	double prof = 0.0;	
	
	// Compute r(theta) = SUM_l a_l P_l(cos theta)	
	for(int l = 0; l < coeff.size(); l++)
		prof += coeff[l] * gsl_sf_legendre_Pl(l,costheta);
	
	// Return this profile
	return prof;
	
} // END computeLEGS()


bool CheckInsideObject(struct OBJECT obj, double x, double y){
	
	// Function to check whether the given spatial coordinates is
	// inside the object
	
	if(obj.type=="ellipse" && abs( x ) < obj.ep1 * sqrt(1.0 - pow( y / obj.ep2, 2.0 )))
		return true;
	if(obj.type=="legpoly" && x * x + y * y < computeLEGS( obj, x, y ) )
		return true;
	else
		return false;
	
} // END CheckInsideObject()


vector<PARTICLE> SetupParticles(struct OBJECT object, struct GRID box, struct BOOKKEEPING strs){
	
	// Setup particle positions
	
	// Vector to be returned, containing the particle coordinates, and masses
	vector<PARTICLE> particles;
	
	// Extract useful quantities from the inputed structs
	int imax = box.imax;
	int jmax = box.jmax;
	double h = box.h;
	double x, y;
	
	// Temporary vector to hold the particle's coordinate
	vector<double> locs;
	PARTICLE particle;
	for(int i = 0; i < imax; i++){
		x = (i - 0.5 * imax) * h;
		for(int j = 0; j < jmax; j++){
			y = (j - 0.5 * jmax) * h ;		
			
			// If we are inside the shape, then put a particle here

			if( CheckInsideObject(object,x,y) ){
				
				locs.push_back(x);
				locs.push_back(y);
				particle.location = locs;
				particles.push_back(particle);
				locs.clear();
				
			}
		}
	}
	
	// Set the mass of the particles such that the total mass is "object.mass",
	// as defined by the user in params.ini
	for(int n = 0; n < particles.size(); n++)
		particles[n].mass = object.mass / particles.size();
	
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


// EOF