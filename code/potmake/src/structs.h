/*

	structs.h

	File to contain globally defined "struct"s

*/



struct PARTICLE{
	
	double mass;
	vector<double> location;
	
};

struct OBJECT{
	
	string type;
	string ID;
	double ep1;
	double ep2;
	double dns;
	double area;
	double mass;
	double measureshift;
	string type2;
};

struct GRID{
	
	int imax;
	int jmax;
	int di;
	double h;
	double xmax;
};

struct COORDS{
	
	vector<double> loc;
	
};

struct BOOKKEEPING{
	
	string outDIR;
	string mainID;
	string fileSUFFIX;
	string icsPROTO;
	string forcexPROTO;
	string forceyPROTO;
	string forcepPROTO;
	string ID;
	string ratiosPROTO;
	int trail;
	
};