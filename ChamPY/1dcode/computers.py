def computelap( phi, i, h2 ):
    
    return (phi[i + 1] + phi[i - 1] - 2.0 * phi[i]) / h2    

def computepot(phi, rho, (mphi2, lam, beta, Mpl) ):
    
    return mphi2 * phi * phi / 2.0 + lam * phi * phi * phi * phi / 6.0 / 4.0 - beta * phi * rho / Mpl

def computedpot(phi, rho, (mphi2, lam, beta, Mpl) ):
    
    return mphi2 * phi + lam * phi * phi * phi / 6.0 - beta * rho / Mpl

def computeeom(lap,dpot):
    
    return lap - dpot
    
def computeforce(phi, (h, imin, imax), ( d, ht, i_ev_min, i_ev_max ) ):
    
    force = []
    
    for i in xrange(imin,imax):
        to_put = 0.0
        if i > i_ev_min and i < i_ev_max:
            to_put = (phi[i+1] - phi[i-1]) / 2.0 / h
        force.append(to_put)
    
    return force    
    
    
def computex(i,imax,h):
        return (i - 0.5 * imax) * h
        
def getspacevect(imin,imax,h):
    
    pos = []
    
    for i in xrange(imin,imax):
        pos.append( computex(i,imax,h) )

    return pos        
    

def compute_eff_length( lam, beta, Mpl, rho_obj):
    
    return (2.0/9.0)**(1.0/6.0) * beta**(-1.0/3.0) * lam**(-1.0/6.0) * (Mpl / rho_obj)**(1.0/3.0)    