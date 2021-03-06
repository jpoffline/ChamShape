/*

	function to print types info
	... boundary conditions (fixed, periodic, etc)
	... initial conditions (random, idealised, etc)
	... equation of motion (damped, gradient flow, etc)

*/




void printinfo(ostream& whereto, string type, int option){
	
	// Setup identifiers to use in switches
	int typeID;
	
	if(type == "InitialConditions")
		typeID = 1;
	if(type=="Potential")
		typeID = 3;
	whereto << type << " = " << option << " :: ";
	
	switch(typeID){
		 
		case 1:
			switch(option){
				case 0: 
					whereto << "homogeneous field" << endl;
					break;
				default:
					whereto << "cant find a description for " << type << endl;
					break;
			}
			break;
		case 3:
			switch(option){
				case 1: 
					whereto << "Lambda5/phi" << endl;
					break;
				default:
					whereto << "cant find a description for " << type << endl;
					break;
			}
			break;
		default:
			whereto << "dont know what " << type << " is" << endl;
			break;
	}
	
	
} // END printinfo()

/*

	Routines to print messages

*/

// Print a welcome message
void printwelcome(ostream& whereto){
	
	whereto << endl;
	whereto << "------------------------------------------" << endl;
	whereto << "Simple code to solve for Chameleon shapes" << endl;
	whereto << "J. Pearson (Nottingham 2014/15)" << endl;
	whereto << "------------------------------------------" << endl;
	whereto << endl;
	
} // END printwelcome()

// Print top matter -- mainly info about current run
void printtopmatter(ostream& whereto){
	
	whereto << endl;
	whereto << "Simulation conditions/parameters:" << endl;
	whereto << "output dir: " << outDIR << endl;	
	whereto << "(imax, jmax) = (" << imax << ", " << jmax << ")" << endl;
	whereto << "(xmax, ymax) = (" << (double)imax*h << ", " << (double)jmax*h << ")" << endl;
	whereto << "(h, ht) = (" << h << ", " << ht << ")" << endl;
	whereto << "boundary layer = " << bl << " grid-points" << endl;
	whereto << "discretization order = " << derivorder << endl;
	printinfo(whereto,"Potential",pottype);	
	printinfo(whereto,"InitialConditions",inittype);
	whereto << endl;
	whereto << "All data files print out dimensionless fields and forces" << endl;
	whereto << "Solving" << endl;
	whereto << "nabla^2phi = - 1/phi^2 + rho + m^2(phi - phiinf)^2/2" << endl;

	whereto << endl;
	whereto << "Begin solving" << endl;
	whereto << endl;
		
} // END printtopmatter()

void printobjectproperties(ostream& whereto){
	
	whereto << endl;
	whereto << "Source object parameters:" << endl;
	whereto << "mattdisttype = " << mattdisttype;
	if(mattdisttype == 1){
		whereto << " :: spherical" << endl;
		whereto << "size = " << obj_size << endl;
	}
	if(mattdisttype == 2){
		whereto << " :: ellipse " << endl;
		whereto << "(a, b) = (" << elparam1 << ", " << elparam2 << ")" << endl;
	}
	if(mattdisttype == 3){
		whereto << " :: crossed ellipses " << endl;
		whereto << "(a, b) = (" << elparam1 << ", " << elparam2 << ")" << endl;
	}
	if(mattdisttype == 4){
		whereto << " :: square " << endl;
		whereto << "(a, b) = (" << elparam1 << ", " << elparam2 << ")" << endl;
	}
	if(mattdisttype == 5){
		whereto << " :: triangle " << endl;
		whereto << "(a, b) = (" << elparam1 << ", " << elparam2 << ")" << endl;
	}
	
	if(mattdisttype == 7){
		whereto << " :: Barret's apple " << endl;
	}
	
	else
		whereto << endl;
	
	
	whereto << "density = " << obj_density << endl;
	//whereto << "skin depth = " << obj_skindepth << endl;
	whereto << "bg density = " << obj_rhobg << endl;
	whereto << "phi_centre = " << 1.0/sqrt(obj_density) << endl;
	whereto << "M = " << M << endl;	
	whereto << "m = " << phi_mass << endl;
	whereto << "phi_inf = " << phi_inf << endl;
	whereto << "Mpl = " << Mpl << endl;	
	whereto << "Lambda5 = " << Lambda5 << endl;
	whereto << "Lparam = " << Lparam << endl;
	whereto << "totmass = " << totmass << endl;
	whereto << endl;
	
}

// Print final message
void printfinalmessage(ostream& whereto, double te){
	
	string tu="ms";
	if(te>1e3){
		te=te/1e3;
		tu="sec";
	}
	whereto << endl;
	whereto << "OutDIR: " << outDIR << endl;
	whereto << endl;
	whereto << "------------------------------------------" << endl;
	whereto << "Complete in " << te << tu << endl;
	whereto << "------------------------------------------" << endl;
	whereto << endl;
	
} // END printfinalmessage()

// Print info to logfile
void printlog(string when,double v1,double v2){
	
	if(when=="start"){
		string filename = outDIR+filePREFIX+".log";
		ofstream dumplog;
		dumplog.open(filename);
		printwelcome(dumplog);
		printtopmatter(dumplog);
		printobjectproperties(dumplog);
		dumplog.close();
	}
	
	if(when=="end"){
		string filename = outDIR+filePREFIX+".log";
		ofstream dumplog;
		dumplog.open(filename,ios::app);
		printfinalmessage(dumplog, v1);
		dumplog.close();
	}
	
} // END printlog()

// Print info about the forces to general ostream
void PrintForceInfo(ostream& whereto, vector<double> fvals){
	
	int ID = 0;
	
	// extract data from fvals 
	double maxCHAMforce_x = fvals[ID]; ID++;
	double maxCHAMforce_x_pos_x = fvals[ID]; ID++;
	double maxCHAMforce_x_pos_y = fvals[ID]; ID++;	
	double maxCHAMforce_y = fvals[ID]; ID++;
	double maxCHAMforce_y_pos_x = fvals[ID]; ID++;
	double maxCHAMforce_y_pos_y = fvals[ID]; ID++;
		
	
	// Output analysis of maximum forces encountered
	whereto << endl;
	whereto << "cham: maxF(x) = " << maxCHAMforce_x << ", (x,y) = (" <<  maxCHAMforce_x_pos_x << ", " << maxCHAMforce_x_pos_y << ")" << endl;
	whereto << "cham: maxF(y) = " << maxCHAMforce_y << ", (x,y) = (" <<  maxCHAMforce_y_pos_x << ", " << maxCHAMforce_y_pos_y << ")" << endl;
	whereto << "cham: maxF(y) / maxF(x) = " << maxCHAMforce_y / maxCHAMforce_x << endl;
	whereto << endl;
	
	if(maxCHAMforce_x > maxCHAMforce_y)
		whereto << "The value of the largest chameleon force is in the x-direction" << endl;
	else 
		whereto << "The value of the largest chameleon force is in the y-direction" << endl;
	
	
} // END PrintForceInfo()

// Print info about the forces to logfile (this opens up logfile stream, and calls "PrintForceInfo")
void PrintForceInfoToLogfile(vector<double> fvals){
	
	string filename = outDIR+filePREFIX+".log";
	ofstream dumplog;
	dumplog.open(filename,ios::app);
	PrintForceInfo(dumplog,fvals);
	dumplog.close();
	
} // END PrintForceInfoToLogfile()

void printerror(ostream& whereto, int errID){
	
	if(errID==1)
		whereto << "imax and/or jmax not chosen sensibly" << endl;
	if(errID==2)
		whereto << "time-step size bigger than space step-size" << endl;
	whereto << "terminating" << endl;
	whereto << endl;
	
} // END printerror()