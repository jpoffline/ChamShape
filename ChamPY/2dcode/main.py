
# main.py

from math import *
import matplotlib.pyplot as plt
import numpy as np
import ic,solver,computers,printinfo,aux_funcs,writer
from params import *

import messages

def driver(source_type, runsolver = True):
    
    # Setup the main properties of the source
    (object_params, rho_vals, (dialled_name,dialled_name_singular) ) = source_type.setup_params(rho_bg, rho_obj)
    
    # Setup the parameters of the simulation
    (units, potparams, (gridparams,mins, maxs), evparams, out_info_params) = param_housekeeping()
    
    # Extract useful filenames from "out_info_params"
    rho_file_suff = out_info_params[4]
    log_filename = out_info_params[10]   
    phi_final_filename = out_info_params[5]
    force_final_filename = out_info_params[6] 

    info = printinfo.print_intro(code_title, author_name, author_institution, author_date)
    info = info + printinfo.print_params(gridparams,rho_vals,potparams,units,tol,ht)
    info = info + printinfo.print_object_params(dialled_name,object_params)
    writer.dump_info(outDIR, log_filename, info )
    
    # Buffer for the file names
    buff = 10000
    
    # ID of the given run
    runID = buff
    
    # Get (X,Y)-vector
    (X, Y) = ( computers.getspacevect(imin,imax,h), computers.getspacevect(jmin,jmax,h) )

    # Get a filename for the object properties-file    
    obj_prop_filename = writer.boot_up_objfile(outDIR, obj_prop_file_name)
    
    sol_central_values_filename = writer.boot_up_objfile(outDIR, 'centralvals.dat')
    
    # Loop over all the source objects    
    for obj in object_params:
        
        print 'Object ' + dialled_name_singular + ' = ', obj, unit_length_screen, '; runID = ', runID
        
        writer.write_objfile(obj_prop_filename,obj)

        # Setup the size parameters for this object
        obj_params = ( obj, rho_obj, rho_bg )
    
        # Setup "rho" for this given object
        rho = ic.setuprho( rho_vals, gridparams, obj_params , (runID, outDIR) , source_type)
        
        # Dump rho to file
        writer.dump( (X,Y), rho, outDIR + str(runID) + rho_file_suff, mins, maxs )
        
        # Dump the runID into the out_info_params list
        out_info_params[ len( out_info_params ) - 1 ] = runID        
        
        if runsolver:
            # Get a solution of "phi" for this rho
            (phi, force, error, energy) = solver.find_solution( gridparams, evparams, potparams, rho, rho_vals, tol , out_info_params )
        
            # Dump the solution (phi) and force to file
            writer.dump( (X,Y), phi, outDIR + str( runID ) + phi_final_filename, mins, maxs )
            writer.dump( (X,Y), force, outDIR + str( runID ) + force_final_filename, mins, maxs )
        
            
            x_cen = computers.computex( int( imax / 2), imax, h )
            y_cen = computers.computex( int( jmax / 2), jmax, h )            
            phi_cen = phi[ int( imax / 2) ][ int( jmax / 2 ) ]
            for_cen = force[ int( imax / 2)][ int( jmax / 2 ) ]
            vals_cen = ( obj, x_cen, y_cen, phi_cen, for_cen, rho_obj, rho_bg )
            writer.write_tofile(sol_central_values_filename,vals_cen)
            
        # Increment the ID of the run
        runID = runID + 1
        
    print messages.MESSAGE_FINISH   
   


