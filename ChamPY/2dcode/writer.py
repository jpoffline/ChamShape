# writer.py

def dump( (X,Y), field, filename, mins, maxs ):
    f = open(filename, 'w')
    
    for i in xrange(mins[0], maxs[0]):
        for j in xrange(mins[1], maxs[1]):
            f.write(str(X[i]) + ' ' + str(Y[j]) + ' ' + str(field[i][j])+' ' + '\n')
        f.write('\n')
        
    f.close()
    

def dump_thist(items,whereto):
    
    str_to_dump = ''
    for i in xrange(0, len(items)):
        str_to_dump = str_to_dump + str(items[i]) + ' '
        
    if whereto[0] == 'file':
        thist = open(whereto[1],'a')
        str_to_dump = str_to_dump + '\n'
        thist.write(str_to_dump)
        thist.close()
        
    elif whereto[0] == 'screen':
        print str_to_dump
    
def open_thist(filename):

    thist_file_stream = open(filename,'w')
    thist_file_stream.close()    
    

def dump_info(outDIR,log_fn,info):
    print info
    f = open(outDIR + log_fn,'w')
    f.write(info)
    f.close()    
    

def boot_up_objfile(outDIR, obj_prop_file_name):  
    
    filename = outDIR + obj_prop_file_name
    obj_prop_file_stream = open(filename,'w')
    obj_prop_file_stream.close()
    
    return filename
    

def write_objfile(filename, prop):
    
    obj_prop_file_stream = open(filename,'a')
    obj_prop_file_stream.write(str(prop) + '\n')
    obj_prop_file_stream.close()    
    
    