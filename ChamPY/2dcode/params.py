
# params.py

########################################################################################
#
#   PARAMETER FILE
#       -  code to solve chameleon field equation via gradient flow
#	
#	Set all simulation conditions here: 
#	- Output directory, suffices for files
#	- Grid properties:
#		-- space & time step-sizes, number of lattice sites
#	- Set model parameters 
#	- Labels for units	
#
########################################################################################

####---####---####---####---####---####---####---####---####---####---####---####---####---####---

## OUTPUT DIRECTORY ##

outDIR = 'out_test/'

# make sure output directory exists; if not, create it

import aux_funcs as aux
aux.check_dir_exists(outDIR)


####---####---####---####---####---####---####---####---####---####---####---####---####---####---

## LATTICE INFO ##

#imax = 300
#jmax = 300
imax = 150
jmax = imax


# Width (in grid-points) of the boundary layer on which to solve the field equations
bl = 2
# space step-size
h = 0.08
# time step-size
ht = 0.0005


####---####---####---####---####---####---####---####---####---####---####---####---####---####---

## NUMERICAL TOLERANCE ##

tol = 0.01

#tol = 0.001


####---####---####---####---####---####---####---####---####---####---####---####---####---####---

## MODEL PARAMS INFO ##

# pot-param: lambda (quartic coupling)
lam = 1.0

# pot-param: beta (coupling between scalar & matter)
beta = 1.0

# Planck mass
Mpl = 0.0046605407948

# scalar field bare mass
mphi2 = 0.0


####---####---####---####---####---####---####---####---####---####---####---####---####---####---

## DENSITY INFO ##

# density of the source
rho_obj = 1.0

# if there is another source object which is supposed to have a different density,
# then that is setup inside the source module file
# density of the ambient environment
rho_bg = 0.001


####---####---####---####---####---####---####---####---####---####---####---####---####---####---

## DUMP FREQS ##

thist_screen_freq = 100
field_dump_freq = 100
thist_file_freq = 100

####---####---####---####---####---####---####---####---####---####---####---####---####---####---

## AUTHOR INFO ##

code_title = "Gradient flow solution to 2D chameleon field equation"
author_name = "J. Pearson"
author_institution = "Nottingham"
author_date = "Jan 2015"



####---####---####---####---####---####---####---####---####---####---####---####---####---####---
####---####---####---####---####---####---####---####---####---####---####---####---####---####---
#
#   Now for some boring settings...
#
####---####---####---####---####---####---####---####---####---####---####---####---####---####---
####---####---####---####---####---####---####---####---####---####---####---####---####---####---

# minimum lattice coordinate
imin = 0
jmin = 0

####---####---####---####---####---####---####---####---####---####---####---####---####---####---

## UNITS INFO ##
unit_length_screen = "[mm]"
unit_density_screen = "[g/cm^-3]"
unit_phi_screen = "[mm^-1]"
unit_length = "$[\mathrm{mm}]$"
unit_density = "$[\mathrm{g}/\mathrm{cm}^3]$"
unit_phi = "$[\mathrm{mm}^{-1}]$"

####---####---####---####---####---####---####---####---####---####---####---####---####---####---

## FILE SUFFICES ##
rho_file_suffix = '_rho.dat'
uptodate_phi_file_suffix = '_uphi.dat'
uptodate_force_file_suffix = '_uforce.dat'
final_phi_file_suffix = '_phi.dat'
final_force_file_suffix = '_force.dat'
thist_file_suffix = '_thist.dat'
log_file_name = 'log.dat'
obj_prop_file_name = 'object_props.dat'


####---####---####---####---####---####---####---####---####---####---####---####---####---####---
####---####---####---####---####---####---####---####---####---####---####---####---####---####---


def param_housekeeping():

    ################################################################################################
    #
    #   Parameter house-keeping
    #       - called in "driver"
    #       - put various items into various arrays to be passed through the code
    #
    ################################################################################################

    # Dump the "units" into a list
    units = (unit_length,unit_density,unit_phi,unit_length_screen,unit_density_screen,unit_phi_screen)
    
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
    
    
    return (units, potparams, (gridparams,mins, maxs), evparams, out_info_params)


