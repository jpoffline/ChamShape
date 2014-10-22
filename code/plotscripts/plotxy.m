function plotxy(varargin)
    close all;
    
    rootdir='../';
    name = char(varargin(1));
    which = char(varargin(2));
    whichID = char(varargin(3));
    
    
    datafx=strcat(rootdir,name,'/file','_x_',which,'.dat');
    datafy=strcat(rootdir,name,'/file','_y_',which,'.dat'); 
    datx = load(datafx);
    daty = load(datafy);
    x = datx(:,1);
    y = daty(:,1);
    
    if whichID == 'cham'
        ID = 2;
    end;
    
    if whichID == 'force'
        ID = 5;
    end;
    
    ylab = whichID;
    fx = datx(:,ID);
    fy = daty(:,ID);
    
    plot(x,fx,y,fy);
    xlim([0 30]);
    xlabel('x');
    ylabel(ylab);
    legend('F : x-dirn','F : y-dirn');
    legend boxoff;