// Some useful auxiliary functions

string Int2String(int Number) {
	
    return static_cast<ostringstream*>( &(ostringstream() << Number) )->str();
	
}

double String2Double(string s) {
     double d;
     stringstream ss(s); //turn the string into a stream
     ss >> d; //convert
     return d;
}

int String2Int(string s) {
     int d;
     stringstream ss(s); //turn the string into a stream
     ss >> d; //convert
     return d;
}

