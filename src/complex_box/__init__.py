# -*- coding: utf-8 -*-

import math
import random


def complex_box(f, n, lo, hi):
    alpha = 1.3
    epsilon = 1e-9
    
    def generate_points(n):
        return map(lambda i: map(lambda l, h, x: l + random.random() * (h - l),
                                 lo, hi, range(n)),
                   range(2 * n))
    
    def centre_of_gravity(points):
        return map(lambda x: x / len(points), map(lambda i: sum(i), 
                                                  zip(*points)))
        
    def reflection(a, b, alpha):
        def check_border(x, l, h):
            if x > h:
                return h
            if x < l:
                return l
            return x
        
        return map(lambda x, y, l, h: check_border(x + alpha * (x - y), l, h), a, b, lo, hi)
        
    
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
        x_h, val_x_h = max_by(points)        
        filtered_points = remove_point(x_h, points)        
        x_2 = centre_of_gravity(filtered_points)
        
        if math.sqrt(sum(map(lambda x: math.pow(f(x) - f(x_2), 2.0), points)) 
                     / (len(points))) < epsilon:
            x_l, val_x_l = min_by(points)
            return x_l
        
        c_alpha = alpha
        x_3 = reflection(x_2, x_h, c_alpha)
        while f(x_3) >= val_x_h:
            c_alpha /= 2.0
            x_3 = reflection(x_2, x_h, c_alpha)
        
        filtered_points.append(x_3)
        points = filtered_points
