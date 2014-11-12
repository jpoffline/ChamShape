function quickpoisssolve
    close all;
    
    imax = 300;
    jmax = 300;
    h = 0.1;
    outfigname='plot.pdf';
    loops = 1000;
    sfreq = 100;
    bl = 1;
    
    elparam1 = 3.0;
    elparam2 = 1.0;
    rho_ob = 1.0;
    rho_bg = 0.0;
    
    jminb=1+bl;
    jmaxb=jmax-bl;
    iminb=1+bl;
    imaxb=imax-bl;
    h2=h*h;
    
    if elparam1>elparam2
        biggest=elparam1;
    else
        biggest=elparam2;
    end;
    %biggest=2*biggest;
    biggest=imax*h/2;
    
    BoxEPARAM_1 = 4.0*elparam1;
    BoxEPARAM_2 = BoxEPARAM_1;
    
    % setup initial configuration
    for loop=1:2
        tt=1+mod(loop,2); 
        tp=tt-1;
        if tt==1
            tp=2;
        end;
        for i=1:imax
            x = (i-0.5*imax)*h;
            xl(i)=x;
            for j=1:jmax
                y = (j-0.5*jmax)*h;
                yl(j)=y;
                if (abs(x) < elparam1*sqrt(1.0-y*y/elparam2/elparam2))
                    rho(i,j)=rho_ob;
                else
                    rho(i,j)=rho_bg;
                end;
                
                Phi(tp,i,j)=0.0;
                Phi(tt,i,j)=0.0;
                
            end;
        end;
    end;
    
    xlin = linspace(min(xl), max(xl), imax);
    ylin = linspace(min(yl), max(yl), jmax);
    [X,Y] = meshgrid(xlin,ylin);

    Z = griddata(xl,yl,rho,X,Y,'cubic');
    imagesc(xlin, ylin,Z);
    SoR=2.0/(1.0+pi/imax);
    %SoR = 1.0;
    maxFx = 0.0;
    maxFx_x = 0.0;
    maxFx_y = 0.0;
    maxFy = 0.0;
    maxFy_x = 0.0;
    maxFy_y = 0.0;
    for loop=1:loops
        tt=1+mod(loop,2); 
        tp=tt-1;
        if tt==1
            tp=2;
        end;
       
        error=0.0;
        for i=iminb:imaxb
            ip=i+1;
            im=i-1;
            x=(i-0.5*imax)*h;
            
            for j=jminb:jmaxb
                jp=j+1;
                jm=j-1;
                y=(j-0.5*jmax)*h;
                
                eom=-rho(i,j)*0.5;
                Phi_im=Phi(tp,im,j);
                Phi_ip=Phi(tt,ip,j);
                Phi_jm=Phi(tp,i,jm);
                Phi_jp=Phi(tt,i,jp);
               
                Phi(tp,i,j)=(1.0-SoR)*Phi(tt,i,j)+SoR*0.25*(Phi_ip+Phi_im+Phi_jp+Phi_jm-h2*eom);
                
                lap=(Phi(tt,ip,j)+Phi(tt,im,j)+Phi(tt,i,jp)+Phi(tt,i,jm)-4.0*Phi(tt,i,j))/h2;
                error=error+abs(lap-eom)*h2;
                if loop==loops
                    dfdx=(Phi(tt,ip,j)-Phi(tt,im,j))/(2*h);
                    dfdy=(Phi(tt,i,jp)-Phi(tt,i,jm))/(2*h);
                    force(i,j)=sqrt(dfdx*dfdx+dfdy*dfdy);
                    errdensity(i,j)=log10(abs(lap-eom));
                    if y==0
                        if force(i,j)>maxFx
                            maxFx = force(i,j);
                            maxFx_x = x;
                            maxFx_y = y;
                        end;
                    end;
                    if x==0
                        if force(i,j)>maxFy
                            maxFy = force(i,j);
                            maxFy_x = x;
                            maxFy_y = y;
                        end;
                    end;
                end;
            end;
        end;
        if mod(loop,sfreq)==0
            fprintf('Loop: %i, error: %f\n ',loop, error);
        end;
    end;
    
    % Fill in lines for plotting the force
    for i=1:iminb
        for j=jminb:jmaxb
            force(i,j)=force(iminb+1,j);
            force(j,i)=force(j,iminb+1);
            errdensity(i,j)=errdensity(iminb+1,j);
            errdensity(j,i)=errdensity(j,iminb+1);
        end;
    end;
    for i=imaxb:imax
        for j=jminb:jmaxb
            force(i,j)=force(imaxb-1,j);
            force(j,i)=force(j,imaxb-1);
            errdensity(i,j)=errdensity(imaxb-1,j);
            errdensity(j,i)=errdensity(j,imaxb-1);
        end;
    end;
    
    close all;
    fprintf('Plotting\n');
    for i=1:imax
        xlb(i)=(i-0.5*imax)*h;
        ylb(i)=(i-0.5*jmax)*h;
        for j=1:jmax
            PhiPlot(i,j)=Phi(1,i,j);
        end;
    end;
    
    nxlb=size(xlb);
    xlin = linspace(min(xl), max(xl), imax);
    ylin = linspace(min(yl), max(yl), jmax);
    [X,Y] = meshgrid(xlin,ylin);
    
    subplot(2,2,1);
    Z = griddata(xl,yl,PhiPlot,X,Y,'cubic');
    imagesc(xlin, ylin,Z);
    xlim([-biggest biggest]);
    ylim([-biggest biggest]);
    cb = colorbar;
    ylabel(cb, '\Phi');
    
    subplot(2,2,2);
    Z = griddata(xl,yl,force,X,Y,'cubic');
    imagesc(xlin, ylin,Z);
    xlim([-biggest biggest]);
    ylim([-biggest biggest]);
    cb = colorbar;
    ylabel(cb, '|F|');
    
    subplot(2,2,3);
    plot(xlb,PhiPlot(imax/2,:), xlb,PhiPlot(:,jmax/2));
    xlim([0 biggest]);
    
    subplot(2,2,4);
    plot(xlb,force(imax/2,:), xlb,force(:,jmax/2));
    xlim([0 biggest]);
    %maxFx = max(force(:,jmax/2));
    %maxFy = max(force(imax/2,:));
    fprintf('maxF(x) = %f, maxF(y) = %f\n',maxFx,maxFy);
    fprintf('(%f, %f), (%f, %f)\n',maxFx_x, maxFx_y,maxFy_x, maxFy_y);
    
    plot_sizeunits='inches';
    plot_width=8.5;
    plot_height=8.5;
    set(gcf, 'PaperUnits',plot_sizeunits);
    set(gcf, 'PaperSize',[plot_width plot_height]);
    set(gcf, 'PaperPosition',[ 0 0 plot_width plot_height]);
    set(gcf, 'renderer', 'painters');
    print('-dpdf',outfigname);
    