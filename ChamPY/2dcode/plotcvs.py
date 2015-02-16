
import plotaux.plot_aux as plotaux
import matplotlib.pyplot as plt
import sys
import matplotlib as mpl

# Import thingy to use latex labels
mpl.rcParams['text.usetex'] = True

# What're the values lambda?
lamvals = (0.5, 1.0, 2.0)
# What're the folders called for each value of lambda?
lamdirs = ('out_inv_l05', 'out_inv', 'out_inv_l2')

# Some markers to use
markers = ('o','s','^')

for i in xrange(0, len(lamvals)):

    lam = lamvals[i]
    DIR = lamdirs[i]
    
    filename = DIR + '/centralvals.dat'

    # column numbers in data
    radius_loc = 1
    phicen_loc = 4

    (radius, phi_cen) = plotaux.GetData_arb(radius_loc-1, phicen_loc-1, filename)
    radius = plotaux.Str2Float(radius)
    phi_cen = plotaux.Str2Float(phi_cen)
   
    # Now compute the derivative of the central value,
    # with respect to the size of the cavity.
    # Remember the radius, which is the "central" value in the bin
    # used to compute the derivative
    rad_d = []
    phi_cen_d = []
    for j in xrange(0, len(radius)-1):
        rad_d.append(radius[j] + (radius[j+1] - radius[j]) / 2.0)
        phi_cen_d.append(( phi_cen[j+1] - phi_cen[j] ) / (radius[j+1] - radius[j]))

    for j in xrange(0, len(phi_cen_d)):
        phi_cen_d[j] = abs(phi_cen_d[j])

    plt.subplot(121)
    plt.loglog( radius, phi_cen ,label = str(lam) , marker=markers[i], markeredgecolor = None)
    plt.xlabel(r'radius of cavity, $R$ [mm]')
    plt.ylabel(r'field at centre of cavity, $\phi_c$')
  
    plt.subplot(122)
    plt.loglog(rad_d, phi_cen_d, label = str(lam), marker=markers[i], markeredgecolor = None)
    plt.xlabel(r'radius of cavity, $R$ [mm]')
    plt.ylabel(r'$|d\phi_c/dR|$')

leg = plt.legend(title=r'Quartic coupling, $\lambda$', loc = 3)
leg.draw_frame(False)
plt.show()
