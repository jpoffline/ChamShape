imax = 300
imin = 0
bl = 2
h = 0.04
ht = 0.0001
rho_obj = 1.0
rho_bg = 0.001
lam = 1.0
beta = 1.0
Mpl = 0.0046605407948
mphi2 = 0.0

tol = 0.001
#tol = 0.0001


unit_length_screen = "[mm]"
unit_density_screen = "[g/cm^-3]"
unit_phi_screen = "[mm^-1]"

unit_length = "$[\mathrm{mm}]$"
unit_density = "$[\mathrm{g}/\mathrm{cm}^3]$"
unit_phi = "$[\mathrm{mm}^{-1}]$"

units = (unit_length,unit_density,unit_phi,unit_length_screen,unit_density_screen,unit_phi_screen)

rho_vals = ( rho_bg, rho_obj )
potparams = ( mphi2, lam, beta, Mpl )

i_ev_min = imin + bl
i_ev_max = imax - bl    

gridparams = ( h, imin, imax )
evparams = ( h, ht, i_ev_min, i_ev_max )