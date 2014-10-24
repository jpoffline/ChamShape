function plotpots
    close all;
    
    B0=0;
    rhoin=10;
    rhoout=0.01;
    M=1000;
    R=5;
    rmax=5*R;
    rin=[0:0.1:R];
    rout=[R:0.1:rmax];
    nrs=size(rin);
    nr=nrs(2);
    
    plot_sizeunits='inches';
    plot_width=4.5;
    plot_height=2.5;
    outfigname = strcat('rhoin_',num2str(rhoin),'_comps.pdf'); 
    
    
    for i=1:nr
        phiIN_2D(i)=-rhoin/4/M*rin(i)*rin(i)+B0;
        phiIN_3D(i)=-rhoin/6/M*rin(i)*rin(i)+B0;
        FIN_2D(i)=rhoin/2/M*rin(i);
        FIN_3D(i)=rhoin/3/M*rin(i);
    end;
    
    nrs=size(rout);
    nr=nrs(2);
    for i=1:nr
        phiOUT_2D(i)=-rhoout/4/M*rout(i)*rout(i)+rhoout*R*R/2/M*(1-rhoin/rhoout)*log(rout(i))+B0+R*R*rhoout/4/M*(1-rhoin/rhoout)*(1-2*log(R));
        phiOUT_3D(i)=-rhoout/6/M*rout(i)*rout(i)+rhoout*R*R*R/3/M*(rhoin/rhoout-1)/rout(i)+rhoout*R*R/2/M*(1-rhoin/rhoout)+B0;
        FOUT_2D(i)=rhoout/2/M*rout(i)-rhoout*R*R/2/M*(1-rhoin/rhoout)/rout(i);
        FOUT_3D(i)=rhoout/3/M*rout(i)+rhoout*R*R*R/3/M*(rhoin/rhoout-1)/rout(i)/rout(i);
    end;
    
    subplot(1,2,1);
    plot(rin,phiIN_2D,'k',rin,phiIN_3D,'r');
    hold on;
    plot(rout,phiOUT_2D,'k',rout,phiOUT_3D,'r');
    xlim([0 rmax]);
    L=legend('2D','3D');
    set(L,'location','southwest');
    legend boxoff;
    xlabel('$r$','interpreter','latex');
    ylabel('$\mbox{gravitational potential}, \Phi(r)$','interpreter','latex');
    
    subplot(1,2,2);
    plot(rin,FIN_2D,'k',rin,FIN_3D,'r');
    hold on;
    plot(rout,FOUT_2D,'k',rout,FOUT_3D,'r');
    xlim([0 rmax]);
    xlabel('$r$','interpreter','latex');
    ylabel('$\mbox{gravitational force}, F(r)$','interpreter','latex');
    
    
    set(gcf, 'PaperUnits',plot_sizeunits);
    set(gcf, 'PaperSize',[plot_width plot_height]);
    set(gcf, 'PaperPosition',[ 0 0 plot_width plot_height]);
    set(gcf, 'renderer', 'painters');
    print('-dpdf',outfigname);
    