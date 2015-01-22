function plotfrats(varargin)

    % plot script:
    % plots max(Fcham/Fgrav) as a function of a parameter specifying
    % the source (here, ellipse: so b/a).

    close all;
    
    name = char(varargin(1));
    rootDIR='../';
    outDIR='output/';
    plotDIR='plots/';
    forceinfofileproto='forceinfo.dat';
    
    plot_sizeunits='inches';
    plot_width=4.5;
    plot_height=3.5;
    
    datafile=strcat(rootDIR,outDIR,name,'/',forceinfofileproto);
    outfigname=strcat(rootDIR,plotDIR,name,'_frats.pdf');
    dat=load(datafile);
    
    % locations in data file
    fratpos=5;
    apos=12;
    bpos=13;
    Mpos=14;
    
    frat=dat(:,fratpos);
    a=dat(:,apos);
    b=dat(:,bpos);
    M=dat(:,Mpos);
    
    ndat=size(dat);
    nd=ndat(1);
    
    for n=1:nd
        el(n)=b(n)/a(n);
        frat(n)=frat(n)*1000-999;
    end;
    
    plot(el,frat,'k-o','MarkerFaceColor','k');
    
    xlabel('$\mbox{aspect }\mbox{ratio,}{\,}b/a$', 'interpreter','latex');
    ylabel('$\mbox{max}(F_{\rm cham}{\,} / F_{\rm grav}){\,}[\mbox{arbitrary } \mbox{units}]$', 'interpreter','latex');
    
    set(gcf, 'PaperUnits',plot_sizeunits);
    set(gcf, 'PaperSize',[plot_width plot_height]);
    set(gcf, 'PaperPosition',[ 0 0 plot_width plot_height]);
    set(gcf, 'renderer', 'painters');
    print('-dpdf',outfigname);
    
    fprintf('Plot saved to %s\n',outfigname);
    