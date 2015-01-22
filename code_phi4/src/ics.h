/*

	ics.h

	Contains initial conditions
	Sets up matter distribution and scalar fields.

*/



bool decidewhere(int type,double x,double y){
	
	// Below each "shape"-type checks to see if the given location
	// is inside or outside the source. If "inside", then "inside = true"
	// is set, and then the matterdensity-array value is set to the internal
	// density value; else, it is set to the prescribed background value.
	
	
	bool where = false;
	
	// Spherical matter distribution
	if(type==1)
	  if(abs(x) < sqrt(obj_size*obj_size-y*y))
	    	where = true;
	
	// ellipse
	if(type==2)
		if(abs(x) < elparam1*sqrt(1.0-y*y/elparam2/elparam2))
			where = true;
	
	// crossed ellipses
	if(type==3)
		if(abs(x)<elparam1*sqrt(1.0-y*y/elparam2/elparam2) || abs(y)<elparam1*sqrt(1.0-x*x/elparam2/elparam2))
			where = true;
	
	// rectangle
	if(type==4)
		if(abs(x) < elparam1 && abs(y) < elparam2)
			where = true;
	
	if(type==6)
		if((abs(x)<elparam1+elparam2 && abs(x)>elparam1-elparam2))
			where = true;
	
	if(type==7)
		if(x * x + y * y < 4.0 * computeLEGS( "legpoly", "apple", x, y ))
			where = true;
	
	return where;
	
} // END decidewhere()

bool outside_bl(int i, int j, int imax, int jmax, int bl){
	
	bool ret = false;
	if(i <= bl || i >= imax - bl || j <= bl || j >= jmax - bl )
		ret = true;
	
	return ret;
	
}

vector<double> initialconditions(double phi_bg, double phi_obj){
		
	double x,y,r;
	double mass_object=0.0;
	double mass_biggest_sphere=0.0;
	double val;
	double largestdist;
	
	if(elparam1>elparam2)
		largestdist=elparam1;
	else
		largestdist=elparam2;
	
	bool inside;
	
	
	string filename = outDIR + filePREFIX + "_ic.dat";
	ofstream dumpic;
	dumpic.open(filename);
	
	for(int i = 0; i < imax; i++){
		x = ( i - 0.5 * imax ) * h;
		for(int j = 0; j < jmax; j++){
			y = ( j - 0.5 * jmax ) * h;
			r = sqrt( x * x + y * y );
			
			////////////////////////////////////////////////
			//
			// 				BEGIN
			// 		Shape-checking algorithms
			//
			////////////////////////////////////////////////
			
			inside = decidewhere(mattdisttype, x, y);
			
			////////////////////////////////////////////////
			//
			// 				END
			// 		Shape-checking algorithms
			//
			////////////////////////////////////////////////
			
			
			// Now we have established whether the given location is
			// inside or outside, set the matterdensity-array value accordingly
			if(inside){
				matterdensity[i][j] = obj_density;
				mass_object++;
			}
			else
				matterdensity[i][j] = obj_rhobg;

			
			if( r < largestdist && matterdensity[i][j] == obj_rhobg)
				mass_biggest_sphere += matterdensity[i][j];
			
			////////////////////////////////////////////////
			//
			// 				BEGIN
			// 		Scalar field initial conditions
			//
			////////////////////////////////////////////////
			
			// Set the initial conditions for the chameleon scalar
			
			
			// For the "simple"-type, set the scalar to its background value
			if(inittype == 0)
				for(int tt = 0; tt < 2; tt++)
					fld[tt][0][i][j] = phi_bg;
			
			
			
			// For "random"-type set the scalar field value to be a uniformly distributed
			// random variable chosen from the interval [0, phi_VAC], where
			// phi_VAC is the value of phi which minimizes the potential
			// in the given location (i.e. depends on whether the location is inside or
			// outside the object).
			if(inittype == 1){
				if(inside)
					val = unitrand() * phi_obj;
				else{
					if(outside_bl( i , j , imax , jmax , bl + 10) )
						val = phi_bg;
					else
						val = phi_bg;
				}
				
				for(int tt = 0; tt < 2; tt++){					
					fld[tt][0][i][j] = val;
				}
			}		
			
			////////////////////////////////////////////////
			//
			// 				END
			// 		Scalar field initial conditions
			//
			////////////////////////////////////////////////
			
			dumpic << x << " " << y << " ";
			dumpic << fld[0][0][i][j] << " " << matterdensity[i][j] << endl;
			
		}
		dumpic << endl;
	}
	
	dumpic.close();
	
	// Compute the mass of the object
	mass_object = mass_object * h * h * obj_density;
	
	vector<double> rets; 
	rets.push_back(mass_object);
	rets.push_back(mass_biggest_sphere*h*h);
	
	// send the total mass back
	return rets;
	
} // END initialconditions()
