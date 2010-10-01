'''
Created on Oct 1, 2010

@author: konstantin
'''
import math
import random
import unittest

from __init__ import network_from_list
from complex_box import complex_box


class Test(unittest.TestCase):


    def test2Neuro(self):
        def signal(point):
            x, y = point
            return 43.0 * math.exp(-(math.pow(0.5 - x, 2.0) + math.pow(0.82 - y, 2.0))/(0.5 ** 2)) + \
                   -2.0 * math.exp(-(math.pow(0.34 - x, 2.0) + math.pow(0.16 - y, 2.0))/(0.35 ** 2))
        
        points = [[random.random(), random.random()] for i in range(100)]
        
        def residual(l):
            NN = network_from_list(l)
            return sum(map(lambda x: math.fabs(signal(x) - NN(x)), points))
        
        print complex_box(residual, 8, [40, 0.3, 0.0, 0.0, -5.0, 0.2, 0.0, 0.0], [50, 0.6, 1.0, 1.0, 0.0, 0.4, 1.0, 1.0])

if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()