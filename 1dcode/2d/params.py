# params.py

#imax = 300
#jmax = 300
imax = 150
jmax = imax
imin = 0
jmin = 0

bl = 2
h = 0.04
ht = 0.0005
rho_obj = 1.0
rho_bg = 0.001
lam = 1.0
beta = 1.0
Mpl = 0.0046605407948
mphi2 = 0.0
outDIR = 'out/'

thist_screen_freq = 100

tol = 0.01
#tol = 0.001

unit_length_screen = "[mm]"
unit_density_screen = "[g/cm^-3]"
unit_phi_screen = "[mm^-1]"

unit_length = "$[\mathrm{mm}]$"
unit_density = "$[\mathrm{g}/\mathrm{cm}^3]$"
unit_phi = "$[\mathrm{mm}^{-1}]$"









################################################################################################
#
#   Put these items into various arrays to be passed through the code
#
################################################################################################

units = (unit_length,unit_density,unit_phi,unit_length_screen,unit_density_screen,unit_phi_screen)

rho_vals = ( rho_bg, rho_obj )
potparams = ( mphi2, lam, beta, Mpl )

i_ev_min = imin + bl
i_ev_max = imax - bl    
j_ev_min = jmin + bl
j_ev_max = jmax - bl 

mins = (imin, jmin)
maxs = (imax, jmax)

ev_min = (i_ev_min, j_ev_min)
ev_max = (i_ev_max, j_ev_max)

gridparams = ( h, mins, maxs )
evparams = ( h, ht, ev_min, ev_max )