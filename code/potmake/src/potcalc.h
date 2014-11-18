/*

	potcalc.h

*/

double getGpot(vector<double> pos, vector<PARTICLE> par){
	
	// Variable to hold denominator in the calculation
	double den;
	
	// Gravitational potential to be returned
	double gpot = 0.0;
	
	// How many spatial dimensions are there?
	int dims = pos.size();	 
	
	for(int n = 0; n < par.size(); n++){

		den = 0.0;
		for(int c = 0; c < dims; c++)
			den += pow(pos[c] - par[n].location[c],2.0);
		gpot += - par[n].mass / pow(den,0.5);

	}
	
	return gpot;
	
} // END getGpot()


// EOF