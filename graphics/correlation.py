#!/usr/bin/python
import sys

from pylab import *

x = []
y = []

for line in sys.stdin:
    xi, yi = map(float, line.split())
    x.append(xi)
    y.append(yi)

figure(1)
scatter(x, y, s=1)
show()
