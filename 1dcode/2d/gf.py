from math import *
import matplotlib.pyplot as plt
import numpy as np
import ic
import solver 
import computers
import printinfo
import aux_funcs
import writer
from params import *

author_name = "J. Pearson"
author_institution = "Nottingham"


def main():
    
    
    
    object_radii = (1.5,0.5,0.15,0.05)
    #object_sizes = (3.0,1.0)
    print printinfo.print_intro(author_name, author_institution)
    print printinfo.print_params(gridparams,rho_vals,potparams,units,tol)
    
    
    buff = 10000
    runID = buff
    
    X = computers.getspacevect(imin,imax,h)
    Y = computers.getspacevect(jmin,jmax,h)
    
    for obj in object_radii:
        
        print "Object radius = ",obj,unit_length_screen
        
        # Setup the size parameters for this object
        obj_params = ( obj, rho_obj, rho_bg )
    
        # Setup "rho" for this given object
        rho = ic.setuprho( rho_vals, gridparams, obj_params , (runID,outDIR) )
        
        # Dump rho to file
        writer.dump( (X,Y), rho, outDIR + str(runID) + '_rho.dat', mins, maxs )
        
        # Get a solution of "phi" for this rho
        (phi, force, error) = solver.find_solution( gridparams, evparams, potparams, rho, rho_vals, tol , (runID,outDIR) )
        
        # Dump the solution (phi) and force to file
        writer.dump( (X,Y), phi, outDIR + str(runID) + '_phi.dat', mins, maxs )
        writer.dump( (X,Y), force, outDIR + str(runID) + '_force.dat', mins, maxs )
        
        runID = runID + 1
        
    print "DONE"    
   



main()