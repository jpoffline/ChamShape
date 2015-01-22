
vector<double> GetCoeffs(string type1, string type2){
	
	/*
	
		Coefficients, a_l, to construct Barrett's apple
	
	*/
	
	vector<double> coeff;
	
	if(type1=="legpoly"){
		if(type2=="apple"){
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

double computeLEGS(string type1, string type2, double x, double y){
	
	/*
		
		Use a sum over Legendre polynomials to define
		the shape of the source object.
	
	*/
	
	// Compute theta = arctan(y/x)
	double theta = atan2(y,x);
	
	// Compute cos(theta)
	double costheta = cos(theta);
	
	// Go get the coefficients
	vector<double> coeff = GetCoeffs(type1, type2);
	
	// Zero the returned profile
	double prof = 0.0;	
	
	// Compute r(theta) = SUM_l a_l P_l(cos theta)	
	for(int l = 0; l < coeff.size(); l++)
		prof += coeff[l] * gsl_sf_legendre_Pl(l,costheta);
	
	// Return this profile
	return prof;
	
} // END computeLEGS()