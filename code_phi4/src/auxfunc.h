
/*

	Some useful auxiliary functions

*/

void checkdirexists(ostream& whereto, string dir){
	struct stat st;
	if(stat(dir.c_str(),&st) == 0)
	    whereto << "> output directory exists" << endl;
	else{
		whereto << endl;
		whereto << "--> creating output directory" << endl;
		string str = "mkdir " + dir;
		system(str.c_str());
	}
} // END mycheckdir()




// Function to return uniform random number on unit interval
double unitrand(){
	
	return rand()/(double)RAND_MAX;
	
} // END unitrand()


/// converting between types

string Int2String(int Number) {
	
    return static_cast<ostringstream*>( &(ostringstream() << Number) )->str();
	
} // END Int2String()

double String2Double(string s) {
     
	 double d;
     stringstream ss(s); //turn the string into a stream
     ss >> d; //convert
     return d;
	 
} // END String2Double()

int String2Int(string s) {
     
	 int d;
     stringstream ss(s); //turn the string into a stream
     ss >> d; //convert
     return d;
	 
} // END String2Int()

