# ic.py 

import computers

def get_phi_startvals((rho_bg, rho_obj),( mphi2, lam, beta, Mpl )):
    
    if mphi2 == 0:
        phi_bg = ( 6.0 * beta * rho_bg / Mpl / lam )**(1.0/3.0)
        phi_obj = ( 6.0 * beta * rho_obj / Mpl / lam )**(1.0/3.0)
    
    return (phi_bg, phi_obj)    


def setuprho((rho_b, rho_o), (h, mins, maxs), (object_size, rho_obj, rho_bg),(runID,outDIR)):

    rho = []
    
    for i in xrange(mins[0],maxs[0]):
        x = computers.computex(i,maxs[0],h)
        rho_dumm = []
        for j in xrange(mins[1],maxs[1]):
            y = computers.computex(j,maxs[1],h)        
            if abs(x*x + y*y) < object_size * object_size:
                rho_to_put = rho_o
            else:
                rho_to_put = rho_b
            rho_dumm.append(rho_to_put)
        rho.append(rho_dumm)    

            
    

    return rho

def setupphi(rho, rhovals, phis, (h, mins, maxs)):
    
    phi = []
    rho_ob = rhovals[1]
    
    for i in xrange(mins[0],maxs[0]):
        phi_dumm = []
        for j in xrange(mins[1],maxs[1]):
            if rho[i][j] == rho_ob:
                phi_to_put = phis[1]
            else:
                phi_to_put = phis[0]                    
            phi_dumm.append(phi_to_put)
        phi.append(phi_dumm)    
        
    return phi

