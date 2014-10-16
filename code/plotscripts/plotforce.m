function plotforce()
    close all;
    root='../';
    plotfile='plot.pdf';
    ndat=1;
    ID{ndat} = '2'; ndat=ndat+1;
    ID{ndat} = '5'; ndat=ndat+1;
    ID{ndat} = '10'; ndat=ndat+1;
    ID{ndat} = '20'; ndat=ndat+1;
    
    plot_sizeunits='inches';
    plot_width=8.5;
    plot_height=3.5;
    for dat=1:ndat-1
        leglab{dat}=strcat('R = ',ID{dat});
    end;
    
    
    plotxmax=25;
    plotxmin=0;
    fnp='file_x_final.dat';
    cols={'r','b','k','m'};
    leglabs={leglab{1},leglab{2},leglab{3},leglab{4}};
    for dat=1:ndat-1
        df=strcat(root,'R',ID{dat},'/',fnp);
        data=load(df);
        x=data(:,1);
        R=str2num(ID{dat});
        x=x-R;
        phi=data(:,2);
        fphi=log10(data(:,5));
        maxFORCE=max(fphi);
        hold on;
        subplot(1,2,1);
        pl1{dat}=plot(x,fphi,'color',cols{dat});
        xlim([plotxmin plotxmax]);
        xlabel('$x-R$','interpreter','latex');
        ylabel('$\log{\,}_{\,10}{\,} F_{(\rm cham)}{\,\,\,\,}$','interpreter','latex');
        hold on;
        subplot(1,2,2);
        x=x+R;
        plot(x,phi,'color',cols{dat});
        xlim([plotxmin plotxmax]);
        xlabel('$x$','interpreter','latex');
        ylabel('$\phi$','interpreter','latex');
        
        fprintf('R = %s, Fmax = %f\n',ID{dat},10^maxFORCE);
        
    end;  
    
    L = legend([leglabs]);
    hold off;
    set(L,'location','southeast');
    legend boxoff;
    
    set(gcf, 'PaperUnits',plot_sizeunits);
    set(gcf, 'PaperSize',[plot_width plot_height]);
    set(gcf, 'PaperPosition',[ 0 0 plot_width plot_height]);
    set(gcf, 'renderer', 'painters');
    print('-dpdf',plotfile);
    
   