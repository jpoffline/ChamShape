function compf(varargin)

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
    
    xory = char(varargin(3));
    
    plot_sizeunits='inches';
    plot_width=5.5;
    plot_height=2.5;
    outfigname = strcat(plotdir,name,'_fcomp_',xory,'_',which,'.pdf'); 
    
    datafx=strcat(rootdir,name,'/file','_',xory,'_',which,'.dat');
    datx = load(datafx);
    
    x = datx(:,1);
    
    axlim=max(x);
    scale=1000;
    
     
    
    
    fcham = datx(:,5);
    fgrav = datx(:,6)/scale;
    
    nfss=size(fcham);
    nf=nfss(1);
    for i=1:nf
        frats(i) = fcham(i)/fgrav(i);
    end;
    
    fchamMAX=max(fcham);
    fgravMAX=max(fgrav);
    
    np1=1;
    np2=2;
    pid=1;
    fprintf('fchamMAX = %f\nfgravMAX = %f\n', fchamMAX,fgravMAX);
    
    subplot(np1,np2,pid);pid=pid+1;
    plot(x,fcham,'k',x,fgrav,'r--');
    xlim([0 axlim]);
    xlabel(xory);
    ylabel('forces');
    legend('cham','grav');
    legend boxoff;
    
    subplot(np1,np2,pid);
    plot(x,frats,'k');
    xlim([0 axlim]);
    xlabel(xory);
    ylabel('F_{cham} / F_{grav}');
    
    set(gcf, 'PaperUnits',plot_sizeunits);
    set(gcf, 'PaperSize',[plot_width plot_height]);
    set(gcf, 'PaperPosition',[ 0 0 plot_width plot_height]);
    set(gcf, 'renderer', 'painters');
    print('-dpdf',outfigname);