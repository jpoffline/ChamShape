# auc_funcs.py
import os

def shift_x(obj_size,x):
    
    shifted_x = []
    for i in xrange(0, len(x)):
        shifted_x.append(x[i] - obj_size * 0.5)
    
    return shifted_x


def check_dir_exists(f):
    d = os.path.dirname(f)
    if not os.path.exists(d):
        os.makedirs(d)
        print "created output directory"