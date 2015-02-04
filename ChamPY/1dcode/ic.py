import computers

def get_phi_startvals((rho_bg, rho_obj),( mphi2, lam, beta, Mpl )):
    
    if mphi2 == 0:
        phi_bg = ( 6.0 * beta * rho_bg / Mpl / lam )**(1.0/3.0)
        phi_obj = ( 6.0 * beta * rho_obj / Mpl / lam )**(1.0/3.0)
    
    return (phi_bg, phi_obj)    

def do_setup_1(x, spacing, osize, rho_o, rho_b):
    
    if abs(x-spacing) < 2.0*osize / 2.0 :
        rho_to_put = object_size*rho_o
    elif abs(x+spacing) < osize / 2.0:
        rho_to_put =  20*rho_o
    else:
        rho_to_put = rho_b


    return rho_to_put


def do_setup_2(x,(x1,x2,r1,x3,x4,r2),rho_b):
    
    if x > x1 and x < x2:
        rho_to_put = r1
    elif x > x3 and x < x4:
        rho_to_put = r2    
    else:
        rho_to_put = rho_b  
          
    return rho_to_put

def setuprho((rho_b, rho_o), (h, imin, imax), (object_size, rho_obj, rho_bg)):
    
    rho = []
    spacing = 2.5
    
    osize = 3.0
    
    obj_type = 2
    ''''
    x1 = computers.computex(0,imax,h) + 10.0
    t1 = 3.0
    s = 1.0
    fac = 1.1
    
    r1 = rho_obj
    r2 = r1 * object_size
        
    x2 = x1 + t1
    x3 = x2 + s
    t2 = t1 * r1 / r2
    x4 = x3 + t2
    while x4 > computers.computex(imax,imax,h) - 10.0:
        t2 = t2 / fac
        r2 = r2 * fac
        x4 = x3 + t2
        
    print (x1,x2), (x3, x4), (x2 - x1)*r1, (x4 - x3)*r2
    '''
    spacing = 0.5
    x1 = computers.computex(0,imax,h) + 10.0
    x2 = -1.0
    r1 = 20.0*rho_obj
    x3 = x2 + spacing
    x4 = computers.computex(imax,imax,h) - 10.0
    r2 = object_size*rho_obj
    
    for i in xrange(imin,imax):
        
        x = computers.computex(i,imax,h)
        if obj_type == 1:
            rho_to_put = do_setup_1(x, spacing, osize, rho_o, rho_bg)
        elif obj_type == 2:
            rho_to_put = do_setup_2(x,(x1,x2,r1,x3,x4,r2), rho_bg)
            
        rho.append(rho_to_put)
    
    return rho


def setupphi(rho, (x,rho_ob),(phi_b, phi_o), (h, imin, imax)):
    
    phi = []
    
    for i in xrange(imin,imax):
        if rho[i] == rho_ob:
            phi_to_put = phi_o
        else:
            phi_to_put = phi_b
                    
        phi.append(phi_to_put)
        
    return phi

