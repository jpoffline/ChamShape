import os


def check_dir_exists(f):
    d = os.path.dirname(f)
    if not os.path.exists(d):
        os.makedirs(d)
        print "created output directory"

def dump(x,F,ID,DIR):
    
    filename = DIR + ID + '_out.dat'
    
    file = open(filename,'w')
    
    nF = len(F)
    
    for i in xrange(0, len(x)):
        to_dump = str(x[i]) + ' '
        for n in xrange(0, nF):
            to_dump = to_dump + str(F[n][i]) + ' '
        to_dump = to_dump + '\n'
        file.write(str(to_dump))    
    
    file.close()