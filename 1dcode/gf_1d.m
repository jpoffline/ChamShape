function gf_1d(varargin)


    for i = 1:imax
        
        
        
        dVdphi_eff = mphi2 * phi * lambda * phi * phi * phi / 6.0 - beta * rho;
        
        lap = phi[i+1] + phi[i-1] - 2.0 * phi[i];
        
        
        
    end;
        