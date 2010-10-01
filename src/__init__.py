import math
from random import random

from neuro import Neuron, NeuralNetwork


dimensions = 2
neurons = 1
delta = 100.0

current = []
inner = []
border = []


def network_from_list(l):
    N = NeuralNetwork([])
    p = dimensions + 2 # 2 for weight and width
    for i in xrange(neurons):        
        N.neurons.append(Neuron(l[i * p], l[i * p + 1],
                                l[i * p + 2 : i * p + 2 + dimensions]))
    return N


inner = [[random(), random()] for i in range(15)]
border = ([[0.0, random()] for i in range(25)] + 
          [[1.0, random()] for i in range(25)] + 
          [[random(), 0.0] for i in range(25)] + 
          [[random(), 1.0] for i in range(25)])


def f(x):
    return 0


def g(x):
    return sum(x)


def J(f, g, inside, borders, NN):
    return sum(map(lambda x: math.pow(NN.laplace(x) - f(x), 2.0), inside)) + \
           delta * sum(map(lambda x: math.pow(NN(x) - g(x), 2.0), borders))


def to_minimize(l):
    global current
    global inner
    global border
    nn = network_from_list(l)
    current = l
    return J(f, g, inner, border, nn)