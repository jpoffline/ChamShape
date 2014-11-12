function plotel
    close all;
    data1 = load('../data/run_ratios.dat');
    data2 = load('../data/run2_ratios.dat');
    data3 = load('../data/run3_ratios.dat');
    data4 = load('../data/run4_ratios.dat');
    
    aspect = data1(:,6);
    aspect2 = data2(:,6);
    aspect3 = data3(:,6);
    aspect4 = data4(:,6);
    frat = data1(:,9);
    frat2 = data2(:,9);
    frat3 = data3(:,9);
    frat4 = data4(:,9);
    plot(aspect, frat,'k-');
    hold on;
    plot(aspect2,frat2,'b-');
    plot(aspect3,frat3,'r-');
    plot(aspect4,frat4,'m-');
    legend('10\Delta x','20\Delta x','40\Delta x','120\Delta x');
    legend boxoff;
    xlabel('aspect ratio');
    ylabel('force ratio');