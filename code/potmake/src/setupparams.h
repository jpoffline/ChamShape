/*

	setupparams.h

*/


double setuparams(string paramFileName){

	ifstream paramsfile;
	paramsfile.open(paramFileName);
	
	h =  getiniDouble(paramsfile,"h", 0.25);
	
	
	paramsfile.close();
	
}