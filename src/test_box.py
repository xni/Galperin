# -*- coding: utf-8 -*-
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
    def test1Neuro(self):
        return True
        def signal(point):
            x, y = point
            return 43.0 * math.exp(-(math.pow(0.5 - x, 2.0) + math.pow(0.82 - y, 2.0))/(0.5 ** 2))
        
        points = [[random.random(), random.random()] for _ in range(100)]
        
        def residual(l):
            NN = network_from_list(l)
            return sum(map(lambda x: math.fabs(signal(x) - NN(x)), points))
          
        res = complex_box(residual, 4, [0, 0.1, 0.0, 0.0], [100, 1.0, 1.0, 1.0])
        diffs = map(lambda x, y: math.fabs(x - y), [43.0, 0.5, 0.5, 0.82], res)
        print diffs
        self.assertTrue(all(map(lambda x: x < 1e-4, diffs)))


    def test2Neuro(self):
        return True
        def signal(point):
            x, y = point
            return 20.0 * math.exp(-(math.pow(0.5 - x, 2.0) + math.pow(0.82 - y, 2.0))/(0.5 ** 2)) + \
                   25.0 * math.exp(-(math.pow(0.34 - x, 2.0) + math.pow(0.16 - y, 2.0))/(0.35 ** 2))
                           
        points = [[random.random(), random.random()] for _ in range(300)]
        
        def residual(l):
            NN = network_from_list(l)
            return sum(map(lambda x: math.fabs(signal(x) - NN(x)), points))
        
        res = complex_box(residual, 8, [0, 0.1, 0.0, 0.0] * 2, [100, 1.0, 1.0, 1.0] * 2)
        print res
        # нижестоящая проверка не работает, так как базисные функции не знают "порядка"
        # ответ 25 0.35 0.34 0.16 20 0.5 0.5 0.82 таким образом был забракован
        # diffs = map(lambda x, y: math.fabs(x - y), [20.0, 0.5, 0.5, 0.82, 25, 0.35, 0.34, 0.16], res)
        # print diffs
        # self.assertTrue(all(map(lambda x: x < 1e-4, diffs)))       

    def test3Neuro(self):
        def signal(point):
            x, y = point
            return 43.0 * math.exp(-(math.pow(0.5 - x, 2.0) + math.pow(0.82 - y, 2.0))/(0.5 ** 2)) + \
                   20.0 * math.exp(-(math.pow(0.34 - x, 2.0) + math.pow(0.16 - y, 2.0))/(0.35 ** 2)) + \
                   14.0 * math.exp(-(math.pow(0.2 - x, 2.0) + math.pow(0.7 - y, 2.0))/(0.31 ** 2))
                   
        points = [[random.random(), random.random()] for _ in range(200)]
        
        def residual(l):
            NN = network_from_list(l)
            return sum(map(lambda x: math.fabs(signal(x) - NN(x)), points))
        
        res = complex_box(residual, 12, [0, 0.1, 0.0, 0.0] * 3, [100, 1.0, 1.0, 1.0] * 3)
        print res
        # см. комментарий в тесте 2
        # diffs = map(lambda x, y: math.fabs(x - y), [20.0, 0.5, 0.5, 0.82, 25, 0.35, 0.34, 0.16, 14, 0.8, 0.94, 0.01], res)
        # print diffs
        # self.assertTrue(all(map(lambda x: x < 1e-4, diffs)))   

if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()