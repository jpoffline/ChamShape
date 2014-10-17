/*

	Routine to read in inifile & set values of parameters

*/


double setuparams(IniReader &init){
	
	h = init.getiniDouble("h", 0.25, "Main");
	ht = init.getiniDouble("ht", 0.1, "Main");	
	ttot = init.getiniInt("ttot", 1000, "Main");		
	imax = init.getiniInt("imax", 512, "Main");		
	jmax = init.getiniInt("jmax", 512, "Main");			
	
	nreals = init.getiniInt("nreals", 1, "Main");		
	killatlx = init.getiniBool("killatlx", true, "Main");		
	ntimespastlx = init.getiniInt("ntimespastlx", 1, "Main");		
	bl = init.getiniInt("bl", 1, "Main");		
	
	eomtype = init.getiniInt("eomtype", 1, "Main");		
	tdamp = init.getiniInt("tdamp", 200, "Main");		
	damp = init.getiniDouble("damp", 5.0, "Main");
	bctype = init.getiniInt("bctype", 1, "Main");		
	pottype = init.getiniInt("pottype", 1, "Main");	
	inittype = init.getiniInt("inittype", 0, "Main");	
	
	outDIR = init.getiniString("outDIR", "data/", "Dump");		
	filePREFIX = init.getiniString("filePREFIX", "file", "Dump");	
	timehistoryproto = init.getiniString("timehistoryproto", "timehistory", "Dump");	
	screendumpfreq = init.getiniInt("screendumpfreq", 20, "Dump");	
	dumptofile = init.getiniBool("dumptofile", true, "Dump");		
	filedumpfreq = init.getiniInt("filedumpfreq", 1000, "Dump");	
	
	objdensity = init.getiniDouble("objdensity", 5.0, "Object");
	objsize = init.getiniDouble("objsize", 5.0, "Object");	
	objskindepth = init.getiniDouble("objskindepth", 5.0, "Object");	
	obj_rhobg = init.getiniDouble("obj_rhobg", 1.0, "Object");	
	mattdisttype = init.getiniInt("mattdisttype", 1, "Object");	
	elparam1 = init.getiniDouble("elparam1", 1, "Object");	
	elparam2 = init.getiniDouble("elparam2", 1, "Object");	
		
	Lambda5 = init.getiniDouble("Lambda5", 5.0, "ChamModel");	
	M = init.getiniDouble("M", 5.0, "ChamModel");	
	phi_bg = init.getiniDouble("phi_bg", 5.0, "ChamModel");	
		
	return 1.0;
	
} // END setuparams()