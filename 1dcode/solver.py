import ic
import updaters as up
import computers

def find_solution(gridparams,evparams,potparams,rho,rho_vals,tol):
    
    phi_start_vals = ic.get_phi_startvals(rho_vals, potparams)
    phi_new = ic.setupphi(rho, rho_vals, phi_start_vals, gridparams)
    phi_old = phi_new
    
    loop = 0
    settle = 10
    while True:
        (phi_new, error) = up.run_update( phi_old, phi_new, rho, evparams, potparams )
        if loop > settle:
            if error < tol:
                break
        else:
            loop = loop + 1
            
        phi_old = phi_new

    force = computers.computeforce(phi_new, gridparams, evparams)

    
    
    return (phi_new, force, error)