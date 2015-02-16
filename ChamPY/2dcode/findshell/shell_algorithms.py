import os.path, sys
sys.path.append(os.path.join(os.path.dirname(os.path.realpath(__file__)), os.pardir))
import plotaux.plot_aux as aux


def GetFileName(arg):
    if len(arg) > 1:   
        return arg[1] 
    else:
        print "You need to specify the file"
        return False
    
#---------------------------------------------------------------------------------    
    
def find_shell_main(filename, thresh):    
    
    force_file_suffix = '_force.dat'
    rho_file_suffix = '_rho.dat'
            
    (x, y, force) = aux.GetData( filename + force_file_suffix ) 
    (x,y, rho) = aux.GetData( filename + rho_file_suffix ) 

    for i in xrange(0, len(rho)):
        rho[i] = float(rho[i])
        force[i] = float(force[i])
    
    force_in_source = 0.0   
    points_in_source = 0
    
    points_above_thresh = 0
    force_above_thresh = 0.0

    min_rho = min(rho)
    max_rho = max(rho)
    locs = []
    for i in xrange(0, len(force)):    
        if rho[i] > min_rho:
            points_in_source += 1
            force_in_source += force[i]
            if force[i] > thresh:
                points_above_thresh += 1
                force_above_thresh += force[i]    
                locs.append((x[i], y[i], force[i]))


    shape_frac_above_thresh = float(points_above_thresh) / float(points_in_source)                
    force_density_in_source = force_in_source / float(points_in_source)
    force_density_above_thresh = force_above_thresh / points_above_thresh


    vals = []
    vals.append(max(force))
    vals.append(thresh)
    vals.append(shape_frac_above_thresh)
    vals.append(force_density_in_source)
    vals.append(force_density_above_thresh)

    
    return vals, locs

#---------------------------------------------------------------------------------

def write_vals(vals, dump):

    string = ''
    for val in vals:
        string = string + str(val) + '\t'
    string = string + '\n'    
    dump.write(string)    


#---------------------------------------------------------------------------------


