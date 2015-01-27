# computers.py

import math

def computelap( phi, i, j, h2 ):
    
    return ( phi[i + 1][j] + phi[i - 1][j] + phi[i][j + 1]  + phi[i][j - 1] - 4.0 * phi[i][j] ) / h2    

def computepot(phi, rho, (mphi2, lam, beta, Mpl) ):
    
    return mphi2 * phi * phi / 2.0 + lam * phi * phi * phi * phi / 6.0 / 4.0 - beta * phi * rho / Mpl

def computedpot(phi, rho, (mphi2, lam, beta, Mpl) ):
    
    return mphi2 * phi + lam * phi * phi * phi / 6.0 - beta * rho / Mpl

def computeeom(lap,dpot):
    
    return lap - dpot
    
def compute_grad((phi_ip, phi_im, phi_jp, phi_jm), h):
    fx = ( phi_ip - phi_im ) / 2.0 / h
    fy = ( phi_jp - phi_jm ) / 2.0 / h
    return (fx, fy)
    
def compute_energy_density(G, pot):
    
    gradient = 0.0;
    
    for i in xrange(0, len(G)):
        gradient = gradient + G[i] * G[i]
    
    return 0.5 * gradient + pot
        
    
def computeforce(phi, (h, mins, maxs), ( d, ht, ev_min, ev_max ) ):
    
    force = []

    for i in xrange(mins[0],maxs[0]):
        force_dumm = []
        for j in xrange(mins[1],maxs[1]):
            to_put = 0.0
            if i > ev_min[0] and i < ev_max[0] and j > ev_min[1] and j < ev_max[1]:
                (fx, fy) = compute_grad( (phi[i + 1][j], phi[i - 1][j], phi[i][j + 1], phi[i][j - 1]),h)
                to_put = math.sqrt( fx * fx + fy * fy )
            force_dumm.append(abs(to_put))
        force.append(force_dumm)    
        
    return force    
    
    
def computex(grid_coord,max_n_grid_points,space_step_size):
        return (grid_coord - 0.5 * max_n_grid_points) * space_step_size
        
def getspacevect(imin,imax,h):
    
    pos = []
    
    for i in xrange(imin,imax):
        pos.append( computex(i,imax,h) )

    return pos        
    

def compute_eff_length( lam, beta, Mpl, rho_obj):
    
    return (2.0/9.0)**(1.0/6.0) * beta**(-1.0/3.0) * lam**(-1.0/6.0) * (Mpl / rho_obj)**(1.0/3.0)    