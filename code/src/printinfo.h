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
	whereto << "J. Pearson (Nottingham 2014)" << endl;
	whereto << "------------------------------------------" << endl;
	whereto << endl;
	
} // END printwelcome()

// Print top matter -- mainly info about current run
void printtopmatter(ostream& whereto){
	
	whereto << endl;
	whereto << "Simulation conditions/parameters:" << endl;
	whereto << "output dir: " << outDIR << endl;	
	whereto << "(imax, jmax) = (" << imax << ", " << jmax << ")" << endl;
	whereto << "(h, ht) = (" << h << ", " << ht << ")" << endl;
	whereto << "boundary layer = " << bl << " grid-points" << endl;
	
	printinfo(whereto,"Potential",pottype);	
	printinfo(whereto,"InitialConditions",inittype);
		
	whereto << "Begin solving" << endl;
	whereto << endl;
		
} // END printtopmatter()

void printobjectproperties(ostream& whereto){
	
	whereto << endl;
	whereto << "Source object parameters:" << endl;
	whereto << "mattdisttype = " << mattdisttype;
	if(mattdisttype == 1)
		whereto << " :: spherical" <<endl;
	if(mattdisttype == 2){
		whereto << " :: ellipse " << endl;
		whereto << "(a, b) = (" << elparam1 << ", " << elparam2 << ")" << endl;
	}
	if(mattdisttype == 3){
		whereto << " :: crossed ellipses " << endl;
		whereto << "(a, b) = (" << elparam1 << ", " << elparam2 << ")" << endl;
	}
	else
		whereto << endl;
	
	whereto << "size = " << objsize << endl;
	whereto << "density = " << objdensity << endl;
	whereto << "skin depth = " << objskindepth << endl;
	whereto << "bg density = " << obj_rhobg << endl;
	whereto << "M = " << M << endl;	
	whereto << "Lambda5 = " << Lambda5 << endl;
	whereto << endl;
	
}

// Print final message
void printfinalmessage(ostream& whereto, double te){
	
	string tu="ms";
	if(te>1e3){
		te=te/1e3;
		tu="sec";
	}
	whereto << "OutDIR: " << outDIR << endl;
	whereto << endl;
	whereto << "------------------------------------------" << endl;
	whereto << "Complete in " << te << tu << endl;
	whereto << "------------------------------------------" << endl;
	whereto << endl;
	
} // END printfinalmessage()

// Print info to logfile
void printlog(string when, double v1,double v2){
	
	if(when=="start"){
		string filename = outDIR+filePREFIX+".log";
		ofstream dumplog;
		dumplog.open(filename);
		printwelcome(dumplog);
		printtopmatter(dumplog);
		printobjectproperties(dumplog);
		dumplog.close();
	}
	
	if(when=="maxFs"){
		string filename = outDIR+filePREFIX+".log";
		ofstream dumplog;
		dumplog.open(filename,ios::app);
		dumplog << endl;
		dumplog << "Max force in x-direction = " << v1 << endl;
		dumplog << "Max force in y-direction = " << v2 << endl;		
		dumplog << endl;
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

void printerror(ostream& whereto, int errID){
	
	if(errID==1)
		whereto << "imax and/or jmax not chosen sensibly" << endl;
	if(errID==2)
		whereto << "time-step size bigger than space step-size" << endl;
	whereto << "terminating" << endl;
	whereto << endl;
	
} // END printerror()