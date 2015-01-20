

int main(){
	
	
	while(true){
		// Pick proposed field configuration
		rlx = getLOC(0);
		rly = getLOC(1);
		// Since we only modify one grid point
		field_PROPOSED = field_current;
		field_PROPOSED[rlx][rly][0] = doMODIFY_field( field_current[rlx][rly][0] );
		// Compute "cost" of proposed configuration
		COST_proposed = getCOST(field_PROPOSED)
		// Accept or reject
		if(COST_proposed < COST_current || RAND_num < THING){
			field_current = field_proposed;
			COST_current = COST_proposed;
		}
		
	}

	
	
	
}

int getLOC(int W){
	
	int i = min_cost[W] - 2;
	
	while( i < min_cost[W] || i > max_cost[W] )
		i = randomINT();
	
	return ret;
	
}

double doMODIFY_field(double F){
	
	return F + randomDOUBLE() * MCMC_sigma;
	
}

double getCOST(vector<vector<double> > F){
	
	double COST = 0.0;
	
	for(int i = imin_cost; i < imax_cost; i++){
		
		ip1 = i + 1;
		im1 = i - 1;
		
		for(int j = jmin_cost; j < jmax_cost; j++){
			
			COST += getLAPLACIAN(F[i][j][0],F[ip1][j][0],F[im1][j][0],F[i][j+1][0],F[i][j-1][0])
					 		- getSOURCE( F[i][j][0], F[i][j][1] );

		}

	}
	
	return COST;
	
}

double getLAPLACIAN(phi, phi_ip1, phi_im1, phi_jp1, phi_jm1){
	
	return ( phi_ip1 + phi_im1 + phi_jp1 + phi_jm1 - 4.0 * phi )/ h2;
	
}

double getSOURCE(phi, rho){
	
	return - Lambda / phi / phi + rho + mass * mass * (phi - phi_inf);
	
}