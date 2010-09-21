from random import random

from complex_box import complex_box
from neuro import Neuron, NeuralNetwork

dimensions = 2
neurons = 7
delta = 100.0


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


inner = [[random(), random()] for i in range(400)]
border = ([[0.0, random()] for i in range(100)] + 
          [[1.0, random()] for i in range(100)] + 
          [[random(), 0.0] for i in range(100)] + 
          [[random(), 1.0] for i in range(100)])

print inner
print border


def to_minimize(l):
    nn = network_from_list(l)
    return J(f, g, inner, border, nn)


l = complex_box(to_minimize, (dimensions + 2) * neurons,
                  [-100.0, 0.3, -1.0, -1.0] * neurons,
                  [ 100.0, 9.9,  1.0,  1.0] * neurons)

for i in xrange(7):
    print "%s * exp( -((%s - x)^2 + (%s - y)^2)/(%s^2) ) + " % (l[4 * i], l[4 * i + 1], l[4 * i + 2], l[4 * i + 3])
