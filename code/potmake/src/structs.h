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
	double area;
	double mass;
	double measureshift;
	double rmax;
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

struct RUNPARAMS{
	int nshapes;
	double obsrad;
	bool dumpdownaxes;
	bool dumpatpoints;
	bool dumpobszone;
	bool dumpplane;
	bool RunAxesRatiosSquash;
	double maxratio;
};

struct BOOKKEEPING{
	
	string outDIR;
	string mainID;
	string fileSUFFIX;
	string icsPROTO;
	string filexPROTO;
	string fileyPROTO;
	string filepPROTO;
	string ID;
	string ratiosPROTO;
	int trail;
	
};


// EOF