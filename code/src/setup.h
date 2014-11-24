/*

	Routine to read in inifile & set values of parameters

*/

double setuparams(string paramFileName){
	
	// Obtain stream containing parameters file
	
	ifstream paramsfile;
	paramsfile.open(paramFileName);
	
	// Go read in relevant parts of the parameter file
	// Structure: getiniTYPE(PARAMstream, PARAMname, DEFAULTvalue)
	 
	h =  getiniDouble(paramsfile,"h", 0.25);
	ht = getiniDouble(paramsfile,"ht", 0.1);	
	ttot = getiniInt(paramsfile,"ttot", 1000);		
	imax = getiniInt(paramsfile,"imax", 512);		
	jmax = getiniInt(paramsfile,"jmax", 512);			
	pottype = getiniInt(paramsfile, "pottype", 1);	
	inittype = getiniInt(paramsfile, "inittype", 0);	
	bl = getiniInt(paramsfile,"bl", 1);		
	
	mattdisttype = getiniInt(paramsfile,"mattdisttype", 1);	
	obj_density =  getiniDouble(paramsfile,"obj_density", 5.0);
	obj_size = getiniDouble(paramsfile,"obj_size", 5.0);	
	obj_skindepth = getiniDouble(paramsfile,"obj_skindepth", 5.0);	
	obj_rhobg = getiniDouble(paramsfile,"obj_rhobg", 1.0);	
	
	phi_inf = getiniDouble(paramsfile,"phi_inf", 1.0);	
	phi_mass = getiniDouble(paramsfile,"phi_mass", 1.0);	
		
	elparam1 = getiniDouble(paramsfile,"elparam1", 1);	
	elparam2 = getiniDouble(paramsfile,"elparam2", 1);	
	
	Lambda5 = getiniDouble(paramsfile,"Lambda5", 5.0);	
	M = getiniDouble(paramsfile,"M", 5.0);	
	Mpl = getiniDouble(paramsfile,"Mpl", M);	
	
	rootoutDIR = getiniString(paramsfile,"rootoutDIR", "output/");		
	outDIR = getiniString(paramsfile,"outDIR", "data/");		
	screendumpfreq = getiniInt(paramsfile,"screendumpfreq", 20);	
	filePREFIX = getiniString(paramsfile,"filePREFIX", "file");	
	dumptofile = getiniBool(paramsfile,"dumptofile", true);		
	filedumpfreq = getiniInt(paramsfile,"filedumpfreq", 1000);	
	timehistoryproto = getiniString(paramsfile,"timehistoryproto", "timehistory");	
	
	derivorder = getiniInt(paramsfile,"derivorder", 4);	
	
	// Put the root dir onto the outDIR
	outDIR=rootoutDIR+outDIR;
		
	paramsfile.close();
		
	return 1.0;
	
} // END setuparams()


