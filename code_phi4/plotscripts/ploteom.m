function ploteom(varargin)
    close all;
    
    rootdir='../';
    name = char(varargin(1));
    
    
    infilename = strcat(rootdir,name,'/file_timehistory.dat');
    inputdata = load(infilename);
    t=inputdata(:,1);
    eom=log10(abs(inputdata(:,2)));
    plot(t,eom);
    
    xlabel('time');
    ylabel('EoM');