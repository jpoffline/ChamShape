

# F_i = m \ddot{X}_i
# \ddot{X} = [ X(t+1) + X(t-1) - 2X(t) ] / dt2
#  X(t+1)  = dt2 * F_i / m +  2X(t) - X(t - 1)

                

def comp_force(loc, d):
    return 1.0    

class PARTICLE():
    def __init__(self, mass = 1.0, ndims = 2, init_loc = (0.0, 1.0) ):
        self.mass = mass
        dum = []
        for d in xrange(0, ndims):
            dum.append(init_loc[d])
        self.loc = dum
    
    def setmass(self, mass):
        self.mass = mass    

    def mass(self):
        return self.mass    


def set_timestep(time_step):
    
    tt = time_step % 2
    
    if tt == 1:
        tp = tt - 1
    else:
        tp = tt + 1
        
    return (time_step + 1, tt, tp)    

def main():
    
    
    nparticles = 10
    ndim = 2
    ps = []
    for p in xrange(0,nparticles):
        ps.append(PARTICLE(1.0, ndim, (1.0,4.0)) )
    particles = []
    particles.append(ps)    
    particles.append(ps)
    print len(particles)
        
    dumm = []
    for d in xrange(0, ndim):
        dumm.append(0.0)
        
    time_step = 0
    
    time_step_max = 10
    
    while True:
        
        (time_step, tt, tp) = set_timestep(time_step)   
         
        for part_this in particles[tt]:    
            for d in xrange(0, ndim):
                dumm[d] = dumm[d] + part_this.loc[d]
        
        if time_step > time_step_max:
            break
        
        
    
    ''''
    while True:
        
        tt = time_step % 2
        if tt == 1:
            tp = tt - 1
        else:
            tp = tt + 1
        
        for p in particles:
            for d in dims:
                particle[p][d][tp] = ht2 * comp_force( particle[p][d][tt], d ) / particle.mass + 2.0 * particle[p][d][tt] - particle[p][d][tm]
        
        if check_state(state):
            break
        else:
            time_step = time_step + 1    
    
    '''
main()    