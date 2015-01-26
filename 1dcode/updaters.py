import computers as comp

def update_gradientflow(phi_current, eom, ht):
    
    return eom * ht + phi_current
    
def run_update(phi_current, phi_new, rho, (h,ht,i_ev_min,i_ev_max), potparams):
    
    error = 0.0
    h2 = h * h
    for i in xrange(i_ev_min, i_ev_max):
        phi_here = phi_current[i]
        lap = comp.computelap(phi_current,i,h2)
        dpot = comp.computedpot(phi_here, rho[i], potparams)
        eom = comp.computeeom(lap,dpot)
        phi_new[i] = update_gradientflow(phi_here, eom, ht) 
        error = error + eom * h
        
    return (phi_new, error)