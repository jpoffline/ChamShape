# solver.py

import ic
import updaters as up
import computers
import writer

def find_solution(gridparams,evparams,potparams,rho,rho_vals,tol,(runID,outDIR)):
    
    thist_screen_freq = 100
    field_dump_freq = 100
    
    phi_start_vals = ic.get_phi_startvals(rho_vals, potparams)

    phi_new = ic.setupphi(rho, rho_vals, phi_start_vals, gridparams)
    
    phi_old = phi_new
    
    loop = 0
    settle = 10
    
    X = computers.getspacevect(gridparams[1][0],gridparams[2][0], gridparams[0] )
    Y = computers.getspacevect(gridparams[1][0],gridparams[2][0], gridparams[0] )
    
    
    while True:
        (phi_new, error) = up.run_update( phi_old, phi_new, rho, evparams, potparams )
        
        if loop % thist_screen_freq == 0:
            print loop, error
        
        if loop % field_dump_freq == 0:
            writer.dump( (X,Y), phi_new, outDIR + str(runID) + '_uphi.dat', gridparams[1], gridparams[2] )
            force = computers.computeforce(phi_new, gridparams, evparams)
            writer.dump( (X,Y), force, outDIR + str(runID) + '_uforce.dat', gridparams[1], gridparams[2] )
        
        loop = loop + 1
                
        phi_old = phi_new
        
        if loop > settle:
            if error < tol:
                break
                
    force = computers.computeforce(phi_new, gridparams, evparams)

    
    
    return (phi_new, force, error)