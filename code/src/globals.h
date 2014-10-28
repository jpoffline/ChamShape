// globals.h
// All parameters here get set from params.ini

//// -------------------------------- ////
///// GRID PROPERTIES
//// -------------------------------- ////
// Note: these are used to construct the array "fld"... a user can specify smaller grid
// in params.ini... but, larger will require these to be modified to encompass the larger
// number of grid-points
const int   itot=1000;				// Number of grid-points in i-direction
const int   jtot=1000;				// Number of grid-points in j-direction
//// -------------------------------- ////
//// -------------------------------- ////


int 		imax, jmax;
const int   nflds=2;        		// Number of scalar fields in total
double  	h;         				// space step-size
double  	ht;         			// time step-size (take note of Courant stability conditions)
int     	ttot;       			// total number of time-steps (gets over-written if killatlx=true)

bool		dumptofile;				// Should we *ever* dump fields to file?
int 		filedumpfreq;			// Frequency (in t-steps) to dump to file
									// (gets reset if making a video)
int			screendumpfreq;			// Frequency (in t-steps) to dump info to screen
string 		rootoutDIR;
string 		outDIR;					// Output directory
string 		filePREFIX;				// Prefix of field/energy-files
string		timehistoryproto; 		// Prefix of time-history file

int   		nreals;				
bool 		killatlx;			
int 		ntimespastlx;		// number of times to run past lx (=1 for "physical" random ICs, =4 for percolation)
int 		eomtype; 				

int			tdamp;				// Time to stop damping			
double		damp;				// Damping magnitude

int			bctype;				
int			pottype;
int			inittype;			
int			mattdisttype;
int 		bl;
double 		Lambda5, M, phi_bg;
double 		objsize,objskindepth,objdensity, obj_rhobg;
double 		elparam1,elparam2;

/// EOF
