# -*- coding: utf-8 -*-
from random import random

from complex_box import complex_box
from neuro import Neuron, NeuralNetwork

dimensions = 2
neurons = 5
delta = 10000.0


def f(x):
    return 0

def g(x):
    return sum(x)


def J(f, g, inside, borders, NN):
    return sum(map(lambda x: (NN.laplace(x) - f(x)) ** 2, inside)) + \
           delta * sum(map(lambda x: (NN(x) - g(x)) ** 2, borders))


def network_from_list(l):
    N = NeuralNetwork([])
    p = dimensions + 2 # 2 for weight and width
    for i in xrange(neurons):
        N.neurons.append(Neuron(l[i * p], l[i * p] + 1,
                                l[i * p + 2 : i * p + 2 + dimensions]))
    return N


inner = [[random(), random()] for i in range(40)]
border = ([[0.0, random()] for i in range(10)] + 
          [[1.0, random()] for i in range(10)] + 
          [[random(), 0.0] for i in range(10)] + 
          [[random(), 1.0] for i in range(10)])

print inner
print border


def to_minimize(l):
    nn = network_from_list(l)
    return J(f, g, inner, border, nn)


l = complex_box(to_minimize, (dimensions + 2) * neurons,
                  [-200.0, 1.0, -3.0, -3.0] * neurons,
                  [ 200.0, 7.0,  4.0,  4.0] * neurons)

print """Solution is complete
    %s neurons
    Complex box method
    f = x + y
    [-200..200, 1..7, -3..4, -3..4]
    40 point in area
    40 points on border
    delta = %s""" % (neurons, delta)

for i in xrange(neurons):
    print "%s * exp( -((%s - x)^2 + (%s - y)^2)/(%s^2) ) + " % (l[4 * i], l[4 * i + 2], l[4 * i + 3], l[4 * i + 1])
