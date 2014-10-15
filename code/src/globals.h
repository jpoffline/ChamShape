


double objsize;
double skindepth;
double Lambda;
double density;
double h, ht,h2;
const int imax_arr = 1000;
const int jmax_arr = 1000;
double fld[2][imax_arr][jmax_arr];
int ip1,ip2,im1,im2,jp1,jp2,jm1,jm2;
int ttot,imax,jmax;
string filePREFIX,outDIR,timehistoryproto;
int screendumpfreq,filedumpfreq;
bool dumptofile;