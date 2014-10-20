function plotxy(varargin)
    close all;
    
    rootdir='../';
    name = char(varargin(1));
    which = char(varargin(2));
    datafx=strcat(rootdir,name,'/file','_x_',which,'.dat');
    datafy=strcat(rootdir,name,'/file','_y_',which,'.dat'); 
    datx = load(datafx);
    daty = load(datafy);
    x = datx(:,1);
    y = daty(:,1);
    
    fx = datx(:,5);
    fy = daty(:,5);
    
    plot(x,fx,y,fy);
    xlim([0 30]);
    xlabel('x');
    ylabel('force');
    legend('F : x-dirn','F : y-dirn');
    legend boxoff;