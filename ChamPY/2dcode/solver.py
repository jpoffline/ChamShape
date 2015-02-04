# solver.py
import time
import ic
import updaters as up
import computers
import writer

def find_solution(gridparams,evparams,potparams,rho,rho_vals,tol,out_infos):

    phi_new = ic.setupphi(rho, rho_vals, gridparams,potparams)
    phi_old = phi_new
    
    # Extract useful quantities out of the out_infos list
    outDIR = out_infos[0]
    thist_screen_freq = out_infos[1]
    field_dump_freq = out_infos[2]
    thist_file_freq = out_infos[3]
    thist_file_suffix = out_infos[7]
    uptodate_phi_file_suffix = out_infos[8]
    uptodate_force_file_suffix = out_infos[9]
    
    runID = str( out_infos[ len(out_infos) - 1 ] )
    
    # Construct filename for the time-history file
    thist_filename = outDIR + runID + thist_file_suffix
    
    # Create a file for the time-history to write to
    writer.open_thist(thist_filename)
    
    # Zero the loop number
    loop = 0
    
    # initiate counter for the error
    error = 0.0
    error_old = error
    energy = 0.0
    energy_old = energy
    # How many loops to do before checking if the error is small enough?
    settle = 10
    
    # Get vectors which correspond to the physical lengths of the box
    X = computers.getspacevect(gridparams[1][0],gridparams[2][0], gridparams[0] )
    Y = computers.getspacevect(gridparams[1][0],gridparams[2][0], gridparams[0] )
    
    # Extract the time step-size
    ht = evparams[1]
        
    # Keep going with gradient flow until a solution has been found
    while True:
        
        ###### ------- ###### ------- ######
        #   
        #   Update phi
        #
        ###### ------- ###### ------- ######
        energy_old = energy
        error_old = error
        
        # Update the value of the scalar, and get a measure of the error on the "solution"
        (phi_new, error, energy) = up.run_update( phi_old, phi_new, rho, evparams, potparams )
        
        energy_change = ( energy - energy_old ) / ht
        
        ###### ------- ###### ------- ######
        #   
        #   Dumpers
        #
        ###### ------- ###### ------- ######  
              
        # Check to see if various quantities need outputting this loop
        # (1) dump timehistory 
        if loop % thist_screen_freq == 0:
            
            # Initiate a list containing time-history items
            thist_items = []
            
            # Construct timehistory items
            thist_items.append( loop )
            thist_items.append( loop * ht )
            thist_items.append( error )
            thist_items.append( ( error - error_old ) / ht )
            thist_items.append( energy )
            thist_items.append( energy_change )
            
            # Dump timehistory to file,
            writer.dump_thist( thist_items, ( 'file' , thist_filename ) )
            
            # ... then to screen
            writer.dump_thist( thist_items, ['screen'] )
        
        # (2) dump fields & forces to file
        if loop % field_dump_freq == 0:
            # First dump phi
            writer.dump( (X,Y), phi_new, outDIR +  runID + uptodate_phi_file_suffix, gridparams[1], gridparams[2] )
            
            # Compute the force
            force = computers.computeforce(phi_new, gridparams, evparams)
            
            # Now dump the force
            writer.dump( (X,Y), force, outDIR + runID + uptodate_force_file_suffix, gridparams[1], gridparams[2] )
        
      
        ###### ------- ###### ------- ######
        #   
        #   Finals this loop
        #
        ###### ------- ###### ------- ######    
            
        # Increment loop number
        loop = loop + 1
        
        # The "old"-phi value is set to be the "new"-phi value        
        phi_old = phi_new
        
        # Decide whether or not to kill this solving loop
        if loop > settle and abs(energy_change) < tol:
            break
    
    # Compute the force corresponding to this solution            
    force = computers.computeforce(phi_new, gridparams, evparams)

      
    # Return the phi, force, error, and energy back
    return (phi_new, force, error, energy)
    
    
    
    