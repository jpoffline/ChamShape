# params.py

code_title = "Gradient flow solution to 2D chameleon field equation"
author_name = "J. Pearson"
author_institution = "Nottingham"
author_date = "Jan 2015"

#imax = 300
#jmax = 300
imax = 150
jmax = imax
imin = 0
jmin = 0

bl = 2
h = 0.08
ht = 0.0005
rho_obj = 1.0
rho_bg = 0.001
lam = 1.0
beta = 1.0
Mpl = 0.0046605407948
mphi2 = 0.0
outDIR = 'out/'

shape_type = 'circle' 
object_radii = (3.0,1.5,0.5,0.15,0.05)
object_param_dialled_name = 'radii'
object_param_dialled_name_singular = 'radius'


object_params = object_radii

thist_screen_freq = 100

tol = 0.01
#tol = 0.001

unit_length_screen = "[mm]"
unit_density_screen = "[g/cm^-3]"
unit_phi_screen = "[mm^-1]"

unit_length = "$[\mathrm{mm}]$"
unit_density = "$[\mathrm{g}/\mathrm{cm}^3]$"
unit_phi = "$[\mathrm{mm}^{-1}]$"


thist_screen_freq = 100
field_dump_freq = 100
thist_file_freq = 100

rho_file_suffix = '_rho.dat'
uptodate_phi_file_suffix = '_uphi.dat'
uptodate_force_file_suffix = '_uforce.dat'
final_phi_file_suffix = '_phi.dat'
final_force_file_suffix = '_force.dat'
thist_file_suffix = '_thist.dat'
log_file_name = 'log.dat'
obj_prop_file_name = 'object_props.dat'


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

# 
out_info_params = []
# If there are any more: make sure to put them on the end (before the '0')
out_info_params.append(outDIR)
out_info_params.append(thist_screen_freq)
out_info_params.append(field_dump_freq)
out_info_params.append(thist_file_freq)
out_info_params.append(rho_file_suffix)
out_info_params.append(final_phi_file_suffix)
out_info_params.append(final_force_file_suffix)
out_info_params.append(thist_file_suffix)
out_info_params.append(uptodate_phi_file_suffix)
out_info_params.append(uptodate_force_file_suffix)
out_info_params.append(log_file_name)
out_info_params.append('0')


