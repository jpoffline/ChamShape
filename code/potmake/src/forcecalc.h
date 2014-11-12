/*

	forcecalc.h

*/

vector<double> GetForce(vector<double> pos, vector<PARTICLE> particles){
	
	// Function to return force at a given position,
	// due to a given set of particles.
	// This algorithm works in an arbitrary number of dimensions.
	
	// Variable to hold denominator in the force calculation
	double den;
	
	// Vector to hold the components of the force.
	// Will be returned
	vector<double> force;
	
	// How many spatial dimensions are there?
	int dims = pos.size();
	
	for(int c = 0; c < dims; c++)
		force.push_back(0.0);
	
	for(int n = 0; n < particles.size(); n++){
		for(int c = 0; c < dims; c++){
			den = 0.0;
			for(int cc = 0; cc < dims; cc++)
				den += pow(pos[cc] - particles[n].location[cc],2.0);
			force[c] += -(pos[c] - particles[n].location[c])/pow(den,1.5);
		}
	}
	
	return force;
	
} // END GetForce()


// EOF