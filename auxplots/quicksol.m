function quicksol
    close all;
    %syms rho(x) real;
    M = 1.0;
    Lambda5 = 1.0;
    h = 0.1;
    ht=0.05:h;
    imax = 2000;
    rho_obj = 1000;
    rho_bg = 0.001;
    tmax=5;
    phi_bg = sqrt(Lambda5*M/rho_bg)
    phi_obj = sqrt(Lambda5*M/rho_obj)
    R = 5;
    
    for i=1:imax
        r(i)=(i-1)*h;
        if r < R
            rho(i) = rho_obj;
        else
            rho(i) = rho_bg;
        end;
       
        for t=1:2
            phi(i,t)=phi_bg;
        end;
        
    end;
    
    for t=1:tmax
        tt=mod(t,2)+1;
        tp=tt+1;
        
        for i=2:imax-1
            
            eom=-Lambda5/phi(i,tt)/phi(i,tt) + rho(i)/M;
            phi(i,tp)=phi(i,tt)+ht*(2*phi(i,tt)-phi(i+1,tt)-phi(i-1,tt)+eom*h*h);
        end;
    end;
    
    plot(r,phi(:,1))