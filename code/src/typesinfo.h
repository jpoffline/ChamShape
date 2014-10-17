/*

	function to print types info
	... boundary conditions (fixed, periodic, etc)
	... initial conditions (random, idealised, etc)
	... equation of motion (damped, gradient flow, etc)

*/



void printinfo(ostream& whereto, string type, int option){
	
	// Setup identifiers to use in switches
	int typeID;
	
	if(type == "InitialConditions")
		typeID = 1;
	if(type=="Potential")
		typeID = 3;
	whereto << type << " = " << option << " :: ";
	
	switch(typeID){
		 
		case 1:
			switch(option){
				case 0: 
					whereto << "homogeneous field" << endl;
					break;
				default:
					whereto << "cant find a description for " << type << endl;
					break;
			}
			break;
		case 3:
			switch(option){
				case 1: 
					whereto << "Lambda5/phi" << endl;
					break;
				default:
					whereto << "cant find a description for " << type << endl;
					break;
			}
			break;
		default:
			whereto << "dont know what " << type << " is" << endl;
			break;
	}
	
	
}