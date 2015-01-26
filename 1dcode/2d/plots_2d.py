import matplotlib.pyplot as plt
import math
import plotaux.plot_aux as aux


buff = 1000
#object_sizes = (3.0,1.0,0.3,0.1,0.03)
object_radii = (1.5,0.5,0.15,0.05)

NP = len(object_radii)

for i in xrange(0,NP):  
     
    fn = str(buff) + str(i)
    filename = 'out/' + fn + '_force.dat'
    
    (x,y,force) = aux.GetData(filename)    
    (y,f) = aux.Get_x((x,y,force),0)
    for j in xrange(0,len(y)):
        y[j] = str(float(y[j]) - object_radii[i])
        
    plt.plot( y, f ,label=str(object_radii[i]))
    

#plt.xlim([0, 1.5])    
leg = plt.legend()   
leg.draw_frame(False)
plt.show()