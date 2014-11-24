/*

	setupparams.h

*/


void setuparams(string paramFileName, struct GRID& box, struct BOOKKEEPING& strs, struct OBJECT& object, struct RUNPARAMS& run){

	ifstream paramsfile;
	// Read in the parameter file

	paramsfile.open(paramFileName);
	
	box.h = getiniDouble(paramsfile,"h", 0.25);
	box.imax = getiniInt(paramsfile,"imax", 1000);
	box.jmax = getiniInt(paramsfile,"jmax", 1000);
	box.di = getiniInt(paramsfile,"di", 100);
	object.type = getiniString(paramsfile,"objecttype","ellipse");
	object.type2 = getiniString(paramsfile,"type2","apple");
	object.mass = getiniDouble(paramsfile,"mass", 1.0);
	object.measureshift = getiniDouble(paramsfile,"measureshift", 4.0);
	strs.outDIR = getiniString(paramsfile,"outDIR","data/");
	strs.mainID = getiniString(paramsfile,"mainID","run");
	run.nshapes = getiniInt(paramsfile,"nshapes", 10);
	run.dumpdownaxes = getiniBool(paramsfile,"dumpdownaxes",false);
	run.dumpatpoints = getiniBool(paramsfile,"dumpatpoints",false);
	run.dumpplane = getiniBool(paramsfile,"dumpplane",false);
	run.dumpobszone = getiniBool(paramsfile,"dumpobszone",false);
	run.RunAxesRatiosSquash = getiniBool(paramsfile,"RunAxesRatiosSquash",false);
	run.maxratio = getiniDouble(paramsfile,"maxratio", 8.0);
	run.obsrad = getiniDouble(paramsfile,"obsrad", 2.0);
	// Setup defaults for the suffices of various file types
	
	strs.fileSUFFIX = ".dat";
	strs.icsPROTO = "partpos";
	strs.filexPROTO = "fx";
	strs.fileyPROTO = "fy";
	strs.filepPROTO = "fp";
	
	strs.ratiosPROTO = "ratios";
	strs.trail = 1000;
	
	paramsfile.close();
	
}