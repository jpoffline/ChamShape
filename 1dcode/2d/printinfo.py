# printinfo.py

import computers

def print_intro(author,institution):
    
    string = print_blank_line()
    string = string + print_line() + print_blank_line()
    
    string = string + "Gradient flow solution to 2D chameleon field equation" + print_blank_line()
    string = string + author + ", " + institution + ", Jan 2015" + print_blank_line()
    string = string + print_line()
    
    return string
    
def print_params(( h, imin, imax ),( rho_bg, rho_obj ),( mphi2, lam, beta, Mpl ),(unit_length,unit_density,unit_phi,unit_length_screen,unit_density_screen,unit_phi_screen),tol):
    
    string = "beta = " + str(beta) + print_blank_line()
    string = string + "lambda = " + str(lam) + print_blank_line()
    string = string + "m_phi^2 = " + str(mphi2) + print_blank_line()
    string = string + "num grid-points = " + str(imax) + print_blank_line()
    string = string + "h = " + str(h) + print_blank_line()
    string = string + "tol = " + str(tol) + print_blank_line()
    string = string + "m_eff^-1 = " + str(computers.compute_eff_length( lam, beta, Mpl, rho_obj ) ) + unit_length_screen + print_blank_line()
    string = string + "Object density = " + str(rho_obj) + unit_density_screen + print_blank_line()
    string = string + "Environment density = " + str(rho_bg) + unit_density_screen
    
    return string
    
def print_line():
    
    string =  "---------------------------------------------------------"    
    return string
    
def print_blank_line():
    string =  "\n"    
    return string