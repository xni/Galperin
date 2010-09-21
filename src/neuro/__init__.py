# -*- coding: utf-8 -*-

import math


class Neuron(object):
    def __init__(self, w, a, c):
        self.w, self.a, self.c = w, a, c

    def __call__(self, point):
        distance = sum(map(lambda x, y: (x - y) ** 2, point, self.c))
        return self.w * math.exp(-1.0 * distance / (self.a ** 2))
    
    def laplace(self, point):
        return sum(map(lambda x, y: -2.0 * self(point) / (self.a ** 2) + 
                                    4.0 * self(point) * ((x - y) ** 2) / 
                                          (self.a ** 4), point, self.c))


class NeuralNetwork(object):
    def __init__(self, neurons):
        self.neurons = neurons
    
    def __call__(self, point):
        return sum(map(lambda neuron: neuron(point), self.neurons))
    
    def laplace(self, point):
        return sum(map(lambda neuron: neuron.laplace(point), self.neurons))

