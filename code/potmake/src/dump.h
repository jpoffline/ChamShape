/*

	dump.h

*/


void dumpshapeinfo(vector<double>info, ostream& whereto){
	
	for(int c = 0; c < info.size(); c++)
		whereto << info[c] << " ";
	whereto << endl;
	
} // END dumpshapeinfo()