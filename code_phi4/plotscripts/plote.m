function plote(varargin)

    close all;

    fprintf('Plotting error estimates\n');

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
    
    plot_sizeunits='inches';
    plot_width=4.5;
    plot_height=2.5;
    outfigname = strcat(plotdir,name,'_errors.pdf'); 
    
    thDATAfile=strcat(rootdir,name,'/file_timehistory.dat');
    fprintf('timehistory file = %s\n',thDATAfile);
    thDATA=load(thDATAfile);
    t = thDATA(:,1);
    e_phi = thDATA(:,2)*1000;
    e_phiDot = thDATA(:,3);
    e_phiForce = thDATA(:,6);
    
    subplot(1,3,1);
    plot(t,e_phi);
    xlabel('time')
    ylabel('$10^3\,|E_{\phi}|$','interpreter','latex');
    subplot(1,3,2);
    plot(t,e_phiDot);
    xlabel('time')
    ylabel('$\dot{E}_{\phi}$','interpreter','latex');
    xlim([min(t)+0.01 max(t)]);
    subplot(1,3,3);
    plot(t,e_phiForce);
    xlabel('time')
    ylabel('$E_{\phi}^F$','interpreter','latex');
    
    
    set(gcf, 'PaperUnits',plot_sizeunits);
    set(gcf, 'PaperSize',[plot_width plot_height]);
    set(gcf, 'PaperPosition',[ 0 0 plot_width plot_height]);
    set(gcf, 'renderer', 'painters');
    print('-dpdf',outfigname);