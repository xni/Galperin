# -*- coding: utf-8 -*-

'''
Метод имитации отжига, совмещенный с PRrop
'''

import math
import random


Q = 0.01 # вероятность неприятия плохого решения


def simulated_annealing(point, derivatives, val_f):
    d = derivatives(point)
    while sum(map(math.fabs, d)) > 0.0001:
        s = 0.01
        while True:
            point_n = map(lambda x, y: x - s * y, point, d)
            val_p = val_f(point)
            val_p_n = val_f(point_n)
            if val_p_n < val_p:
                point = point_n
                break
            else:
                p = math.exp(-(val_p_n - val_p) / Q)
                #print "Probability is", p
                r = random.random()
                if r < p:
                    print "Accepting bad solution with probability", p
                    point = point_n
                    break
                s /= 2.0
        print "J = ", val_f(point)
        d = derivatives(point)
    return point
        