# -*- coding: utf-8 -*-

import math


class Cube(object):
    def __init__(self, center, r):
        self.center, self.r = map(float, center), float(r)
        
    def divide(self, N):
        c_2 = self.r / 2.0
        left = map(lambda x: x - c_2, self.center)
        right = map(lambda x: x + c_2, self.center)
        
        def generate_grid_on_line(left, right):
            tmp = (right - left) / (2 * N)
            l = left + tmp
            for _ in xrange(1, 2 * N, 2):
                yield l
                l += 2 * tmp
        
        def fix_point(current_fixed):
            current_unfixed = len(current_fixed)
            if current_unfixed == len(left):
                yield Cube(current_fixed, self.r / N)
            else:
                point_generator = generate_grid_on_line(left[current_unfixed],
                                                        right[current_unfixed])
                for coord in point_generator:
                    for i in fix_point(current_fixed + [coord]):
                        yield i
            
        return fix_point([])  
    
    def contains(self, other):
        t = 0.5 * (self.r - other.r)
        return all(map(lambda x, y: math.fabs(x - y) <= t,
                       self.center, other.center))
    
    def is_contained_by(self, other):
        return other.contains(self)
    
    def not_contains(self, other):
        t = 0.5 * (self.r - other.r)
        return any(map(lambda x, y: math.fabs(x - y) > t,
                       self.center, other.center))       
    
    def intersect(self, other):
        return (not self.contains(other) and 
                not other.contains(self))
                
    def left(self):
	    return map(lambda x: x - self.r / 2, self.center)
	    
    def right(self):
	    return map(lambda x: x + self.r / 2, self.center)
        
    def __repr__(self):
        return "Cube(%s, %s)" % (self.center, self.r)
        