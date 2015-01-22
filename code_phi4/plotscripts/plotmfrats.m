function plotmfrats(varargin)

    % plot script:
    % plots max(Fcham/Fgrav) as a function of a parameter specifying
    % the source (here, ellipse: so b/a).
    % useage:
    % plotmfrats('data1','data2',...,'legendtitle1','legendtitle2',...)
    
    close all;
    
    nins=size(varargin);
    nin=nins(2)/2;
    for i=1:nin
        name{i} = char(varargin(i));
        legs{i} = char(varargin(nin+i));
    end;
    
    % locations in data file
    fratpos=5;
    apos=12;
    bpos=13;
    Mpos=14;
    
    
    rootDIR='../';
    outDIR='output/';
    plotDIR='plots/';
    forceinfofileproto='forceinfo.dat';
    
    plot_sizeunits='inches';
    plot_width=4.5;
    plot_height=3.5;
    
    cols={'k','b','r'};
    maks={'-ks','--bo','-r^'};
    
    outfigname=strcat(rootDIR,plotDIR,'many_frats.pdf');
    maxrat=0.0;
    for np=1:nin
        
        datafile=strcat(rootDIR,outDIR,name{np},'/',forceinfofileproto);
        dat=load(datafile);
        frat=dat(:,fratpos);
        a=dat(:,apos);
        b=dat(:,bpos);
        M=dat(:,Mpos);

        ndat=size(dat);
        nd=ndat(1);

        for n=1:nd
            el(n)=b(n)/a(n)/M(n);
            if frat(n) > maxrat
                maxrat=frat(n);
            end;
        end;

        plot(el,frat/maxrat*1000-999,maks{np},'MarkerFaceColor',cols{np});
        hold on;
        xlabel('$\mbox{aspect }\mbox{ratio,}{\,}b/a$', 'interpreter','latex');
        ylabel('$\mbox{max}(F_{\rm cham}{\,} / F_{\rm grav}){\,}[\mbox{arbitrary } \mbox{units}; \mbox{exaggerated}]$', 'interpreter','latex');
        
        fprintf('%s :: diff = %f%%\n',legs{np},100*(max(frat)-min(frat))/max(frat));
        
    end;
    
    legend(legs)
    legend boxoff;
    
    set(gcf, 'PaperUnits',plot_sizeunits);
    set(gcf, 'PaperSize',[plot_width plot_height]);
    set(gcf, 'PaperPosition',[ 0 0 plot_width plot_height]);
    set(gcf, 'renderer', 'painters');
    print('-dpdf',outfigname);
    
    fprintf('Plot saved to %s\n',outfigname);
    