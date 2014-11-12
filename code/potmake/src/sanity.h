

bool sanity(struct OBJECT object, struct GRID box){
	
	if( object.ep1 > box.xmax || object.ep2 > box.xmax )
		return false;
	else
		return true;
	
}