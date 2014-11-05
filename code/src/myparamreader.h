/*

	myparamreader.h

	Treat Double, Int, Bool, String separately

*/

double getiniDouble(ifstream& inif, string namerequired, double deflt){
	
	bool notfound=true;
	string temp;
	string delim="=";
	string commlim="#";
	string names,tempval;
	
	while(!inif.eof() && notfound){

		// Dump into string array
		inif >> temp;
		if(temp.substr(0) != commlim){
			// find out where in string the delimiter is
			size_t pos = temp.find(delim);       
			// get a string from the fist part of the line to the delimiter
	 	    names = temp.substr(0,pos); 
			tempval = temp.substr(pos+1); 

			if(names==namerequired){
				// Once found, go back to the beginning of the file
				inif.clear();
				inif.seekg(0,ios::beg);
				return String2Double(tempval);
				notfound=false;
				
				break;
			}
		}
		
	}	
	
	// If not found anything
	// (1) go back to start of file	
	inif.clear();
	inif.seekg(0,ios::beg);
	// (2) return the default
	return deflt;
	
} // END getiniDouble()

int getiniInt(ifstream& inif, string namerequired, int deflt){
	
	bool notfound=true;
	string temp;
	string delim="=";
	string commlim="#";
	string names,tempval;
	
	while(!inif.eof() && notfound){

		// Dump into string array
		inif >> temp;

		if(temp.substr(0) != commlim){
			// find out where in string the delimiter is
			size_t pos = temp.find(delim);       
			// get a string from the fist part of the line to the delimiter
	 	    names = temp.substr(0,pos); 
			tempval = temp.substr(pos+1); 

			if(names==namerequired){
				// Once found, go back to the beginning of the file
				inif.clear();
				inif.seekg(0,ios::beg);
				return String2Int(tempval);
				notfound=false;
				break;
			}
		}
		
	}	

	// If not found anything
	// (1) go back to start of file	
	inif.clear();
	inif.seekg(0,ios::beg);
	// (2) return the default
	return deflt;
	
} // END getiniInt()

string getiniString(ifstream& inif, string namerequired, string deflt){
	
	bool notfound=true;
	string temp;
	string delim="=";
	string commlim="#";
	string names,tempval;
	
	while(!inif.eof() && notfound){

		// Dump into string array
		inif >> temp;
		
		if(temp.substr(0) != commlim){
			// find out where in string the delimiter is
			size_t pos = temp.find(delim);       
			// get a string from the fist part of the line to the delimiter
	 	    names = temp.substr(0,pos); 
			tempval = temp.substr(pos+1); 

			if(names==namerequired){
				// Once found, go back to the beginning of the file
				inif.clear();
				inif.seekg(0,ios::beg);
				return tempval;
				notfound=false;
				break;
			}
		}
		
	}	
	
	// If not found anything
	// (1) go back to start of file	
	inif.clear();
	inif.seekg(0,ios::beg);
	// (2) return the default
	return deflt;
	
} // END getiniString()

bool getiniBool(ifstream& inif, string namerequired, bool deflt){
	
	bool notfound=true;
	string temp;
	string delim="=";
	string commlim="#";
	string names,tempval;
	bool tempvalret;
	
	while(!inif.eof() && notfound){

		// Dump into string array
		inif >> temp;
		
		if(temp.substr(0) != commlim){
			// find out where in string the delimiter is
			size_t pos = temp.find(delim);       
			// get a string from the fist part of the line to the delimiter
	 	    names = temp.substr(0,pos); 
			tempval = temp.substr(pos+1); 

			if(names==namerequired){
				if(tempval=="true")
					tempvalret=true;
				if(tempval=="false")
					tempvalret=false;
				// Once found, go back to the beginning of the file
				inif.clear();
				inif.seekg(0,ios::beg);
				return tempvalret;
				notfound=false;
				break;
			}
		}
		
	}	
	
	// If not found anything
	// (1) go back to start of file	
	inif.clear();
	inif.seekg(0,ios::beg);
	// (2) return the default
	return deflt;
	
} // END getiniBool()