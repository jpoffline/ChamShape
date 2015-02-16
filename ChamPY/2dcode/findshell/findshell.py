import os.path, sys
sys.path.append(os.path.join(os.path.dirname(os.path.realpath(__file__)), os.pardir))
import plotaux.plot_aux as aux
from shell_algorithms import *
import matplotlib.pyplot as plt


markers = ('o','s','^','d','v','*')

type_dir = GetFileName(sys.argv)
output_dir = 'output/'
objs_props_file = 'object_props.dat'

# What're the force thresholds to use?
threshs = (0.1, 1.0, 2.0, 5.0, 10.0)

# Numerical buffer used on the file name
ID_buffer = 10000
ID_thresh = ID_buffer

root_of_files = '../'
DIR = root_of_files + type_dir + '/'
object_radii = aux.getobjectinfo(DIR,objs_props_file)
print "\nReading object properties file: ", DIR + objs_props_file + '\n'
reference_size = object_radii[0]

# Change the radii to be relative to the "first" one
for i in xrange(0, len(object_radii)):
    object_radii[i] = object_radii[i] / reference_size



threshs_file = output_dir + type_dir + '_threshs.dat'
thresh_dump = open(threshs_file, 'w')
thresh_dump.write('# Force thresholds used. Columns:\n')
thresh_dump.write('# ID \tthresh\n')

nids = len(object_radii)



#--#
ID_shape_aspect_ratio = 0
ID_maxforce = 1
ID_shape_frac_above_thresh = 3
ID_force_density_in_source = 4
ID_force_density_above_thresh = 5
#--#

for thresh in threshs:
    ID_file = ID_buffer
    # Create output filename
    output_filename = output_dir + 'out_' + type_dir + '_thresh_' + str(ID_thresh) + '.dat'
    # Open output file
    output_file = open(output_filename,'w') 
    thresh_dump.write(str(ID_thresh) + '\t' + str(thresh) + '\n')
    
    shape_aspect_ratio = []
    shape_frac_above_thresh = []
    force_density_in_source = []
    force_density_above_thresh = []
    print "thresh = ", thresh
    
    for ID in xrange(0, nids):
        file_name = DIR + str(ID_file)
        aspect_ratio = object_radii[ID] 
        print "reading in ::", file_name
        vals, locs = find_shell_main(file_name, thresh)
        
        dump_locs = open(output_dir + type_dir + '_' + str(ID_thresh) + '_' + str(ID_file) + '_locs.dat','w')
        for loc in locs:
            string = ''
            for i in xrange(0, len(loc)):
                string += str(loc[i]) + '\t'
            dump_locs.write(string + '\n')
        dump_locs.close()
        
        
        vals.insert(0,aspect_ratio)
        write_vals(vals, output_file)
        shape_aspect_ratio.append(vals[ID_shape_aspect_ratio])
        shape_frac_above_thresh.append(vals[ID_shape_frac_above_thresh])
        force_density_in_source.append(vals[ID_force_density_in_source])
        force_density_above_thresh.append(vals[ID_force_density_above_thresh])
        ID_file += 1
        
    plt.subplot(131)
    plt.plot(shape_aspect_ratio, shape_frac_above_thresh, marker = markers[ID_thresh - ID_buffer],label=str(thresh))
    plt.xlabel('aspect ratio')
    plt.ylabel('Fraction of shape above threshold')
    
    plt.subplot(132)
    plt.plot(shape_aspect_ratio, force_density_above_thresh, marker = markers[ID_thresh - ID_buffer],label=str(thresh))
    plt.xlabel('aspect ratio')
    plt.ylabel('force density above threshold')
    
    # Close this output file    
    output_file.close()  
    ID_thresh += 1  

thresh_dump.close()

# ------- Now to plot
lg = plt.legend(title='threshold')
lg.draw_frame(False)
plt.subplot(133)
plt.plot(shape_aspect_ratio, force_density_in_source, marker = markers[len(markers)-1])    
plt.xlabel('aspect ratio')
plt.ylabel('force density inside source')

plt.show()
