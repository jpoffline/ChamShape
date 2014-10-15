/*

	ics.h

	Contains initial conditions

*/

double initialconditions(double phi_bg){
	
	for(int i=0;i<imax;i++){
		for(int j=0;j<jmax;j++){
			if(inittype == 0){
				for(int tt=0;tt<2;tt++){
					fld[tt][0][i][j]=phi_bg;
					fld[tt][1][i][j]=0.0;
				}
			}	
		}
	}
	
	return 1.0;
	
} // END initialconditions()