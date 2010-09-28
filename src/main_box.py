# -*- coding: utf-8 -*-
import math
from os import mkdir
from random import random
from time import time

import matplotlib.pyplot as plot
from matplotlib.patches import Patch
from pylab import *

from estimate import make_quad_estimate
from complex_box import complex_box
from neuro import Neuron, NeuralNetwork
import neuro.draw


dimensions = 2
neurons = 3
delta = 100.0

current = []
inner = []
border = []


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

inner = [[random(), random()] for i in range(15)]
border = ([[0.0, random()] for i in range(25)] + 
          [[1.0, random()] for i in range(25)] + 
          [[random(), 0.0] for i in range(25)] + 
          [[random(), 1.0] for i in range(25)]) 


def to_minimize(l):
    global current
    global inner
    global border
    nn = network_from_list(l)
    current = l
    return J(f, g, inner, border, nn)

t_start = time()
try:
    l = complex_box(to_minimize, neurons * (2 + dimensions), 
                    [-250.0, 1.0, -2.0, -2.0] * neurons, 
                    [250.0, 10.0, 6.0, 6.0] * neurons)
except KeyboardInterrupt, e:
    l = current
t_end = time()
folder = "/tmp/" + str(int(t_end)) + "/"
mkdir(folder)

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
    print "(%s)*exp(-(((%s)-x)^2+((%s)-y)^2)/((%s)^2))+" % (l[ns * i], 
                            l[ns * i + 2], l[ns * i + 3], l[ns * i + 1]),
print "0)"
neuro.draw.draw(resulting_nn, (-3.0, -3.0, 7.0, 7.0), (0.0, 0.0, 1.0, 1.0), 
                folder + "cfg.png")

dx, dy = 0.005, 0.005
ax = arange(0, 1.0001, dx)
ay = arange(0.0, 1.0001, dy)
X, Y = meshgrid(ax, ay)

def residual(x, y):
    c = []
    for j in xrange(len(x)):
        cur_c = []
        for i in xrange(len(x[j])):
            cur_x = x[j][i]
            cur_y = y[j][i]
            cur_c.append(math.fabs(g([cur_x, cur_y]) - resulting_nn([cur_x, cur_y])))
        c.append(cur_c)
    return c

Z = residual(X, Y)
figure(5)
pcolor(X, Y, Z)
colorbar()
axis([0,1,0,1])
savefig(folder + "overall.png")

for c_y in xrange(3):
    y = c_y * 0.5
    xs = [0.01*x for x in range(100)]
    ys = [resulting_nn([x, y]) for x in xs]
    zs = [g([x, y]) for x in xs]
    figure(c_y)
    xlabel('$x$')
    ylabel('$y$')
    title(ur'Погрешность полученного решения в сечении $y = %.1f$' % y)
    plot(xs, ys, label=ur'полученное решение', color='red')    
    plot(xs, zs, label=ur'точное решение', color='green')    
    legend(loc='upper right')
    savefig(folder + "fig_%s.png" % c_y)
