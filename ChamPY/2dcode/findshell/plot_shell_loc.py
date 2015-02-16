import os.path, sys
sys.path.append(os.path.join(os.path.dirname(os.path.realpath(__file__)), os.pardir))
import plotaux.plot_aux as aux
import matplotlib.pyplot as plt

import shell_algorithms as algs

output_dir = 'output/'

type_dir = algs.GetFileName(sys.argv)


buffer_1 = 10000
buffer_2 = 10000
ID_1 = buffer_1
ID_2 = buffer_2


i = 1
n = 4
m = 4
num_plots_x = n
num_plots_y = m
    
for pp in xrange(0,m):    
    ID_1 = buffer_1
   

    for plotit in xrange(0, n):
        
        ID = str(ID_1) + '_' + str(ID_2)

        data_file_name = output_dir + type_dir + '_' + ID + '_locs.dat'
        (x,y,F) = aux.GetData(data_file_name)
        plt.subplot(num_plots_y,num_plots_x,i)
        plt.plot(x,y, marker = 'o',markeredgecolor = 'none', linestyle = 'None')
        maxx = 0.0
        for xx in x:
            if xx > maxx:
                maxx = xx
        maxx = float(maxx) + 0.4        
    
        plt.xlim(-maxx, maxx)
        plt.ylim(-maxx, maxx)    
        i +=1
        ID_1 += 1
        
    ID_2 +=1
     
plt.show()    