/*

	ics.h

	Contains initial conditions
	Sets up matter distribution and scalar fields.

*/


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

vector<double> initialconditions(double phi_bg){
		
	double x,y,r;
	double mass_object=0.0;
	double mass_biggest_sphere=0.0;
	
	// Parameters for squashing triangles
	// these are the dimensions of the triangle
	double l1=elparam1;
	double l2=elparam2;
	double l3=sqrt(l1*l1-(l2/2.0)*(l2/2.0));
	double mCA=2*l3/l2;
	double cCA=l3/2;
	double mAB=-2*l3/l2;
	double cAB=l3/2;

	double largestdist;
	
	if(elparam1>elparam2)
		largestdist=elparam1;
	else
		largestdist=elparam2;
	
	
	for(int i=0;i<imax;i++){
		x=(i-0.5*imax)*h;
		for(int j=0;j<jmax;j++){
			y=(j-0.5*jmax)*h;
			r=sqrt(x*x+y*y);
			
			
			// Spherical matter distribution
			if(mattdisttype==1){
			  if(abs(x) < sqrt(obj_size*obj_size-y*y))
			     matterdensity[i][j]=obj_density;
			  else
			     matterdensity[i][j]=obj_rhobg;
			}
			
			// elliptical distribution
			if(mattdisttype==2){
				if(abs(x) < elparam1*sqrt(1.0-y*y/elparam2/elparam2))
					matterdensity[i][j]=obj_density;
				else
					matterdensity[i][j]=obj_rhobg;
			}
			
			// crossed ellipses
			if(mattdisttype==3){
				if(abs(x)<elparam1*sqrt(1.0-y*y/elparam2/elparam2) || abs(y)<elparam1*sqrt(1.0-x*x/elparam2/elparam2))
					matterdensity[i][j]=obj_density;
				else
					matterdensity[i][j]=obj_rhobg;
			}
			
			// rectangle
			if(mattdisttype==4){
				if(abs(x) < elparam1 && abs(y) < elparam2)
					matterdensity[i][j]=obj_density;
				else
					matterdensity[i][j]=obj_rhobg;
			}
			
			
			// triangle
			if(mattdisttype==5){
				if( y>-0.5*l3 && y<mCA*x+cCA && y<mAB*x+cAB )
					matterdensity[i][j]=obj_density;
				else
					matterdensity[i][j]=obj_rhobg;
			}
			
			if(mattdisttype==6){
				if((abs(x)<elparam1+elparam2 && abs(x)>elparam1-elparam2))
					matterdensity[i][j]=obj_density;
				else
					matterdensity[i][j]=obj_rhobg;
			}
			
			if(mattdisttype==7){
				if(x * x + y * y < 4.0 * computeLEGS( "legpoly", "apple", x, y ))
					matterdensity[i][j]=obj_density;
				else
					matterdensity[i][j]=obj_rhobg;
			}
			
			//  find the area
			if(matterdensity[i][j]==obj_density)
				mass_object++;
			
			if(r<largestdist && matterdensity[i][j]==obj_rhobg)
				mass_biggest_sphere+=matterdensity[i][j];
			
			// set the initial conditions for the chameleon and gravitational scalar
			if(inittype == 0){
				for(int tt=0;tt<2;tt++)
					fld[tt][0][i][j]=phi_bg;
			}	
			
			
			
		}
	}
	
	mass_object = mass_object * h * h * obj_density;
	
	vector<double> rets; 
	rets.push_back(mass_object);
	rets.push_back(mass_biggest_sphere*h*h);
	
	// send the total mass back
	return rets;
	
} // END initialconditions()
