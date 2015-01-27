# printinfo.py

import computers

def print_intro(title, author, institution, date):
    
    string = print_blank_line()
    string = string + print_line() + print_blank_line()
    
    string = string + title + print_blank_line()
    string = string + author + ", " + institution + ", " + date + print_blank_line()
    string = string + print_line() + print_blank_line()
    
    return string
    
def print_params( gps, rps, pps, units, tol, ht):

    string = "beta = " + str(pps[2]) + print_blank_line()
    string = string + "lambda = " + str(pps[1]) + print_blank_line()
    string = string + "m_phi^2 = " + str(pps[0]) + print_blank_line()
    string = string + "num grid-points = " + str(gps[2]) + print_blank_line()
    string = string + "h = " + str(gps[0]) + print_blank_line()
    string = string + "ht = " + str(ht) + print_blank_line()
    string = string + "tol = " + str(tol) + print_blank_line()
    string = string + "m_eff^-1 = " + str(computers.compute_eff_length( pps[1], pps[2], pps[3], rps[1] ) ) + units[3] + print_blank_line()
    string = string + "Object density = " + str(rps[1]) + units[4] + print_blank_line()
    string = string + "Environment density = " + str(rps[0]) + units[4]
    string = string + print_blank_line()
    return string

def print_object_params( param_name_dialled, values ):
    string = param_name_dialled + ' = '
    for i in xrange(0, len(values)):
        string = string + str(values[i]) + ' '
        
    string = string + print_blank_line()
    return string

    
def print_line():
    
    string =  "---------------------------------------------------------"    
    return string
    
def print_blank_line():
    string =  "\n"    
    return string
    
    