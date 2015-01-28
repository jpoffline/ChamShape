# ic.py 

import computers

def get_phi_startvals((rho_bg, rho_obj),( mphi2, lam, beta, Mpl )):
    
    if mphi2 == 0:
        phi_bg = ( 6.0 * beta * rho_bg / Mpl / lam )**(1.0/3.0)
        phi_obj = ( 6.0 * beta * rho_obj / Mpl / lam )**(1.0/3.0)
    
    return (phi_bg, phi_obj)    


def isinsideobject(x,y,obj_params,shape_type):
    
    # Function to determine whether or not a given spatial location
    # is within the source object.
    
    ret = False
    
    if shape_type == 'circle':
        if abs( x * x + y * y ) < obj_params * obj_params:
            ret = True
        
    if shape_type == 'ellipse':
        if abs( ( x / obj_params[0] ) * ( x / obj_params[0] ) + ( y / obj_params[1] ) * ( y / obj_params[1] ) ) < 1.0:
            ret = True
        
    if shape_type == 'rectangle':
        if abs(x) < obj_params[0] and abs(y) < obj_params[1]:
            ret = True    
        
    return ret
                

def setuprho( (rho_b, rho_o), (h, mins, maxs), (object_size, rho_obj, rho_bg),(runID,outDIR), shape_type ):
    
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
            
            if isinsideobject( x, y, (object_size), shape_type ):
                rho_to_put = rho_o
            else:
                rho_to_put = rho_b
                
            rho_dumm.append( rho_to_put )
        rho.append( rho_dumm )    

    return rho

def setupphi(rho, rhovals, (h, mins, maxs),potparams):
    
    
    phis = get_phi_startvals(rhovals, potparams)
    
    phi = []
    rho_ob = rhovals[1]
    
    for i in xrange(mins[0],maxs[0]):
        phi_dumm = []
        for j in xrange(mins[1],maxs[1]):
            if rho[i][j] == rho_ob:
                phi_to_put = phis[1]
            else:
                phi_to_put = phis[0]                    
            phi_dumm.append(phi_to_put)
        phi.append(phi_dumm)    
        
    return phi

