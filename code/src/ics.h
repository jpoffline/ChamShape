/*

	ics.h

	Contains initial conditions
	Sets up up matter distribution and scalar fields.
*/

double initialconditions(double phi_bg){
	double x,y;
	
	for(int i=0;i<imax;i++){
		x=(i-0.5*imax)*h;
		for(int j=0;j<jmax;j++){
			y=(j-0.5*jmax)*h;
			
			if(mattdisttype==1){
				// Spherical matter distribution
				matterdensity[i][j] = obj_rhobg*(1+0.5*(objdensity/obj_rhobg-1.0)*(1.0-tanh((sqrt(x*x+y*y)-objsize)/objskindepth)));
			}
			
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