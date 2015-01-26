# updaters.py

import computers as comp

def update_gradientflow(phi_current, eom, ht):
    
    return eom * ht + phi_current
    
def run_update(phi_current, phi_new, rho, (h,ht,ev_min,ev_max), potparams):
    
    error = 0.0
    h2 = h * h
    for i in xrange(ev_min[0], ev_max[0]):
        for j in xrange(ev_min[1],ev_max[1]):
            phi_here = phi_current[i][j]
            lap = comp.computelap(phi_current,i,j,h2)
            dpot = comp.computedpot(phi_here, rho[i][j], potparams)
            eom = comp.computeeom(lap,dpot)
            phi_new[i][j] = update_gradientflow(phi_here, eom, ht) 
            error = error + eom * h
        
    return (phi_new, error)