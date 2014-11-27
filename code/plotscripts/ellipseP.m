function ellipseP

    close all;

    dataDIR = '../output/ellipse/';
    rundata = 'file_final.dat';
    xdata = 'file_x_final.dat';
    ydata = 'file_y_final.dat';
    
    h = 0.01;
    e1 = 2.0;
    e2 = 0.4;
    
    np_xsurf = e1/h;
    np_ysurf = e2/h;
    
    %datarun = load(strcat(dataDIR,rundata));
    datax = load(strcat(dataDIR,xdata));
    datay = load(strcat(dataDIR,ydata));
    
    ss = size(datax);
    s = ss(1);
    for n = 1:s/2
        x(n) = datax(n+s/2,1)-2;
        fx(n) = datax(n+s/2,2);
        Fx(n) = datax(n+s/2,4);
    
        y(n) = datay(n+s/2,1)+1.6-2;
        fy(n) = datay(n+s/2,2);
        Fy(n) = datay(n+s/2,4);
    end;
    
    sss=size(Fy)
    np_ysurf;
    for n=1:2.5*np_ysurf
        xx(n) = n * h;
        Fxx(n) = Fx(np_xsurf+n);
        Fyy(n) = Fy(np_ysurf+n);
        rat(n) = Fyy(n) / Fxx(n);
    end;
    
    subplot(1,3,1);
    plot(xx,Fxx,xx,Fyy);
    
    subplot(1,3,2);
    plot(xx,rat);
    
    subplot(1,3,3);
    plot(x,Fx,y,Fy);
    
    
    