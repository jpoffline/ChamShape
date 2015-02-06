    
def setup_params(rho_bg, rho_obj):
    
    
    object_radii = (3.0,1.5)
    
    rho_vals = []
    rho_vals.append(rho_bg)
    rho_vals.append(rho_obj)
    
    object_params = []
    
    for i in xrange(0,len(object_radii)):
        object_params.append((object_radii[0],object_radii[i]))
    
    dialled_name = 'radii'
    
    dialled_name_singular = 'radius'
    
    return (object_params, rho_vals, (dialled_name, dialled_name_singular))        

def isinsideobject(x,y,obj_params):

    # Function to determine whether or not a given spatial location
    # is within the source object.
    
   
    axis_x = obj_params[0]
    axis_y = obj_params[1]
    
    xt = x / axis_x
    
    yt = y / axis_y
    
    if abs( xt * xt + yt * yt ) < 1.0:
        ret = True
        which = 1 
    else:
        ret = False
        which = 0  
        
    return (ret, which)         

    
