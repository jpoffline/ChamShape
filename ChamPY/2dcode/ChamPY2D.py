import main 
import setups
import sys
from messages import *

# Setup the default source type
source_type_default = "ellipse"

# Get the source type from the command-line (else, default is used)
if len(sys.argv) > 1:   
    source_type_name = sys.argv[1]   
else:
    source_type_name = source_type_default



# Setup the source-class; also, check that it exists
(flag_exists, source_type) = setups.setup_source_class(source_type_name)

if len(sys.argv) > 2:   
    runSolver = False
else:
    runSolver = True
    
# If the chosen source exists, the proceed
if not flag_exists:
    main.driver(source_type, runSolver)   
else:         
    print MESSAGE_SOURCE_NOT_EXIST
    
    
    