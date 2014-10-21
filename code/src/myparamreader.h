/*

	myparamreader.h

	At the moment, the reader carries on from its previous location
	... this needs to be fixed

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
				return String2Double(tempval);
				notfound=false;
				break;
			}
		}
		
	}	
	
	// Send default back if not found anything
	return deflt;
	
}


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
				return String2Int(tempval);
				notfound=false;
				break;
			}
		}
		
	}	
	
	// Send default back if not found anything
	return deflt;
	
}

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
				return tempval;
				notfound=false;
				break;
			}
		}
		
	}	
	
	// Send default back if not found anything
	return deflt;
	
}


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
				
				return tempvalret;
				notfound=false;
				break;
			}
		}
		
	}	
	
	// Send default back if not found anything
	return deflt;
	
}