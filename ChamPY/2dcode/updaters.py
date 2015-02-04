# updaters.py

import computers as comp

def update_gradientflow(phi_current, eom, ht):
    
    # Function to return field value updated via gradient flow algorithm
    
    return eom * ht + phi_current
    
    
    
def run_update(phi_current, phi_new, rho, (h,ht,ev_min,ev_max), potparams):
    
    # Function designed to run over all space and update the value of the 
    # field according to a gradient flow algorithm; finite difference 
    # derivatives are used.
    
    # Zero the integrated error
    error = 0.0
    
    # Zero the integrated energy
    energy = 0.0
    
    # Compute h2 = h * h
    h2 = h * h
    
    # Begin run over space
    for i in xrange(ev_min[0], ev_max[0]):
        for j in xrange(ev_min[1],ev_max[1]):
            
            # Extract the value of phi at this location
            phi_here = phi_current[i][j]
            
            # Extract the value of rho at this location
            rho_here = rho[i][j]
            
            ###### ------- ###### ------- ######
            #   
            #   Updater
            #
            ###### ------- ###### ------- ######
            
            # Obtain the Laplacian
            lap = comp.computelap(phi_current,(i,j),h2)
            
            # Obtain dV/dphi
            dpot = comp.computedpot(phi_here, rho_here, potparams)
            
            # Obtain E = nabla^2phi - dV/dphi
            eom = comp.computeeom(lap,dpot)
            
            # Update phi at this location using gradient flow
            phi_new[i][j] = update_gradientflow(phi_here, eom, ht) 
            
            ###### ------- ###### ------- ######
            #   
            #   Energy calculation
            #
            ###### ------- ###### ------- ######
            
            # Get the gradient of the field at this location
            (fx, fy) = comp.compute_grad( phi_current, (i,j) , h )
            
            # Get the potential energy of the field at this location
            pot = comp.computepot( phi_here, rho_here, potparams )
            
            # Get the energy density at this location
            energydensity = comp.compute_energy_density((fx, fy), pot)
            
            # Compute the error on this configuration
            error = error + eom 
            
            # Compute energy
            energy = energy + energydensity 
    
    # Return the new value of phi, the error, and the energy density
    return (phi_new, error * h2, energy * h2)
    
    