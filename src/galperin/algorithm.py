# -*- coding: utf-8 -*-

import sys

import cube

N = 3
eta = 0.01
L = 2
alpha = 0.342076097

default_cube = cube.Cube([0.5, 0.5], 1)

def minimize(f):
    def get_point(X, Y, Z, C):
        if C.r < 1e-5:
            return False
        
        not_embedded_cubes = []        
        for c_j in C.divide(N):
            if not any(map(lambda x: x.contains(c_j), X + Y + Z)):
                not_embedded_cubes.append(c_j)            
        
        for c_j in not_embedded_cubes:
            if all(map(lambda x: c_j.not_contains(x), X + Y + Z)):
                return c_j.center
            
        for c_j in not_embedded_cubes:
            if get_point(X, Y, Z, c_j):
                return get_point(X, Y, Z, c_j)
            
        return False
    
    def split(X, Y, Z, points, current_min):
        last_value = points[-1][1]
        new_min = min(last_value, current_min)
        if current_min == new_min:
            if last_value == new_min: X.append(
                cube.Cube(points[-1][0], eta / L))
            elif 0 < last_value <= new_min + eta: Y.append(
                cube.Cube(points[-1][0], eta / L))
            else: Z.append(cube.Cube(points[-1][0], (last_value - new_min - alpha * eta) / L))
        else:
            X = map(lambda p: cube.Cube(points[p][0], eta / L),
                    filter(lambda i: points[i][1] - new_min == 0,
                           range(len(points))))
            Y = map(lambda p: cube.Cube(points[p][0], eta / L),
                    filter(lambda i: 0 < points[i][1] - new_min <= eta,
                       range(len(points))))
            Z = map(lambda p: cube.Cube(points[p][0], (points[p][1] - new_min - alpha * eta) / L), 
                    filter(lambda i: points[i][1] - new_min > eta,
                       range(len(points))))
        return X, Y, Z, new_min
            
    X = []
    Y = []
    Z = []
    
    p = [0.453, 0.808]
    points = [(p, f(p))]
    X, Y, Z, m = split(X, Y, Z, points, 10002000)
    print X, Y, Z
    print "=" * 100
    print m
    print "=" * 100
    
    for qqq in xrange(150):
        p = get_point(X, Y, Z, default_cube)
        points.append((p, f(p)))
        X, Y, Z, m = split(X, Y, Z, points, m)
        print len(X), len(Y), len(Z)
        print "=" * 100
        print m
        print "=" * 100
    
    print points
    
    
minimize(lambda x: (x[0]-0.666)**2 + (x[1]-0.666)**4)