/*

	solve.h

*/


vector<double> solve(){
	
	double error_phi=1.0E12,error_grav=1.0E12;
	double olderror_phi,olderror_grav;
	double int_CHAMforce,int_GRAVforce;
	double phi,phi_ip1,phi_im1,phi_jp1,phi_jm1;
    double x,y;
    double h2=h*h;
	int    tt,tp,ip1,im1,jp1,jm1,ip2,im2,jp2,jm2;
	bool   dump=false; // initial setup of the dump-checker
    int    filenum=0;
	double eom,lap;
	double dfdx,dfdy;
	double fd[2];
	double phierrdens;
	double maxCHAMforce_x=0.0,maxCHAMforce_y=0.0;
	double maxGRAVforce_x=0.0,maxGRAVforce_y=0.0;
	// SoR parameter used to relax Poisson equation
	double SORparam=2.0/(1.0+PI/imax);
	string filename;
	ofstream timehist,filedump,filexdump,fileydump,filexydump;  
	bool killnext=false;
	double errorTHRESH=5.0E-10;
	double GlobalMaxForceRatio=0.0;
	double GlobalMaxForceRatio_xpos,GlobalMaxForceRatio_ypos,GlobalMaxForceRatio_dens;
	
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
	cout << endl;
	cout << "Begin relaxation to find chameleon and gravitational potential shapes" << endl;
	cout << endl;
    for(int t=0;t<ttot;t++){
	
		// If the errors are below the acceptable threshold, kill.
		// The errors are the integrated values of the "violation" of the equations of motion.
		if(abs(error_phi) < errorTHRESH && abs(error_grav) < errorTHRESH)
			killnext=true;
	
        // Set the time-step counters for arrays
		tt=t%2;tp=tt+1;
		if(tt==1)tp=0;
	
		// If outputting to file, setup that file
		if(( (t%filedumpfreq==0 || t==ttot-1) && dumptofile) || t==ttot-1 || killnext){
			dump=true;
			
			// open up full 2D-field files
			if(t==ttot-1 || killnext)
				filename = outDIR+filePREFIX+"_final.dat";
			else
				filename=outDIR+filePREFIX+"_uptodate.dat";				
			filedump.open(filename);
			
			// open up x-field files
			if(t==ttot-1 || killnext)
				filename = outDIR+filePREFIX+"_x_final.dat";
			else
				filename=outDIR+filePREFIX+"_x_uptodate.dat";	
			filexdump.open(filename);
			
			// open up y-field files
			if(t==ttot-1 || killnext)
				filename = outDIR+filePREFIX+"_y_final.dat";
			else
				filename=outDIR+filePREFIX+"_y_uptodate.dat";
			fileydump.open(filename);
			
			// open up y-field files
			if(t==ttot-1 || killnext)
				filename = outDIR+filePREFIX+"_xy_final.dat";
			else
				filename=outDIR+filePREFIX+"_xy_uptodate.dat";
			filexydump.open(filename);
			
		} 
	
	
		
		// Dump current errors into the old errors:
		olderror_phi=error_phi;
		olderror_grav=error_grav;
		
		// Zero the integrated errors:
		error_phi=0.0;
		error_grav=0.0;
		
		// Note: also tracking the integrated forces.
		// They must be zeroed here too
		int_CHAMforce=0.0;
		int_GRAVforce=0.0;
		
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
				
					// Frequently used "forward" and "backward" values of phi
					phi_ip1=fld[tt][c][ip1][j];
					phi_im1=fld[tt][c][im1][j];
					phi_jp1=fld[tt][c][i][jp1];
					phi_jm1=fld[tt][c][i][jm1];			
			 
					// Second order accurate laplacian
					lap=(phi_ip1+phi_im1+phi_jp1+phi_jm1-4.0*phi)/h2;
				
					// Fourth order accurate laplacian
					// Really flipping accurate, but takes slightly longer to compute
					//lap = (-fld[tt][c][ip2][j]+16.0*phi_ip1-30.0*phi+16.0*phi_im1-fld[tt][c][im2][j])/12.0/h2
					//	+ (-fld[tt][c][i][jp2]+16.0*phi_jp1-30.0*phi+16.0*phi_jm1-fld[tt][c][i][jm2])/12.0/h2;
				
					// Compute derivatives to compute force

					dfdx=(phi_ip1-phi_im1)/2.0/h;
					dfdy=(phi_jp1-phi_jm1)/2.0/h;
				
					// The updating algorithms, also computes an error measurement
					
					// Gradient flow for the chameleon scalar
					if(c==0){
						
//						eom=lap-getdpot(phi)-matterdensity[i][j]/M;
//						fld[tp][c][i][j]=ht*eom+phi;

						eom=getdpot(phi)+matterdensity[i][j]/M;
						fld[tp][c][i][j]=(1.0-SORparam)*fld[tt][c][i][j]
												+0.25*SORparam*(fld[tt][c][ip1][j]+fld[tp][c][im1][j]+fld[tt][c][i][jp1]
												+fld[tp][c][i][jm1]-h2*eom);
						
						// error measurement is the violation of the equation of motion								
						phierrdens=lap-eom;
						error_phi=error_phi+phierrdens*h2;
						
						// Also compute error by computing time variation of the integral
						// of the magnitude of the force density
						//dfdx=(-fld[tt][c][ip2][j]+8.0*fld[tt][c][ip1][j]-8.0*fld[tt][c][im1][j]+fld[tt][c][im2][j])/12.0/h;
						//dfdy=(-fld[tt][c][i][jp2]+8.0*fld[tt][c][i][jp1]-8.0*fld[tt][c][i][jm1]+fld[tt][c][i][jm2])/12.0/h;		
					    int_CHAMforce=int_CHAMforce+sqrt(dfdx*dfdx+dfdy*dfdy)*h2;
						
					}
					
					// SoR updating algorithm for gravitational potential
					if(c==1){
						
						// Second order accuracy
						fld[tp][c][i][j]=(1.0-SORparam)*fld[tt][c][i][j]
												+0.25*SORparam*(fld[tt][c][ip1][j]+fld[tp][c][im1][j]+fld[tt][c][i][jp1]
												+fld[tp][c][i][jm1]+h2*matterdensity[i][j]/M);
						
						
					    //error_grav=error_grav+sqrt(dfdx*dfdx+dfdy*dfdy)*h2;
						// error measurement is the violation of the equation of motion								
						error_grav=error_grav+(lap+matterdensity[i][j]/M)*h2;
						int_GRAVforce=int_GRAVforce+sqrt(dfdx*dfdx+dfdy*dfdy)*h2;
					}
					
					
				}
				
						
				// Dump to file
				if(dump){
					for(int c=0;c<nflds;c++){
						// Fourth order accurate first derivatives
						dfdx=(-fld[tt][c][ip2][j]+8.0*fld[tt][c][ip1][j]-8.0*fld[tt][c][im1][j]+fld[tt][c][im2][j])/12.0/h;
						dfdy=(-fld[tt][c][i][jp2]+8.0*fld[tt][c][i][jp1]-8.0*fld[tt][c][i][jm1]+fld[tt][c][i][jm2])/12.0/h;					
						// |F| 						
						fd[c]=sqrt(dfdx*dfdx+dfdy*dfdy);
					}
					
					filedump << x << " " << y << " " << fld[tt][0][i][j] << " " << fld[tt][1][i][j];
					filedump << " " << matterdensity[i][j] << " " << fd[0] << " " << fd[1] << " " << phierrdens << endl;
					
					// Output down the x-axis
					if(y==0){
						filexdump << x << " " << fld[tt][0][i][j] << " " << fld[tt][1][i][j];
						filexdump << " " << matterdensity[i][j] << " " << fd[0] << " " << fd[1] << " " << phierrdens << endl;

						// Find max force in x-direction
						if(fd[0]>maxCHAMforce_x)
							maxCHAMforce_x=fd[0];
						
						if(fd[1]>maxGRAVforce_x)
							maxGRAVforce_x=fd[1];

					}	
					
					// Output down the y-axis
					if(x==0){
						fileydump << y << " " << fld[tt][0][i][j] << " " << fld[tt][1][i][j];
						fileydump << " " << matterdensity[i][j] << " " << fd[0] << " " << fd[1] << " " << phierrdens << endl;

						// Find max force in y-direction
						if(fd[0]>maxCHAMforce_y)
							maxCHAMforce_y=fd[0];
						
						if(fd[1]>maxGRAVforce_y)
							maxGRAVforce_y=fd[1];						

					}
					
					// Output down the x=y-axis
					if(i==j){
						filexydump << sqrt(x*x+y*y) << " " << fld[tt][0][i][j] << " " << fld[tt][1][i][j];
						filexydump << " " << matterdensity[i][j] << " " << fd[0] << " " << fd[1] << " " << phierrdens << endl;
					}						
				}
				
				// At the end, find the location of maximum force ratio
				if( (killnext || t==ttot-1) && x!=0 && y!=0){
					if(fd[0]/fd[1]>GlobalMaxForceRatio && matterdensity[i][j]<objdensity){
						GlobalMaxForceRatio=fd[0]/fd[1];
						GlobalMaxForceRatio_xpos=x;
						GlobalMaxForceRatio_ypos=y;
						GlobalMaxForceRatio_dens=matterdensity[i][j];
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
			fileydump.close();
			filexydump.close();
			dump=false;
			filenum++;
        }
	
		// Dump timehistory
		timehist << t*ht << " ";
		timehist << abs(error_phi) << " " << (error_phi - olderror_phi)/ht << " ";
		timehist << abs(error_grav) << " " << (error_grav - olderror_grav)/ht << " ";
		timehist << int_CHAMforce << " " << int_GRAVforce << endl;
		
		// Dump to screen
		if(t%screendumpfreq==0){
			cout << t << "/"  << ttot << " " << abs(error_phi) << " " << abs(error_grav) << " " ;
			cout << (error_grav - olderror_grav)/ht << " " << (error_phi - olderror_phi)/ht << " ";
			cout << int_CHAMforce << " " << int_GRAVforce << endl;
		}
		// Rescale gravitational potential
		// Note: Laplace's equation, nabla^2Phi = - rho, is invariant under Phi -> Phi + c1 x + c2 x^2
	
		if(killnext){
			cout << endl;
			cout << "Errors in chameleon and gravitational scalars are below threshold" << endl;
			cout << "EoM satisfied to less than " << errorTHRESH << endl;
			cout << " > stopping" << endl;
			cout << endl;
			break;
		}
	
    }// end t-loop

	// Close timehistory file
	timehist.close();
	
	// Dump force info into vector
	vector<double> forceinfo;
	// This gets returned back to the main_X.cpp algorithm
	forceinfo.push_back(maxCHAMforce_x);
	forceinfo.push_back(maxCHAMforce_y);
	forceinfo.push_back(maxGRAVforce_x);
	forceinfo.push_back(maxGRAVforce_y);
	forceinfo.push_back(GlobalMaxForceRatio);
	forceinfo.push_back(GlobalMaxForceRatio_xpos);
	forceinfo.push_back(GlobalMaxForceRatio_ypos);	
	forceinfo.push_back(GlobalMaxForceRatio_dens);
	forceinfo.push_back(M);
	forceinfo.push_back(objdensity);
	forceinfo.push_back(obj_rhobg);
	forceinfo.push_back(elparam1);
	forceinfo.push_back(elparam2);
	
	// Print force info: first to screen
	PrintForceInfo(cout,forceinfo);	
	// Now to logfile (its the same info, but call routine which opens up logfile first)
	PrintForceInfoToLogfile(forceinfo);
	
	// Print closing message to screen
	cout << endl;
	cout << "Completed relaxation" << endl;
	cout << endl;	
	
	return forceinfo;
	
} // END solve()
