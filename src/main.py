# -*- coding: utf-8 -*-
import math
from random import random

from nelder_mead import nelder_mead
from neuro import Neuron, NeuralNetwork


dimensions = 2
neurons = 1
delta = 1000.0


def f(x):
    return 0

def g(x):
    return sum(x)


def J(f, g, inside, borders, NN):
    #for i in borders:
    #    print "Border point", i, g(i), NN(i), math.pow(NN(i) - g(i), 2.0)
    return sum(map(lambda x: math.pow(NN.laplace(x) - f(x), 2.0), inside)) + \
           delta * sum(map(lambda x: math.pow(NN(x) - g(x), 2.0), borders))


def network_from_list(l):
    N = NeuralNetwork([])
    p = dimensions + 2 # 2 for weight and width
    for i in xrange(neurons):        
        N.neurons.append(Neuron(l[i * p], l[i * p + 1],
                                l[i * p + 2 : i * p + 2 + dimensions]))
    return N


inner = [[random(), random()] for i in range(10)]
border = ([[0.0, random()] for i in range(10)] + 
          [[1.0, random()] for i in range(10)] + 
          [[random(), 0.0] for i in range(10)] + 
          [[random(), 1.0] for i in range(10)])


def to_minimize(l):
    nn = network_from_list(l)
    return J(f, g, inner, border, nn)


l = nelder_mead(to_minimize, neurons * (2 + dimensions))

print """Solution is complete
    %s neurons
    Nelder-Mead
    f = x + y
    %s point in area
    %s points on border
    delta = %s
    AVERAGE on border is %s""" % (neurons, len(inner), len(border), delta, 
                                  J(f, g, inner, border, 
                                    network_from_list(l)) / (delta * len(border)))
    
print "MIN VALUE = J = ", J(f, g, inner, border, network_from_list(l))
#print l
#for i in border:
#        print "Border point", i, g(i), network_from_list(l)(i), math.pow(network_from_list(l)(i) - g(i), 2.0)
print "(" ,
for i in xrange(neurons):
    ns = 2 + dimensions
    print "(%s)*exp(-(((%s)-x)^2+((%s)-y)^2)/((%s)^2))+" % (l[ns * i], l[ns * i + 2], l[ns * i + 3], l[ns * i + 1]),
print "0)"