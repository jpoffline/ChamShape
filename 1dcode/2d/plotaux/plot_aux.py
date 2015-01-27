# plot_aux.py


def GetData(filename):
    f = open(filename,'r')
    lines = f.readlines()

    f.close()
    x = []
    y = []
    dat = []
    for line in lines:
        if line.strip() and len(line.split()) > 0:
            theline = line.split()
            x.append(theline[0])
            y.append(theline[1])
            dat.append(theline[2])
        
    return (x,y,dat)
    
    
def Get_x((x,y,field),VAL):
    Y = []
    F = []
    for i in xrange (0, len(x)):
        if float(x[i]) == VAL:
            Y.append(y[i])
            F.append(field[i])  
            
    return (Y,F)   
    

def getobjectinfo(outd, fn):
    
    filename = outd + fn
    file = open(filename,'r')
    lines = file.readlines()
    file.close()
    object_radii = []
    for line in lines:
        if line.strip() and len(line.split()) > 0:
            theline = line.split()
            object_radii.append(float(theline[0]))
    
    return tuple(object_radii)    