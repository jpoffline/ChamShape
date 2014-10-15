/*

	evolver.h

*/


double solve(){
	
	double error_phi=0.0,error_grav=0.0,olderror_phi,olderror_grav;
	double phi,phi_ip1,phi_im1,phi_jp1,phi_jm1;
    double x,y;
	int    tt,tp,ip1,im1,jp1,jm1,ip2,im2,jp2,jm2;
    double h2=h*h;
	bool   dump=false;
    int    filenum=0;
	int    trail=10000;
	double eom,lap;
	double dfdx,dfdy;
	double fd[2];
	// SoR parameter used to relax Poisson equation
	double SORparam=2.0/(1.0+PI/imax);
	string filename;
	ofstream timehist,filedump,filexdump;  
	
	// Set min & max grid-points to be solved
	// where "min" is the bl - boundary layer
	int iminb = bl;
	int imaxb = imax-bl;
	int jminb = bl;
	int jmaxb = jmax-bl;
	
	// Get file name of timehistory
	filename=outDIR+filePREFIX+"_"+timehistoryproto+".dat";
	
	// Open up timehistory file
	timehist.open(filename);
	
    // Begin evolution
    for(int t=0;t<ttot;t++){
	
        // Set the time-step counters for arrays
		tt=t%2;tp=tt+1;
		if(tt==1)tp=0;
	
		// If outputting to file, setup that file
		if(( (t%filedumpfreq==0 || t==ttot-1) && dumptofile) || t==ttot-1){
			dump=true;
			
			// open up full 2D-field files
			if(t==ttot-1)
				filename = outDIR+filePREFIX+"_final.dat";
			else
				filename=outDIR+filePREFIX+"_"+to_string(trail+filenum)+".dat";
			
			filedump.open(filename);
			
			// open up x-field files
			if(t==ttot-1)
				filename = outDIR+filePREFIX+"_x_final.dat";
			else
				filename=outDIR+filePREFIX+"_x_"+to_string(trail+filenum)+".dat";
			filexdump.open(filename);
		} 
	
	
		
		// dump current energy into the old energy 
		olderror_phi=error_phi;
		olderror_grav=error_grav;
		// zero the integrated energy
		error_phi=0.0;
		error_grav=0.0;
		// Begin run over space
        for(int i=iminb;i<imaxb;i++){
            
			x=(i-0.5*imax)*h;
			ip1=i+1;im1=i-1;
			ip2=i+2;im2=i-2;
			
            for(int j=jminb;j<jmaxb;j++){
            	
			    y=(j-0.5*jmax)*h;
                jp1=j+1;jm1=j-1;                
				jp2=j+2;jm2=j-2;
				
				// Now for the main evolution and analysis rountines
				for(int c=0; c<nflds;c++){
					// Get phi at this location for easier reading
	                phi=fld[tt][c][i][j];
				
					phi_ip1=fld[tt][c][ip1][j];
					phi_im1=fld[tt][c][im1][j];
					phi_jp1=fld[tt][c][i][jp1];
					phi_jm1=fld[tt][c][i][jm1];			
			 
					//lap=(phi_ip+phi_im+phi_jp+phi_jm-4.0*phi)/h2;
				
					// Fourth order accurate laplacian
					// Really flipping accurate, but takes slightly longer to compute
					lap = (-fld[tt][c][ip2][j]+16.0*phi_ip1-30.0*phi+16.0*phi_im1-fld[tt][c][im2][j])/12.0/h2
						+ (-fld[tt][c][i][jp2]+16.0*phi_jp1-30.0*phi+16.0*phi_jm1-fld[tt][c][i][jm2])/12.0/h2;
				
					// The updating algorithms, also computes an error measurement
					if(c==0){
						// Gradient flow for the chameleon scalar
						eom=lap-getdpot(phi)-matterdensity[i][j]/M;
						fld[tp][c][i][j]=ht*eom+phi;
						
						// The error measurement is phidot								
						error_phi=error_phi+eom*h2;
					
					}
					
					if(c==1){
						// SoR updating algorithm for gravitational potential
						// Second order accuracy
						fld[tp][c][i][j]=(1.0-SORparam)*fld[tt][c][i][j]
												+0.25*SORparam*(fld[tt][c][ip1][j]+fld[tp][c][im1][j]+fld[tt][c][i][jp1]
												+fld[tp][c][i][jm1]+h2*matterdensity[i][j]);
						
						// Compute derivatives to compute force
						// for error measurement; uses second order for brevity
						dfdx=(phi_ip1-phi_im1)/2.0/h;
						dfdy=(phi_jp1-phi_jm1)/2.0/h;
					    error_grav=error_grav+sqrt(dfdx*dfdx+dfdy*dfdy)*h2;
					}
					
					
				}
				
						
				// Dump to file
				if(dump){
					for(int c=0; c<nflds;c++){
						// Fourth order accurate first derivatives
						dfdx=(-fld[tt][c][ip2][j]+8.0*fld[tt][c][ip1][j]-8.0*fld[tt][c][im1][j]+fld[tt][c][im2][j])/12.0/h;
						dfdy=(-fld[tt][c][i][jp2]+8.0*fld[tt][c][i][jp1]-8.0*fld[tt][c][i][jm1]+fld[tt][c][i][jm2])/12.0/h;					
						// |F| 						
						fd[c]=sqrt(dfdx*dfdx+dfdy*dfdy);
					}
					
					filedump << x << " " << y << " " << fld[tt][0][i][j] << " " << fld[tt][1][i][j];
					filedump << " " << matterdensity[i][j] << " " << fd[0] << " " << fd[1] << endl;
					

					if(y==0){
						filexdump << x << " " << fld[tt][0][i][j] << " " << fld[tt][1][i][j];
						filexdump << " " << matterdensity[i][j] << " " << fd[0] << " " << fd[1] << endl;
					}	
				}
				
				
            } // end j-loop
		
			 
		
			// Print a newline to file
			// Dump to file
			if(dump)
				filedump << endl;	
		
		
        } // end i-loop
	
	
		// Close the output file
        if(dump){
        	filedump.close();
			filexdump.close();
			dump=false;
			filenum++;
        }
	
		// Dump timehistory
		timehist << t*ht << " " << error_phi << " " << error_grav ;
		timehist << " " << (error_grav - olderror_grav)/ht << " " << (error_phi - olderror_phi)/ht << endl;
		
		// Dump to screen
		if(t%screendumpfreq==0){
			cout << t << "/"  << ttot << " " << error_phi << " " << error_grav;
			cout  << " " << (error_grav - olderror_grav)/ht << " " << (error_phi - olderror_phi)/ht << endl;
		}
		// Rescale gravitational potential
		// Note: Laplace's equation, nabla^2Phi = - rho, is invariant under Phi -> Phi + c1 x + c2 x^2
	
    }// end t-loop

	// Close timehistory file
	timehist.close();

	return 1.0;
	
} // END solve()
