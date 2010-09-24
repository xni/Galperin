# -*- coding: utf-8 -*-
import math
from random import random
from time import time

from estimate import make_quad_estimate
from complex_box import complex_box
from neuro import Neuron, NeuralNetwork


dimensions = 2
neurons = 3
delta = 10000.0


def f(x):
    return 0

def g(x):
    return sum(x)


def J(f, g, inside, borders, NN):
    return sum(map(lambda x: math.pow(NN.laplace(x) - f(x), 2.0), inside)) + \
           delta * sum(map(lambda x: math.pow(NN(x) - g(x), 2.0), borders))


def network_from_list(l):
    N = NeuralNetwork([])
    p = dimensions + 2 # 2 for weight and width
    for i in xrange(neurons):        
        N.neurons.append(Neuron(l[i * p], l[i * p + 1],
                                l[i * p + 2 : i * p + 2 + dimensions]))
    return N




def to_minimize(l):
    inner = [[random(), random()] for i in range(5)]
    border = ([[0.0, random()] for i in range(25)] + 
          [[1.0, random()] for i in range(25)] + 
          [[random(), 0.0] for i in range(25)] + 
          [[random(), 1.0] for i in range(25)])

    nn = network_from_list(l)
    return J(f, g, inner, border, nn)

t_start = time()
l = complex_box(to_minimize, neurons * (2 + dimensions), 
                [-250.0, 1.0, -5.0, -5.0] * neurons, 
                [250.0, 10.0, 6.0, 6.0] * neurons)
t_end = time()

resulting_nn = network_from_list(l)
sqrt_err = make_quad_estimate(resulting_nn, g, 0, 0, 1, 1, 0.01, 0.01)

print u"""Solution is complete
    %s neurons
    Complex Box
    f = x + y
    %s point in area
    %s points on border
    delta = %s
    J = %s
    sqrt_estimate = %s
    Time taken: %s""" % (neurons, len(inner), len(border), delta, 
                         J(f, g, inner, border,resulting_nn),
                         sqrt_err, t_end - t_start)

print "(" ,
for i in xrange(neurons):
    ns = 2 + dimensions
    print "(%s)*exp(-(((%s)-x)^2+((%s)-y)^2)/((%s)^2))+" % (l[ns * i], l[ns * i + 2], l[ns * i + 3], l[ns * i + 1]),
print "0)"
