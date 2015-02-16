# plot_aux.py
from ast import literal_eval


def Str2Float(data):
    for i in xrange(0,len(data)):
        data[i] = float(data[i])

    return data    

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
    
    
def GetData_arb(p1, p2, filename):
    f = open(filename,'r')
    lines = f.readlines()

    f.close()
    x = []
    dat = []
    for line in lines:
        if line.strip() and len(line.split()) > 0:
            theline = line.split()
            x.append(theline[p1])
            dat.append(theline[p2])
        
    return (x,dat)    
    
def Get_x((x,y,field),VAL):
    Y = []
    F = []
    for i in xrange (0, len(x)):
        if float(x[i]) == VAL:
            Y.append(y[i])
            F.append(field[i])  
            
    return (Y,F)
    
def Get_y((x,y,field),VAL):
    X = []
    F = []
    for i in xrange (0, len(y)):
        if float(y[i]) == VAL:
            X.append(x[i])
            F.append(field[i])  
            
    return (X,F)       
    

def getobjectinfo(outd, fn):
    
    filename = outd + fn
    file = open(filename,'r')
    lines = file.readlines()
    file.close()
    object_radii = []
    clever = False
    for line in lines:
        if not line.startswith('('):
            object_radii.append(float(line[0]))
        else:
            object_radii.append(literal_eval(line.strip())) 
            clever = True  
            
    object_radii = tuple(object_radii)        
    
    if clever:
        object_radiir = []
        for row in object_radii:
            object_radiir.append(row[1])
    else:
        object_radiir = object_radii  
          
    return object_radiir
    
    