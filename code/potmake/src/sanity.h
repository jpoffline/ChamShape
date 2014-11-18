

bool sanity(struct OBJECT object, struct GRID box){
	
	if( object.ep1 > box.xmax || object.ep2 > box.xmax )
		return false;
	else
		return true;
	
}

double checkFieldSanity(double input){
	
	// Routine to check whether "input"
	// is "nan" or "inf"
	
	if( input != input || isinf(input) )
		return -1.0;
	else
		return input;
	
} // END checkFieldSanity()