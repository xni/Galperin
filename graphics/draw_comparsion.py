#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Скрипт для генерации сравнительных отчетов для разных методов решения
"""
from __future__ import division
import sys
from pylab import *
import math


class RBFGaussLoader(object):
    Identifier = "RBF-Gauss"

    def __init__(self, file_iter):
        self.data = []
        for line in file_iter:
            self.data.append(map(float, line.strip().split()))

    def get_value(self, x, y):
        res = 0.0
        for w, a, c_x, c_y in self.data:
            d_x = c_x - x
            d_y = c_y - y
            res += w * math.exp(- (d_x * d_x + d_y * d_y) / (a * a))
        return res


class RBFMQLoader(object):
    Identifier = "RBF-MQ"

    def __init__(self, file_iter):
        self.data = []
        for line in file_iter:
            self.data.append(map(float, line.strip().split()))

    def get_value(self, x, y):
        res = 0.0
        for w, a, c_x, c_y in self.data:
            d_x = c_x - x
            d_y = c_y - y
            res += w * math.sqrt(d_x * d_x + d_y * d_y + a * a)
        return res

class RBFIndirectMQLoader(object):
    Identifier = "RBF-INDIRECT-MQ"

    def __init__(self, file_iter):
        self.data = []
        for line in file_iter:
            self.data.append(map(float, line.strip().split()))

    def get_value(self, x, y):
        self.n = 10
        self.p = 5
        res = 0.0
        for w, a, c_x, c_y in self.data[0 : self.n]:
            d_x = x - c_x
            d_y = y - c_y
            r2 = d_x * d_x + d_y * d_y
            a2 = a * a
            res += w * (math.pow((r2 + a2), 1.5) / 6.0 + \
              0.5 * (r2 - d_x * d_x + a2) * (d_x * math.log(d_x + math.sqrt(r2 + a2)) - math.sqrt(r2 + a2)))
        for w, a, c_x, c_y in self.data[self.n * 2 : self.n * 2 + self.p]:
            d_x = c_x - x
            d_y = c_y - y
            res += x * (w * math.sqrt(d_x * d_x + d_y * d_y + a * a))
        for w, a, c_x, c_y in self.data[self.n * 2 + self.p : self.n * 2 + self.p * 2]:
            d_x = c_x - x
            d_y = c_y - y
            res += w * math.sqrt(d_x * d_x + d_y * d_y + a * a)
        return res


class GridLoader(object):
    Identifier = "Grid"

    def __init__(self, file_iter):
        self.left_x, self.right_x, self.bottom_y, self.top_y = map(
            float, file_iter.next().strip().split())
        
        self.data = []
        for line in file_iter:
            self.data.append(map(float, line.strip().split()))

        self.step_x = (self.right_x - self.left_x) / (len(self.data[0]) - 1)
        self.step_y = (self.top_y - self.bottom_y) / (len(self.data) - 1)

        self.data.reverse()
        print "Loaded data: %sx%s" % (len(self.data[0]), len(self.data))

    def get_value(self, x, y):
        q_top = int(math.ceil(y / self.step_y))
        q_bottom = int(math.floor(y / self.step_y))
        q_left = int(math.floor(x / self.step_x))
        q_right = int(math.ceil(x / self.step_x))

        if q_top >= len(self.data):
            q_top = len(self.data) - 1
        if q_right >= len(self.data[0]):
            q_right = len(self.data[0]) - 1

        if (q_top == q_bottom) and (q_left == q_right):
            return self.data[q_top][q_left]

        if (q_top == q_bottom):
            return self.data[q_top][q_left] + (x - q_left * self.step_x) / self.step_x * (
                self.data[q_top][q_right] - self.data[q_top][q_left])

        if (q_left == q_right):
            return self.data[q_bottom][q_left] + (y - q_bottom * self.step_y) \
                / self.step_y * (self.data[q_top][q_left] - self.data[q_bottom][q_left])

        y_interpolation_left = (self.data[q_bottom][q_left] +
            (y - q_bottom * self.step_y) / self.step_y * (self.data[q_top][q_left] -
                                                       self.data[q_bottom][q_left]))
        y_interpolation_right = (self.data[q_bottom][q_right] +
            (y - q_bottom * self.step_y) / self.step_y * (self.data[q_top][q_right] -
                                                       self.data[q_bottom][q_right]))
        interpolation = (y_interpolation_left +
                         (x - q_left * self.step_x) / self.step_x * (
                y_interpolation_right - y_interpolation_left))
        return interpolation


class Exact(object):
    Identifier = "Exact"

    def __init__(self):
        pass

    #def get_value(self, x, y):
    #    return x*x - y*y

    def get_value(self, x, y):
        return -1.0 * math.sin(math.pi * x) * math.sin(math.pi * y) / (
            2.0 * math.pi * math.pi)


def draw_two_value_maps(interpreter1, interpreter2):
    x = arange(0.0, 1.00001, 0.025)
    y = arange(0.0, 1.00001, 0.025)
    X, Y = meshgrid(x, y)
    
    interpreter3 = Exact()

    R1 = []
    R2 = []
    R3 = []
    for i in xrange(len(X)):
        p1 = []
        p2 = []
        p3 = []
        R1.append(p1)
        R2.append(p2)
        R3.append(p3)
        for j in xrange(len(X[0])):
            p1.append(interpreter1.get_value(X[i][j], Y[i][j]))
            p2.append(interpreter2.get_value(X[i][j], Y[i][j]))
            p3.append(interpreter3.get_value(X[i][j], Y[i][j]))

    figure(1)
    im1 = imshow(R1, cmap=cm.jet)
    im1.set_interpolation('bilinear')
    colorbar()

    figure(2)
    im2 = imshow(R2, cmap=cm.jet)
    im2.set_interpolation('bilinear')
    colorbar()
    
    figure(3)
    im3 = imshow(R3, cmap=cm.jet)
    im3.set_interpolation('bilinear')
    colorbar()

    show()


def draw_diff_map(interpreter1, interpreter2):
    x = arange(0.0, 1.00001, 0.025)
    y = arange(0.0, 1.00001, 0.025)
    X, Y = meshgrid(x, y)

    R1 = []
    for i in xrange(len(X)):
        p1 = []
        R1.append(p1)
        for j in xrange(len(X[0])):
            p1.append(math.fabs(interpreter1.get_value(X[i][j], Y[i][j]) -
                                interpreter2.get_value(X[i][j], Y[i][j])))

    figure(1)
    im1 = imshow(R1, cmap=cm.jet)
    im1.set_interpolation('bilinear')
    colorbar()

    show()


def get_x_section(interpreter1, interpreter2):
    x = float(raw_input("Input x=const: ").strip())
    y = arange(0.0, 1.0001, 0.025)
    interpreter3 = Exact()
    i1 = [interpreter1.get_value(x, y_i) for y_i in y]
    i2 = [interpreter2.get_value(x, y_i) for y_i in y]
    i3 = [interpreter3.get_value(x, y_i) for y_i in y]
    figure(1)
    xlabel('$x$')
    ylabel('$y$')
    title(ur'Сравнение сечений функций плоскостью $x = %.1f$' % x)
    plot(y, i1, label=interpreter1.Identifier, color='red')    
    plot(y, i2, label=interpreter2.Identifier, color='green')
    plot(y, i3, label=interpreter3.Identifier, color='blue')
    legend(loc='upper right')
    show()


def get_y_section(interpreter1, interpreter2):
    y = float(raw_input("Input y=const: ").strip())
    x = arange(0.0, 1.0001, 0.025)
    interpreter3 = Exact()
    i1 = [interpreter1.get_value(x_i, y) for x_i in x]
    i2 = [interpreter2.get_value(x_i, y) for x_i in x]
    i3 = [interpreter3.get_value(x_i, y) for x_i in x]
    figure(1)
    xlabel('$x$')
    ylabel('$y$')
    title(ur'Сравнение сечений функций плоскостью $y = %.1f$' % y)
    plot(x, i1, label=interpreter1.Identifier, color='red')    
    plot(x, i2, label=interpreter2.Identifier, color='green')
    plot(x, i3, label=interpreter3.Identifier, color='blue')    
    legend(loc='upper right')
    show()
    

def get_interpretator(filename):
    file_iter = iter(open(filename, "r"))
    loaders = [RBFGaussLoader, RBFMQLoader, RBFIndirectMQLoader, GridLoader]
    interpreter = file_iter.next().strip()
    return filter(lambda cl: cl.Identifier == interpreter,
                  loaders)[0](file_iter)
   
    
filename1 = raw_input("Enter path to first file: ")
filename2 = raw_input("Enter path to second file: ")

interpretators = map(get_interpretator, (filename1, filename2))

commands = {"1": lambda: draw_two_value_maps(*interpretators),
            "2": lambda: get_x_section(*interpretators),
            "3": lambda: get_y_section(*interpretators),
            "4": lambda: draw_diff_map(*interpretators),
            "0": sys.exit}

while True:
    print """Menu
------------------------------------------
 1. For two comparsion graphics
 2. For x=const section
 3. For y=const section
 4. For draw diff map
 0. For exiting"""

    command = raw_input("Your choise: ")
    commands[command.strip()]()
