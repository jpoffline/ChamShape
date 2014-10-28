/*

	ics.h

	Contains initial conditions
	Sets up matter distribution and scalar fields.

*/

double initialconditions(double phi_bg){
	
	double x,y;
	double area=0.0;
	
	
	for(int i=0;i<imax;i++){
		x=(i-0.5*imax)*h;
		for(int j=0;j<jmax;j++){
			y=(j-0.5*jmax)*h;
			
			// Spherical matter distribution
			if(mattdisttype==1){
			  if(abs(x) < sqrt(objsize*objsize-y*y))
			     matterdensity[i][j]=objdensity;
			  else
			     matterdensity[i][j]=obj_rhobg;
			}
			
			// elliptical distribution
			if(mattdisttype==2){
				if(abs(x) < elparam1*sqrt(objsize*objsize-y*y/elparam2/elparam2))
					matterdensity[i][j]=objdensity;
				else
					matterdensity[i][j]=obj_rhobg;
			}
			
			// crossed ellipses
			if(mattdisttype==3){
				if(abs(x)<elparam1*sqrt(objsize*objsize-y*y/elparam2/elparam2) || abs(y)<elparam1*sqrt(objsize*objsize-x*x/elparam2/elparam2))
					matterdensity[i][j]=objdensity;
				else
					matterdensity[i][j]=obj_rhobg;
			}
			
			// rectangle
			if(mattdisttype==4){
				if(abs(x) < elparam1 && abs(y) < elparam2)
					matterdensity[i][j]=objdensity;
				else
					matterdensity[i][j]=obj_rhobg;
			}
			
			//  find the area
			if(matterdensity[i][j]==objdensity)
				area++;
			
			// set the initial conditions for the chameleon and gravitational scalar
			if(inittype == 0){
				for(int tt=0;tt<2;tt++){
					fld[tt][0][i][j]=phi_bg;
					fld[tt][1][i][j]=0.0;
				}
			}	
			
			
			
		}
	}
	
	// send the total mass back
	return area*h*h*objdensity;
	
} // END initialconditions()
