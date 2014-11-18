function t
    close all;
    
    theta = 0:0.01:2*pi;
    
     
    coeff(1) = 0.3482169;
    coeff(2) = 0.0969634;
    coeff(3) = -0.0450812;
    coeff(4) = 0.0346095;
    coeff(5) = -0.0304927;
    coeff(6) = 0.0276200;
    coeff(7) = -0.0245809;
    coeff(8) = 0.0209728;
    coeff(9) = -0.0168116;
    coeff(10) = 0.0123419;
    coeff(11) = -0.0079524;
    coeff(12) = 0.0041198;
    coeff(13) = -0.0013419;
   
    %{
    lmax = 10;
    for n=1:lmax
        sign = 1.0;
        if rand < 0.5
            %sign = - sign;
        end;
        coeff(n) = sign * rand;
    end;
    %}
    lmax = size(coeff);
    lmax = lmax(2);
    rho = 0.0;
    for l=1:lmax
        rhoD = coeff(l) * legendre(l-1,cos(theta));
        rho = rho + rhoD(1,:);
    end;
    
    figure;
    polar(theta,rho,'--r');
    
    