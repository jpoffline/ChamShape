/*

	structs.h

*/



struct PARTICLE{
	double mass;
	vector<double> location;
};

struct OBJECT{
	string type;
	double ep1;
	double ep2;
	double dns;
	double area;
	double mass;
	string ID;
};

struct GRID{
	int imax;
	int jmax;
	double h;
};

struct COORDS{
	vector<double> loc;
};

struct BOOKKEEPING{
	
	string outDIR;
	string mainID;
	string fileSUFFIX;
	string icsPROTO;
	int trail;
};