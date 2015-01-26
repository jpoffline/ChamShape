# auc_funcs.py

def shift_x(obj_size,x):
    
    shifted_x = []
    for i in xrange(0, len(x)):
        shifted_x.append(x[i] - obj_size * 0.5)
    
    return shifted_x
