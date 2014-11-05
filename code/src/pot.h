/*

	pot.h

	Contains scalar potential V(phi), and V'(phi)
	
	Returns the "dimensionless" forms
	
*/


double getpot(double phi){
	
	
	if(pottype==1)
		return 1.0 / phi;
	else
		return 0.0;
	
}

double getdpot(double phi){
	
	if(pottype==1){
		return -1.0/phi/phi;
	}
	else
		return 0.0;
		
}

