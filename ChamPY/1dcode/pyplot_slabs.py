import matplotlib.pyplot as plt
import math, sys
import numpy as np
import os.path

class prettyfloat(float):
    def __repr__(self):
        return "%0.2f" % self
        
        

if len(sys.argv) > 1:
    DIR = sys.argv[1]
    DIR = DIR + '/'
else:
    DIR = 'out/'

#DIR = 'out3/'

fproto = '_out.dat'
rho_ambient = 0.001
#object_sizes = (0.05, 0.1, 0.5, 1.0, 1.5, 5.0)
object_sizes = (0.05, 0.1, 0.3, 0.5, 1.0, 1.5, 3.0, 4.0, 5.0, 10.0)
#object_sizes = [0.05]
Nobs = len(object_sizes)
buff = 10000
ID = 0

objs = []
ens = []
sizes = []
rhos = []
n = 0
for obj in object_sizes:
    filename = DIR + str(buff+ID) + fproto

    
    data = open(filename,'r')
    lines = data.readlines()
    data.close()
    x = []
    phi = []
    force = []
    rho = []
    for line in lines:
        p = line.split()
        x.append(float(p[0]))
        phi.append(float(p[1]))
        force.append(float(p[2]))
        rho.append(float(p[3]))
        
    en = 0.0    
    dx = x[10] - x[9]
    
    for i in xrange(0,len(x)):
        if rho[i] == rho_ambient and x[i]> -2 and x[i] < 1:
            en = en + force[i] * dx
    
    size = 0
    rho_test = rho_ambient
    size_ = []
    rho_ = []
    for i in xrange(0, len(x)):
        if rho[i] > rho_ambient:
            inside = True
        else:
            inside = False
        if inside:
            size = size + dx
        else:
            size = 0
        if inside and rho[i] != rho[i+1]:
            size_.append(size)
            rho_.append(rho[i])
            
    sizes.append(size_)
    rhos.append(rho_)    
                



    for nn in xrange(0, len(sizes[n])):
        string = ''
        mass = sizes[n][nn] * rhos[n][nn]
        string = string +  str(mass) + ' '
        
        if nn == 0:
            mass_ref = mass
            
   
    objs_ = mass / mass_ref
    plt.subplot(133)
    plt.plot(objs_,en,marker='o',markeredgecolor=None, markersize = 10)
    plt.xlabel('$m_{RHS} / m_{LHS}$')
    plt.ylabel('integrated force inside cavity')
    
    objs.append(objs_)
    ens.append(en)        
        
    x = np.array(x)
    phiv = np.array(phi)
    forcev = np.array(force)
    plt.subplot(131)
    plt.plot(x,phiv)
    plt.xlabel('$x$ [mm]')
    plt.ylabel('Chameleon scalar, $\phi$')
    plt.subplot(132)

    newstring = "%.1f" % (rho_[0] / rho_[1])
    print newstring
    plt.plot(x,forcev,label = newstring)
    plt.xlim([-1, -0.5]) 
    plt.xlabel('$x$ [mm] - between plates')
    plt.axhline(y=0.,color='k',ls='dashed')
    plt.ylabel('force in cavity between plates') 
    leg = plt.legend(loc=2,title='$\\rho_L / \\rho_R$')
    leg.draw_frame(False)


    ID = ID + 1    
    n = n + 1

''''
for n in xrange(0, len(sizes)):
    string = ''
    for nn in xrange(0, len(sizes[n])):
        
        mass = sizes[n][nn] * rhos[n][nn]
        string = string +  str(mass) + ' '
        
        if nn == 0:
            mass_ref = mass
            
    print string 
    objs[n] = mass / mass_ref
'''

plt.subplot(133)
plt.plot(objs,ens)
#plt.xlabel('$m_{RHS} / m_{LHS}$')
#plt.ylabel('integrated force inside cavity')

plt.show()        


