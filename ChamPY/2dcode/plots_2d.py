# plots_2d.py


import matplotlib.pyplot as plt
import math, sys
import plotaux.plot_aux as aux
import os.path


buff = 10000

if len(sys.argv) > 1:
    fileDIR = sys.argv[1]
else:    
    fileDIR = 'out'

fileDIR = fileDIR + '/'

# Read in the 'object properties' file
# in order to find out what we can plot
object_radii = aux.getobjectinfo(fileDIR,'object_props.dat')


plot_it_1_proto = 'phi'
plot_it_2_proto = 'force'

NP = len(object_radii)

for i in xrange(0,NP):  
     
    fID = str(buff + i)    
    
    if not os.path.exists(fileDIR + fID + '_' + plot_it_1_proto + '.dat'):
        plot_it_1 = 'u' + plot_it_1_proto
        plot_it_2 = 'u' + plot_it_2_proto
        inf = 'u'
    else:
        plot_it_1 = plot_it_1_proto  
        plot_it_2 = plot_it_2_proto
        inf = ''
    
    filename = fileDIR + fID + '_' + plot_it_1 + '.dat'
    
    if os.path.exists(filename):
        
        (x,y,F) = aux.GetData(filename)    
        (yy,phi_y) = aux.Get_x((x,y,F),0)
        Y = []
        for j in xrange(0,len(yy)):
            Y.append(str(float(yy[j]) - object_radii[i]))
            
        (xx,phi_x) = aux.Get_y((x,y,F),0)
        X = []
        for j in xrange(0,len(xx)):
            X.append(str(float(xx[j])))
            
    
        filename = fileDIR + fID + '_' + plot_it_2 + '.dat'    
        (x,y,F) = aux.GetData(filename)    
        (yy,force_y) = aux.Get_x((x,y,F),0)
        
        (xx,force_x) = aux.Get_y((x,y,F),0)        
        
        
        plt.subplot(221)    
        plt.plot( Y, phi_y ,label = inf + str(object_radii[i]) )
        plt.xlabel('x')
        plt.ylabel('$\phi$')
        
        plt.subplot(222)    
        plt.plot( X, phi_x ,label = inf + str(object_radii[i]) )
        plt.xlabel('y')
        plt.ylabel('$\phi$')
                
        plt.subplot(223)    
        plt.plot( Y, force_y ,label = inf + str(object_radii[i]) )
        plt.xlim([0, 1.5])     
        plt.xlabel('x')
        plt.ylabel('force')
        
        plt.subplot(224)    
        plt.plot( X, force_x ,label = inf + str(object_radii[i]) )
        plt.xlim([3, 5]) 
        plt.xlabel('y')
        plt.ylabel('force')
           
leg = plt.legend()   
leg.draw_frame(False)
plt.show()