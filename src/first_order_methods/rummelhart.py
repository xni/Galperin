# -*- coding: utf-8 -*-

'''
Он же метод тяжелого шарика.
с. 212
'''

import math

BETA = 0.99


def rummelhart(point, derivatives, val_f):
    d2 = derivatives(point)
    while sum(map(math.fabs, d2)) > 0.001:
        d = derivatives(point)
        point = map(lambda x, y, z: x - 0.00001 * (y + BETA * z), point, d, d2)
        d2 = d
        print "J = ", val_f(point)
    return point
        