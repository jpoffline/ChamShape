# writer.py

def dump( (X,Y), field, filename, mins, maxs ):
    f = open(filename, 'w')
    
    for i in xrange(mins[0], maxs[0]):
        for j in xrange(mins[1], maxs[1]):
            f.write(str(X[i]) + ' ' + str(Y[j]) + ' ' + str(field[i][j])+' ' + '\n')
        f.write('\n')
        
    f.close()