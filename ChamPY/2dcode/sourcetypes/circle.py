
# circle.py

def isinsideobject(x,y,obj_params):
    
    circ_radius = obj_params
    
    if abs( x * x + y * y ) < circ_radius * circ_radius:
        ret = True
        which = 1
    else:
        ret = False
        which = 0    
    
    return (ret, which)    
    
    
def setup_params(rho_bg, rho_obj):    
    
    #object_radii = (3.0,1.5)
    object_radii = (3.0,1.5,0.5,0.15,0.1)
    
    rho_vals = []
    rho_vals.append(rho_bg)
    rho_vals.append(rho_obj)
    
    object_params = object_radii
    dialled_name = 'radii'
    dialled_name_singular = 'radius'    
    
    return (object_params, rho_vals, (dialled_name, dialled_name_singular))        