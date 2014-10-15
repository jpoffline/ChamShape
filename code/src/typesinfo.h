/*

	function to print types info
	... boundary conditions (fixed, periodic, etc)
	... initial conditions (random, idealised, etc)
	... equation of motion (damped, gradient flow, etc)

*/



void printinfo(string type, int option){
	
	// Setup identifiers to use in switches
	int typeID;
	
	if(type == "InitialConditions")
		typeID = 1;
	if(type=="Potential")
		typeID = 3;
	cout << type << " = " << option << " :: ";
	
	switch(typeID){
		 
		case 1:
			switch(option){
				case 0: 
					cout << "homogeneous field" << endl;
					break;
				default:
					cout << "cant find a description for " << type << endl;
					break;
			}
			break;
		case 3:
			switch(option){
				case 1: 
					cout << "Lambda/phi" << endl;
					break;
				default:
					cout << "cant find a description for " << type << endl;
					break;
			}
			break;
		default:
			cout << "dont know what " << type << " is" << endl;
			break;
	}
	
	
}