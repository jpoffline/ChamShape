/*

	solve_chamonly.h

*/


vector<double> solve(){
	
	// Define 
    double x,y;
    double h2=h*h;
	double hh=2.0*h;
	int    tt,tp,ip1,im1,jp1,jm1,ip2,im2,jp2,jm2;
	
	double olderror_phi;
	double int_CHAMforce;
	double phi,phi_ip1,phi_im1,phi_jp1,phi_jm1;
	double GlobalMaxForceRatio_xpos,GlobalMaxForceRatio_ypos,GlobalMaxForceRatio_dens;
	
	double eom,lap,rho;
	double dfdx,dfdy;
	double fd[1];
	string filename;
	ofstream timehist,filedump,filexdump,fileydump,filexydump;  
	
	// Set min & max grid-points to be solved
	// where "min" is the bl - boundary layer
	int iminb = bl;
	int imaxb = imax-bl;
	int jminb = bl;
	int jmaxb = jmax-bl;
	
	struct MAXVALS{
		double maxF[2];
		double pos[2][2];
	};
	int xID = 0;
	int yID = 1;
	MAXVALS max_xdir;
	MAXVALS max_ydir;
	
	// Define and initialize integrated, maximal quantities,
	// and checkers.
	double error_phi=1.0E12;
	
	for(int c=0;c<nflds;c++){
		max_xdir.maxF[c]=0.0;
		max_ydir.maxF[c]=0.0;
	}
		
	
	double GlobalMaxForceRatio=0.0;
	bool   dump=false; // initial setup of the dump-checker
	bool   killnext=false;
    int    filenum=0;
	
	double x0 = 0.0; 
	double y0 = 0.0;
	
 
	
	// Accuracy threshold on chameleon scalar and gravitational potential
	double errorTHRESH=5.0E-8;
	
	// Get file name of timehistory
	filename=outDIR+filePREFIX+"_"+timehistoryproto+".dat";
	
	// Open up timehistory file
	timehist.open(filename);
	
    // Begin evolution
	cout << endl;
	cout << "Begin relaxation to find chameleon scalar shapes" << endl;
	cout << endl;
	
	int c = 0;
	
    for(int t=0;t<ttot;t++){
	
		// If the errors are below the acceptable threshold, kill.
		// The errors are the integrated values of the "violation" of the equations of motion.
		if( abs(error_phi) < errorTHRESH )
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
		
		// Zero the maximum forces
		
		max_xdir.maxF[c]=0.0;
		max_ydir.maxF[c]=0.0;
		
		
		// Dump current errors into the old errors:
		olderror_phi=error_phi;

		
		// Zero the integrated errors:
		error_phi=0.0;
		
		// Note: also tracking the integrated forces.
		// They must be zeroed here too
		int_CHAMforce=0.0;
		
		// Begin run over space
        for(int i=iminb;i<imaxb;i++){
            
			x=(i-0.5*imax)*h;
			ip1=i+1;im1=i-1;
			ip2=i+2;im2=i-2;
			
            for(int j=jminb;j<jmaxb;j++){
            	
			    y=(j-0.5*jmax)*h;
                jp1=j+1;jm1=j-1;                
				jp2=j+2;jm2=j-2;
				
				rho=matterdensity[i][j];
				
				 
					
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

				dfdx=(phi_ip1-phi_im1)/hh;
				dfdy=(phi_jp1-phi_jm1)/hh;
				//dfdx=(-fld[tt][c][ip2][j]+8.0*fld[tt][c][ip1][j]-8.0*fld[tt][c][im1][j]+fld[tt][c][im2][j])/12.0/h;
				//dfdy=(-fld[tt][c][i][jp2]+8.0*fld[tt][c][i][jp1]-8.0*fld[tt][c][i][jm1]+fld[tt][c][i][jm2])/12.0/h;	
				fd[c]=sqrt(dfdx*dfdx+dfdy*dfdy);
				
				// The updating algorithms; also computes an error measurement
				// error measurements are the violation of the equation of motion	
											
				 

				eom = -1.0 / ( phi * phi ) + rho + phi_mass * phi_mass * ( phi - phi_inf );
				
				fld[tp][c][i][j]=ht*(lap-eom)+phi;	
				error_phi=error_phi+(fld[tp][c][i][j]-phi)*h2;
			    int_CHAMforce=int_CHAMforce+fd[c]*h2;
					 
										
					
				// Check to find maximum forces
				if(x==x0){
					if(fd[c]>=max_ydir.maxF[c]){
						max_ydir.maxF[c]=fd[c];
						max_ydir.pos[c][xID]=x;
						max_ydir.pos[c][yID]=y;								
					}
				}	
					
				// Check to find maximum forces
				if(y==y0){
					if(fd[c]>=max_xdir.maxF[c]){
						max_xdir.maxF[c]=fd[c];
						max_xdir.pos[c][xID]=x;
						max_xdir.pos[c][yID]=y;
					}
				}	
						
				// Dump to file
				if(dump){
					
					filedump << x << " " << y << " " << fld[tt][c][i][j] << " ";
					filedump << rho << " " << fd[c] << endl;
					
					// Output down the x-axis
					if(y==y0){
						filexdump << x << " " << fld[tt][c][i][j] << " ";
						filexdump << rho << " " << fd[c] << endl;

					}	
					
					// Output down the y-axis
					if(x==x0){
						fileydump << y << " " << fld[tt][c][i][j] << " ";
						fileydump << rho << " " << fd[c] << endl;						
					}
					
					// Output down the x=y-axis
					if(i==j){
						filexydump << sqrt(x*x+y*y) << " " << fld[tt][c][i][j] << " ";
						filexydump << rho << " " << fd[c] << endl;
					}						
					
				}
				/*
				// At the end, find the location of maximum force ratio
				if( (killnext || t==ttot-1) && x!=0 && y!=0){
					
					if(fd[0]/fd[1]>GlobalMaxForceRatio && rho < obj_density){
						GlobalMaxForceRatio=fd[0]/fd[1];
						GlobalMaxForceRatio_xpos=x;
						GlobalMaxForceRatio_ypos=y;
						GlobalMaxForceRatio_dens=rho;
					}
					
				}
				*/
				
            } // end j-loop
		
		
			// Print a newline to file
			// Dump to file
			if(dump)
				filedump << endl;	
		
		
        } // end i-loop
	
		// If constructing plates, enforce periodic boundaries
		if(mattdisttype==6){
			for(int j=0;j<jminb;j++){
				for(int i=iminb;i<imaxb;i++){
					for(int c=0;c<nflds;c++)
						fld[tp][c][i][j]=fld[tp][c][i][jminb+1];
				}
			}
			for(int j=jmaxb;j<jmax;j++){
				for(int i=iminb;i<imaxb;i++){
					for(int c=0;c<nflds;c++)
						fld[tp][c][i][j]=fld[tp][c][i][jmaxb-1];
				}
			}
		}
	
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
		timehist << int_CHAMforce << " ";
		timehist << fld[tt][0][int(0.5*imax)][int(0.5*jmax)] << " ";
		timehist << max_xdir.maxF[0] << " " << max_ydir.maxF[0] << endl;
		
		// Dump to screen
		if(t%screendumpfreq==0){
			cout << t << "/"  << ttot << " " << abs(error_phi) << " " ;
			cout << (error_phi - olderror_phi)/ht << " ";
			cout << int_CHAMforce << endl;
		}
		// Rescale gravitational potential
		// Note: Laplace's equation, nabla^2Phi = - rho, is invariant under Phi -> Phi + c1 x + c2 x^2
	
		if(killnext){
			cout << endl;
			cout << "Errors in chameleon scalar is below threshold" << endl;
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
	for(int c = 0; c < nflds; c++){
		forceinfo.push_back(max_xdir.maxF[c]);
		forceinfo.push_back(max_xdir.pos[c][xID]);
		forceinfo.push_back(max_xdir.pos[c][yID]);		
		forceinfo.push_back(max_ydir.maxF[c]);
		forceinfo.push_back(max_ydir.pos[c][xID]);
		forceinfo.push_back(max_ydir.pos[c][yID]);		
	}
	
	forceinfo.push_back(GlobalMaxForceRatio);
	forceinfo.push_back(GlobalMaxForceRatio_xpos);
	forceinfo.push_back(GlobalMaxForceRatio_ypos);	
	forceinfo.push_back(GlobalMaxForceRatio_dens);
	forceinfo.push_back(obj_density);
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
