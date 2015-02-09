#

# Main entry point into the ChamPY2D code.
# J. Pearson, Nottingham, Jan 2015

#

#



import main, setups, sys, messages

# Setup the default source type
source_type_default = "ellipse"

NumCommandArgs = len(sys.argv)


if NumCommandArgs > 1:   
    # Get the source type from the command-line (else, default is used)
    source_type_name = sys.argv[1]  
    # If a second argument is passed, then don't solve the field equations
    if NumCommandArgs > 2:   
        runSolver = False
    else:
        runSolver = True 
else:
    source_type_name = source_type_default

# Setup the source-class; also, check that it exists
(flag_exists, source_type) = setups.setup_source_class(source_type_name)

    
# If the chosen source exists, the proceed to the main solver-driver
if not flag_exists:
    main.driver(source_type, runSolver)   
else:         
    print messages.MESSAGE_SOURCE_NOT_EXIST
    
    
    