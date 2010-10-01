import math
import operator
from random import random

from neuro import Neuron, NeuralNetwork


dimensions = 2
neurons = 3
delta = 1000.0

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
           
           
def J_grad(f, g, inside, borders, NN):
    def calculate_derivatives(neuron_number):
        neuron = NN.neurons[neuron_number]
        w = neuron.w
        a = neuron.a
        c = neuron.c
        
        def w_grad():
            return sum(map(lambda x:
                           2.0 * neuron.laplace(x) * (NN.laplace(x) - f(x)), inside)) + \
                   2.0 * delta * sum(map(lambda x: neuron(x) / w * (NN(x) - g(x)), borders))

        def a_grad():
            return sum(map(lambda x: 2.0 * (NN.laplace(x) - f(x)) *
                       ( 8.0 * neuron(x) * sum(map(lambda xc, cc: -math.pow(xc - cc, 2.0), x, c)) * (
                             a * a - sum(map(lambda xc, cc: math.pow(xc - cc, 2.0), x, c))
                         ) / math.pow(a, 7.0) -
                         16.0 * neuron(x) * sum(map(lambda xc, cc: math.pow(xc - cc, 2.0), x, c)) / math.pow(a, 5.0) +
                         8.0 * neuron(x) / math.pow(a, 3.0)
                       ), inside)) - \
                   4.0 * delta * sum(map(lambda x: neuron(x) * (NN(x) - g(x)) * 
                                             sum(map(lambda xc, cc: -math.pow(xc - cc, 2.0), x, c)) / math.pow(a, 3),
                                         borders))
                   
        def c_grad(index):
            return sum(map(lambda x:
                           2.0 * (NN.laplace(x) - f(x)) * 8.0 * neuron(x) * (
                               -2.0 * a * a * (x[index] - c[index]) +
                               math.pow(x[index] - c[index], 3.0) + 
                               (x[index] - c[index]) * math.pow(x[1 - index] - c[1 - index], 2.0)
                           ) / math.pow(a, 6.0), inner)) + \
                   4.0 * delta * sum(map(lambda x: neuron(x) * (NN(x) - g(x)) * (x[index] - c[index]) / math.pow(a, 2.0), borders))
            
        return [w_grad(), a_grad()] + map(c_grad, range(2))
    return reduce(operator.add, map(calculate_derivatives, range(neurons)))


def J_grad_wrap(l):
    return J_grad(f, g, inner, border, network_from_list(l))


def to_minimize(l):
    global current
    global inner
    global border
    nn = network_from_list(l)
    return J(f, g, inner, border, nn)


print J_grad(f, g, inner, border, network_from_list([5] * 12))