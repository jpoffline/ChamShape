/*

	evolver.h

*/


double solve(){
	
	double energy,energy_phi,energy_grav,oldenergy;
	double phi,phi_ip1,phi_im1,phi_jp1,phi_jm1;
    double x,y;
	int    ip1,im1,jp1,jm1,ip2,im2,jp2,jm2;
	int	   tt,tp;
    double h2=h*h;
	bool   dump=false;
    int    filenum=0;
	int    trail=10000;
	double eom,lap;
	double dfdx,dfdy;
	double fd[2];
	string filename;
	ofstream timehist,filedump;  
	
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
	
	
	// zero integrated energy
	energy=0.0;
	
    // Begin evolution
    for(int t=0;t<ttot;t++){
	
        // Set the time-step counters for arrays
		tt=t%2;tp=tt+1;
		if(tt==1)tp=0;
	
		// If outputting to file, setup that file
		if(( (t%filedumpfreq==0 || t==ttot-1) && dumptofile) || t==ttot-1){
			dump=true;
			filename=outDIR+filePREFIX+"_"+to_string(trail+filenum)+".dat";
			if(t==ttot-1)
				filename = outDIR+filePREFIX+"_final.dat";
			filedump.open(filename);
		} 
	
	
		
		// dump current energy into the old energy 
		oldenergy=energy;
		// zero the integrated energy
		energy_phi=0.0;
		energy_grav=0.0;
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
				
					// The updating algorithms
					if(c==0){
						// Gradient flow for the chameleon scalar
						eom=lap-getdpot(phi)-getmattdensity(x,y)/M;
						energy_phi=energy_phi+eom*h2;
						fld[tp][c][i][j]=ht*eom+phi;							
					}
					if(c==1){
						eom=lap+getmattdensity(x,y);
						// Gauss-Seidel updating algorithm for gravitational potential
						fld[tp][c][i][j]=0.25*(fld[tt][c][ip1][j]+fld[tp][c][im1][j]+fld[tt][c][i][jp1]+fld[tp][c][i][jm1]+h2*getmattdensity(x,y));
		                energy_grav=energy_grav+(fld[tp][c][i][j] - fld[tt][c][i][j])*h2;
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
					filedump << " " << getmattdensity(x,y) << " " << eom << " " << fd[0] << " " << fd[1] << endl;

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
			dump=false;
			filenum++;
        }
	
		// Dump timehistory
		timehist << t*ht << " " << energy_phi << " " << energy_grav << endl;
		// Dump to screen
		if(t%screendumpfreq==0)
			cout << t << "/"  << ttot << " " << energy_phi << " " << energy_grav << endl;
		
	
	
    }// end t-loop

	// Close timehistory file
	timehist.close();

	return 1.0;
	
} // END solve()
