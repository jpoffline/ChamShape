

def setup_params(rho_bg, rho_obj):
    
    object_params = []
    for i in xrange(0,len(object_radii)):
        object_params.append((object_radii[0],object_radii[i]))
        
    dialled_name = 'side lengths'
    
    dialled_name_singular = 'side length'

    rho_vals = []
    rho_vals.append(rho_bg)
    rho_vals.append(rho_obj)

    return (object_params, rho_vals, (dialled_name, dialled_name_singular))    
    
        

def isinsideobject(x,y,obj_params):

    # Function to determine whether or not a given spatial location
    # is within the source object.
    # Returns True if inside; also, "which" is returned to specify
    # which of the sources the grid-point is inside     
    rect_half_width = obj_params[0]
    rect_half_height = obj_params[1]
    
    if abs(x) < rect_half_width and abs(y) < rect_half_height:
        ret = True    
        which = 1
    else:
        ret = False
        which = 0
    
    return (ret, which)    
   