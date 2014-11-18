function plotJ
    close all;
    dataDIR = '../data2/';
    
    N = 20;
    h = 0.01;
    
    plot_fontsize = 10;
    
    for n=1:N
        ID = num2str(1000+n);
        filen = strcat(dataDIR,'run_',ID,'__J_.dat');
        data = load(filen);
        
        x = h*data(:,2);
        y = data(:,4);
        subplot(2,2,1);
        plot(x,y);
        xlabel('$\mbox{distance from surface}$','interpreter','latex','fontsize',plot_fontsize);
        ylabel('$f = F_y/F_x$','interpreter','latex','fontsize',plot_fontsize);
        box on;
        hold on;
        
        
        
        subplot(2,2,4);
        [val IDX] = max(y);
        scatter(data(1,3),h*data(IDX,2));
        xlabel('$\mbox{aspect ratio}$','interpreter','latex','fontsize',plot_fontsize);
        ylabel('$\mbox{position of max}(f)$','interpreter','latex','fontsize',plot_fontsize);
        box on;
        hold on;
        
        subplot(2,2,3);
        scatter(data(1,3),max(y));
        xlabel('\mbox{aspect ratio}','interpreter','latex','fontsize',plot_fontsize);
        ylabel('$\mbox{max}(f)$','interpreter','latex','fontsize',plot_fontsize);
        box on;
        hold on;
        
        
        subplot(2,2,2);
        [val IDX] = max(x);
        fr_max = max(data(:,4));
        fr_xmax = data(IDX,4);
        scatter(data(1,3),(fr_max-fr_xmax)/fr_max);
        hold on;
        box on;
        xlabel('$\mbox{aspect ratio}$','interpreter','latex','fontsize',plot_fontsize);
        ylabel('$\mbox{force shift}$','interpreter','latex','fontsize',plot_fontsize);
    end;
    
    plot_sizeunits='inches';
    plot_width=5.5;
    plot_height=5.5;
    outfigname = 'p2222.pdf';
    set(gcf, 'PaperUnits',plot_sizeunits);
    set(gcf, 'PaperSize',[plot_width plot_height]);
    set(gcf, 'PaperPosition',[ 0 0 plot_width plot_height]);
    set(gcf, 'renderer', 'painters');
    print('-dpdf',outfigname);
    
    
    
    