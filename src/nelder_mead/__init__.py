# -*- coding: utf-8 -*-

import math
import random


def nelder_mead(f, n):
    alpha = 1.0
    beta = 0.5
    gamma = 2.0
    epsilon = 1e-10
    
    def generate_points(n):
        return map(lambda i: map(lambda x: random.uniform(2, 10), range(n)),
                   range(n + 1))
    
    def centre_of_gravity(points):
        return map(lambda x: x / len(points), map(lambda i: sum(i), 
                                                  zip(*points)))
        
    def reflection(a, b):
        return map(lambda x, y: x + alpha * (x - y), a, b)
    
    def expansion(a, b):
        return map(lambda x, y: x + gamma * (y - x), a, b) 
    
    def compression(a, b):
        return map(lambda x, y: x + beta * (y - x), a, b)
    
    def reduction(a, points):
        return map(lambda x, y: map(lambda cx, cy: cx + 0.5 * (cy - cx), x, y),
                   [a] * len(points), points)
    
    def min_by(points, f = f):
        return reduce(lambda (mp, mv), (p, v): (p, v) if v < mv else (mp, mv),
                      map(lambda p: (p, f(p)), points),
                      (points[0], f(points[0])))
        
    def max_by(points):
        rez = min_by(points, lambda x: -1.0 * f(x))
        return (rez[0], -rez[1])
    
    def remove_point(p, points):
        return filter(lambda x: x != p, points)
        
    points = generate_points(n)
    
    while True:
        x_l, val_x_l = min_by(points)
        x_h, val_x_h = max_by(points)
        print val_x_h
        filtered_points = remove_point(x_h, points)
        x_s, val_x_s = max_by(filtered_points)
        
        x_2 = centre_of_gravity(filtered_points)
        
        if math.sqrt(sum(map(lambda x: math.pow(f(x) - f(x_2), 2.0), points)) 
                     / (len(points))) < epsilon:
            print "MINIMUM", val_x_l
            return x_l
        
        x_3 = reflection(x_2, x_h)
        
        if f(x_3) < val_x_l:
            x_4 = expansion(x_2, x_3)        
            if f(x_4) < val_x_l:
                filtered_points.append(x_4)
                points = filtered_points
            elif f(x_4) >= val_x_l:
                filtered_points.append(x_3)
                points = filtered_points
        elif val_x_s < f(x_3) <= val_x_h:
            x_5 = compression(x_2, x_h)
            filtered_points.append(x_5)
            points = filtered_points
        elif val_x_l < f(x_3) <= val_x_s:
            filtered_points.append(x_3)
            points = filtered_points
        elif f(x_3) > val_x_h:
            points = reduction(x_l, points)
