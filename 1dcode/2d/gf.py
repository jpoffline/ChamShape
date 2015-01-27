from math import *
import matplotlib.pyplot as plt
import numpy as np
import ic,solver,computers,printinfo,aux_funcs,writer
from params import *


def main():
    
    rho_file_suff = out_info_params[4]
    log_filename = out_info_params[10]   
    phi_final_filename = out_info_params[5]
    force_final_filename = out_info_params[6] 

    info = printinfo.print_intro(code_title, author_name, author_institution, author_date)
    info = info + printinfo.print_params(gridparams,rho_vals,potparams,units,tol,ht)
    info = info + printinfo.print_object_params(object_param_dialled_name,object_radii)
    writer.dump_info(outDIR, log_filename, info )
    
    buff = 10000
    runID = buff
    
    X = computers.getspacevect(imin,imax,h)
    Y = computers.getspacevect(jmin,jmax,h)
        
    for obj in object_params:
        
        print 'Object ' + object_param_dialled_name_singular + ' = ', obj, unit_length_screen
        
        # Setup the size parameters for this object
        obj_params = ( obj, rho_obj, rho_bg )
    
        # Setup "rho" for this given object
        rho = ic.setuprho( rho_vals, gridparams, obj_params , (runID, outDIR) , shape_type)
        
        # Dump rho to file
        writer.dump( (X,Y), rho, outDIR + str(runID) + rho_file_suff, mins, maxs )
        
        # Dump the runID into the out_info_params list
        out_info_params[ len( out_info_params ) - 1 ] = runID        
        
        # Get a solution of "phi" for this rho
        (phi, force, error) = solver.find_solution( gridparams, evparams, potparams, rho, rho_vals, tol , out_info_params )
        
        # Dump the solution (phi) and force to file
        #writer.dump( (X,Y), phi, outDIR + str(runID) + phi_final_filename, mins, maxs )
        #writer.dump( (X,Y), force, outDIR + str(runID) + force_final_filename, mins, maxs )
        
        runID = runID + 1
        
    print "DONE"    
   



main()