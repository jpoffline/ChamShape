function makesurf(varargin)

    close all;
    name = char(varargin(1));
    whichID = char(varargin(2));
    
    plot_sizeunits='inches';
    plot_width=4.5;
    plot_height=3.5;
    axlim=20;
    
    DIR='../';
    infilename = strcat(DIR,name,'/file_',whichID,'.dat');
    inputdata = load(infilename);
    
    x = inputdata(:,1);
    y = inputdata(:,2);
    xmin=min(x);
    xmax=max(x);
    ymin=xmin;
    ymax=xmax;
    
    ID = 6;
    F = inputdata(:,ID);
    if ID==8
        F = log10(abs(inputdata(:,ID)));
    end;
    outfigname = strcat(name,'_',whichID,'.pdf'); 
    
    xlin = linspace(xmin, xmax, 1000);
    ylin = linspace(ymin, ymax, 1000);
    [X,Y] = meshgrid(xlin,ylin);

    Z = griddata(x,y,F,X,Y,'cubic');
    imagesc(xlin, ylin,Z);
    cb = colorbar;
    ylabel(cb, 'force density');
    colormap Hot;
    shading interp;
    xlabel('x');
    ylabel('y');
    
    xlim([-axlim axlim]);
    ylim([-axlim axlim]);
    caxis([0.5*max(F) max(F)])
    box on;
    
    
    set(gcf, 'PaperUnits',plot_sizeunits);
    set(gcf, 'PaperSize',[plot_width plot_height]);
    set(gcf, 'PaperPosition',[ 0 0 plot_width plot_height]);
    set(gcf, 'renderer', 'painters');
    print('-dpdf',outfigname);