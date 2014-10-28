function plotfrats(varargin)

    name = strcat(char(varargin(1)),'/');
    rootDIR='../';
    outDIR='output/';
    forceinfofileproto='forceinfo.dat';
    
    datafile=strcat(rootDIR,outDIR,name,forceinfofileproto);
    
    dat=load(datafile);
    
    fratpos=5;
    apos=12;
    bpos=13;
    Mpos=14;
    
    frat=dat(:,fratpos);
    a=dat(:,apos);
    b=dat(:,bpos);
    M=dat(:,Mpos);
    
    ndat=size(dat);
    nd=size(1);
    
    for n=1:nd
        el=a(n)/b(n);
    end;
    
    plot(el,frat);
    xlabel('a/b');
    ylabel('max(F_{cham} / F_{grav})');
    