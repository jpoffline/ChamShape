/*

	ics.h

	Contains initial conditions
	Sets up matter distribution and scalar fields.

*/

double initialconditions(double phi_bg){
	double x,y;
	for(int i=0;i<imax;i++){
		x=(i-0.5*imax)*h;
		for(int j=0;j<jmax;j++){
			y=(j-0.5*jmax)*h;
			
			if(mattdisttype==1)
				// Spherical matter distribution
				matterdensity[i][j] = obj_rhobg*(1+0.5*(objdensity/obj_rhobg-1.0)*(1.0-tanh((sqrt(x*x+y*y)-objsize)/objskindepth)));
			if(mattdisttype==2){
				//pec=(sqrt(x*x+(y+elparam)*(y+elparam))+sqrt(x*x+(y-elparam)*(y-elparam)))/2.0/elparam;
				//matterdensity[i][j] = obj_rhobg*(1+0.5*(objdensity/obj_rhobg-1.0)*(1.0-tanh((pec-objsize)/objskindepth)));
				if(abs(x)<elparam1*sqrt(objsize*objsize-y*y/elparam2/elparam2) || abs(y)<elparam1*sqrt(objsize*objsize-x*x/elparam2/elparam2))
					matterdensity[i][j]=objdensity;
				else
					matterdensity[i][j]=obj_rhobg;
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