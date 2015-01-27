import matplotlib.pyplot as plt
import math
import plotaux.plot_aux as aux


buff = 10000

object_radii = (1.5,0.5,0.15,0.05)
plot_it_2 = 'phi'
plot_it_2 = 'force'

NP = len(object_radii)

for i in xrange(0,NP):  
     
    fID = str(buff + i)
    
    filename = 'out/' + fID + '_' + plot_it_1 + '.dat'
    if open(filename,'r'):
        
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
        plt.plot( y, phi ,label = str(object_radii[i]) )
        plt.subplot(122)    
        plt.plot( y, force ,label = str(object_radii[i]) )
        plt.xlim([0, 1.5])     

   
leg = plt.legend()   
leg.draw_frame(False)
plt.show()