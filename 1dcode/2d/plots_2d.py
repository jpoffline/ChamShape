# plots_2d.py


import matplotlib.pyplot as plt
import math
import plotaux.plot_aux as aux
import os.path


buff = 10000

# Read in the 'object properties' file
# in order to find out what we can plot
object_radii = aux.getobjectinfo('out/','object_props.dat')

plot_it_1_proto = 'phi'
plot_it_2_proto = 'force'

NP = len(object_radii)

for i in xrange(0,NP):  
     
    fID = str(buff + i)    
    
    if not os.path.exists('out/' + fID + '_' + plot_it_1_proto + '.dat'):
        plot_it_1 = 'u' + plot_it_1_proto
        plot_it_2 = 'u' + plot_it_2_proto
        inf = 'u'
    else:
        plot_it_1 = plot_it_1_proto  
        plot_it_2 = plot_it_2_proto
        inf = ''
    
    filename = 'out/' + fID + '_' + plot_it_1 + '.dat'
    
    if os.path.exists(filename):
        
        (x,y,F) = aux.GetData(filename)    
        (y,phi) = aux.Get_x((x,y,F),0)
        for j in xrange(0,len(y)):
            y[j] = str(float(y[j]) - object_radii[i])
    
        filename = 'out/' + fID + '_' + plot_it_2 + '.dat'
    
        (x,y,F) = aux.GetData(filename)    
        (y,force) = aux.Get_x((x,y,F),0)
        for j in xrange(0,len(y)):
            y[j] = str(float(y[j]) - object_radii[i])
        
        plt.subplot(121)    
        plt.plot( y, phi ,label = inf + str(object_radii[i]) )
        plt.subplot(122)    
        plt.plot( y, force ,label = inf + str(object_radii[i]) )
        plt.xlim([0, 1.5])     

   
leg = plt.legend()   
leg.draw_frame(False)
plt.show()