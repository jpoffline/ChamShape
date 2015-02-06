# ic.py 

import computers

def get_phi_startvals(rhos,( mphi2, lam, beta, Mpl )):
    
    phis = []
    
    if mphi2 == 0:
        for rho in rhos:
            phis.append( ( 6.0 * beta * rho / Mpl / lam )**(1.0/3.0) )
    
    return phis   

def setuprho( rhos, (h, mins, maxs), (object_size, rho_obj, rho_bg),(runID,outDIR), shape_type ):
    
    # Function to setup the density profile of the source
    # which is doing the screening. 
    

    # Initiate array which will ultimately be returned,
    # and will contain the "rho" at a given location
    rho = []
    
    for i in xrange( mins[0], maxs[0] ):
        # Get the x-value of the current location on the grid
        x = computers.computex( i , maxs[0] , h )
        rho_dumm = []
        for j in xrange( mins[1], maxs[1] ):
            # Get the y-value of the current location on the grid
            y = computers.computex(j,maxs[1],h)        
            (inside, which) = shape_type.isinsideobject( x, y, (object_size) )
            rho_dumm.append( rhos[which] )
        rho.append( rho_dumm )    

    return rho

def setupphi(rho, rhovals, (h, mins, maxs),potparams):
    
    
    phis = get_phi_startvals(rhovals, potparams)
    
    phi = []
    rho_ob = rhovals[1]
    
    for i in xrange(mins[0],maxs[0]):
        phi_dumm = []
        for j in xrange(mins[1],maxs[1]):
            
            for p in xrange(0, len(phis)):
                if rho[i][j] == rhovals[p]:
                    phi_to_put = phis[p]              
            
            phi_dumm.append(phi_to_put)
        phi.append(phi_dumm)    
        
    return phi

