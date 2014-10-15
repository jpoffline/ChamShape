/*

	pot.h

	Contains scalar potential V(phi), and V'(phi)

*/


double getpot(double phi){
	
	
	if(pottype==1)
		return Lambda5 / phi;
	else
		return 0.0;
	
}

double getdpot(double phi){
	
	if(pottype==1){
		return - Lambda5/phi/phi;
	}
	else
		return 0.0;
		
}

