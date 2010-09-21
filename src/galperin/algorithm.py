# -*- coding: utf-8 -*-

import sys

import cube
import draw
import copy

N = 5
eta = 2
L = 100 / 1.4
alpha = 0.342076097

default_cube = cube.Cube([50, 50], 100)

def minimize(f):
    def get_point(X, Y, Z, C):
        def stopping_rule():
            pass
        
        if C.r < 2:
            return False
        
        deleted = True
        
        for c_j in C.divide(N):
            if any(map(lambda x: x.contains(c_j), X + Y + Z)):
                continue
            deleted = False
            if all(map(lambda x: x.not_contains(c_j), X + Y + Z)):
                return c_j.center
            # intersection
            if sum(map(lambda x: 1 if x.intersect(c_j) else 0, X + Y + Z)) == 1:
                only_intersector = filter(lambda x: x.intersect(c_j), X + Y + Z)
                maximize_index, max_err = 0, 0
                for (i, (x_j_s, x_k_s)) in enumerate(zip(c_j.center, only_intersector.center)):
                    if math.fabs(x_j_s - x_k_s) > max_err:
                        max_err = math.fabs(x_j_s - x_k_s)
                        maximize_index = i
                res = copy.copy(x_j.center)
                res[maximize_index] += c_j.r / 2.0
                return res
        if deleted:
            return False
        if stopping_rule():
            return False
        else:
            for c_j in C.divide(N):
                if any(map(lambda x: x.contains(c_j), X + Y + Z)):
                    continue
                p = get_point(X, Y, Z, c_j)
                if p:
                    return p
                    
    
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
    
    p = [1.0, 1.0]
    points = [(p, f(p))]
    X, Y, Z, m = split(X, Y, Z, points, 10002000)
    draw.create_image("/tmp/%s.bmp" % 0, X, Y, Z)
    
    for qqq in xrange(150):
        p = get_point(X, Y, Z, default_cube)
        if p == False: break
        points.append((p, f(p)))
        X, Y, Z, m = split(X, Y, Z, points, m)
        draw.create_image("/tmp/%s.bmp" % (1 + qqq), X, Y, Z)
        print m
    
    
minimize(lambda x: (x[0] - 23.1) ** 2 + (x[1] - 62.9)**2)