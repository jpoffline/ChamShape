from math import *
import matplotlib.pyplot as plt

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
    
    object_sizes = (0.05, 0.1, 0.5, 1.0, 1.5, 5.0)
#    object_sizes = [3.0]
#    object_sizes = (3.0,1.0,0.3,0.1,0.03)
    #object_sizes = (3.0,1.0)
    print printinfo.print_intro(author_name, author_institution)
    print printinfo.print_params(gridparams,rho_vals,potparams,units,tol)
    
    phis = []
    forces = []
    rhos = []
    buff = 10000
    runID = buff
    outDIR = 'out3/'
    writer.check_dir_exists(outDIR)
    
    x = computers.getspacevect(imin,imax,h)
    for obj in object_sizes:
        
        print "Object thickness = ",obj,unit_length_screen
        
        # Setup the size parameters for this object
        obj_params = ( obj, rho_obj, rho_bg )
    
        # Setup "rho" for this given object
        rho = ic.setuprho( rho_vals, gridparams, obj_params )
    
        # Get a solution of "phi" for this rho
        (phi, force, error) = solver.find_solution( gridparams, evparams, potparams, rho, rho_vals, tol )
        
        # Dump this solution into an array of solutions
        phis.append(phi)
        forces.append(force)
        rhos.append(rho)
        
        writer.dump(x,(phi, force, rho),str(runID),outDIR)
        runID = runID + 1
        
    print "DONE"    

''''
    plt.figure()
    plt.clf()
    
    # Plot the solutions
    for object_size in xrange( 0 , len(object_sizes) ):
        #x_shifted = aux_funcs.shift_x( object_sizes[object_size], x )
        
        plt.subplot(1,3,1)
       # plt.plot( x_shifted, phis[object_size])
        plt.plot( x, phis[object_size])        
        #plt.xlim([-3, 3])
        plt.xlabel( '$x$ ' + unit_length )
        plt.ylabel( '$\phi(x)\,$' + unit_phi )

        
        plt.subplot(1,3,2)
        #plt.plot( x_shifted, forces[object_size] , label=str(object_sizes[object_size])+"mm")        
        plt.plot( x, forces[object_size] , label=str(object_sizes[object_size])+"mm")                
        plt.xlim([-1, 1])
        plt.ylim([0, 5])
        plt.xlabel( '$x$ ' + unit_length )
        plt.ylabel( 'force' )
        
        plt.subplot(1,3,3)
        #plt.plot( x_shifted, forces[object_size] , label=str(object_sizes[object_size])+"mm")        
        plt.plot( x, rhos[object_size] , label=str(object_sizes[object_size])+"mm")                
        #plt.xlim([0, 3])
        plt.xlabel( '$x$ ' + unit_length )
        plt.ylabel( 'density' )
        
    leg = plt.legend()   
    leg.draw_frame(False)
    plt.show()


'''
main()