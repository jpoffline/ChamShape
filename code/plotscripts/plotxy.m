function plotxy(varargin)

    %
    %   Useage example:
    %       plotxy('run1','final','force')
    %

    close all;
    
    % where is the root of all output files?
    rootdir='../output/';
    % where will the plots go?
    plotdir = '../plots';
    % check plots directory exists, and if not: make it
    if ~exist(plotdir,'dir')
        mkdir(plotdir);
    end;
    % add on a slash to the plotdir name
    plotdir=strcat(plotdir,'/');
    
    % pull off of input the "name"... folder name for run
    name = char(varargin(1));
    % which file do we want? usually "final"
    which = char(varargin(2));
    % what type of thing to plot? force or cham
    whichID = char(varargin(3));
    
    plot_sizeunits='inches';
    plot_width=4.5;
    plot_height=3.5;
    outfigname = strcat(plotdir,name,'_fxy_',whichID,'_',which,'.pdf'); 
    
    datafx=strcat(rootdir,name,'/file','_x_',which,'.dat');
    datafy=strcat(rootdir,name,'/file','_y_',which,'.dat'); 
    datx = load(datafx);
    daty = load(datafy);
    x = datx(:,1);
    y = daty(:,1);
    axlim=max(x);
    if strcmp(whichID,'cham')
        ID = 2;
    end;
    
    if strcmp(whichID,'force')
        ID = 5;
    end;
    
    if strcmp(whichID,'phierr')
        ID = 7;
    end;
    
    ylab = whichID;
    
    fx = datx(:,ID);
    fy = daty(:,ID);
    
    plot(x,fx,y,fy);
    xlim([0 axlim]);
    xlabel('distance');
    ylabel(ylab);
    legend('F(x, y = 0)','F(x = 0, y)');
    legend boxoff;
    
    set(gcf, 'PaperUnits',plot_sizeunits);
    set(gcf, 'PaperSize',[plot_width plot_height]);
    set(gcf, 'PaperPosition',[ 0 0 plot_width plot_height]);
    set(gcf, 'renderer', 'painters');
    print('-dpdf',outfigname);
    