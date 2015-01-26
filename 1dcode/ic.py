import computers

def get_phi_startvals((rho_bg, rho_obj),( mphi2, lam, beta, Mpl )):
    
    if mphi2 == 0:
        phi_bg = ( 6.0 * beta * rho_bg / Mpl / lam )**(1.0/3.0)
        phi_obj = ( 6.0 * beta * rho_obj / Mpl / lam )**(1.0/3.0)
    
    return (phi_bg, phi_obj)    


def setuprho((rho_b, rho_o), (h, imin, imax), (object_size, rho_obj, rho_bg)):
    
    rho = []
    
    for i in xrange(imin,imax):
        
        x = computers.computex(i,imax,h)

        if abs(x) < object_size / 2.0:
            rho_to_put = rho_o
        else:
            rho_to_put = rho_b
            
        rho.append(rho_to_put)
    
    return rho


def setupphi(rho, (x,rho_ob),(phi_b, phi_o), (h, imin, imax)):
    
    phi = []
    
    for i in xrange(imin,imax):
        if rho[i] == rho_ob:
            phi_to_put = phi_o
        else:
            phi_to_put = phi_b
                    
        phi.append(phi_to_put)
        
    return phi

