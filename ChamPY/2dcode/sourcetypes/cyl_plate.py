
def setup_params(rho_bg, rho_obj):
    
    plate_thicknesses = (1.0, 1.0)
    cylinder_radii = (1.0, 1.0)
    separations = (0.3,1.0, 1.1)
    rho_cyl = rho_obj

    object_params = (plate_thicknesses, cylinder_radii, separations)
    object_params = []
    for i in xrange(0, len(plate_thicknesses)):
        object_params.append((plate_thicknesses[i], cylinder_radii[i], separations[i]))  
    dialled_name = 'lengths'
    dialled_name_singular = '(plate thickness, cylinder radius, separation)'
    
    
    rho_vals = []
    rho_vals.append(rho_bg)
    rho_vals.append(rho_obj)
    rho_vals.append(rho_cyl)
    
    return (object_params, rho_vals, (dialled_name, dialled_name_singular))


def isinsideobject(x,y,obj_params):

    # Function to determine whether or not a given spatial location
    # is within the source object.
   
        
    plate_thickness = obj_params[0]
    cylinder_radius = obj_params[1]
    separation = obj_params[2]
    co_x = 0
    co_y = 0
    plate_edge_near_cyl = co_x + cylinder_radius + separation
    plate_edge_far = plate_edge_near_cyl + plate_thickness
    xs = x - co_x
    ys = y - co_y
    
    if abs( xs * xs + ys * ys ) < cylinder_radius * cylinder_radius:
        ret = True
        which = 1
    elif x > plate_edge_near_cyl and x < plate_edge_far:
        ret = True
        which = 2
    else:
        ret = False
        which = 0
        
    return (ret, which)    
    
    
    