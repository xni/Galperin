#!/usr/bin/python
import sys
from math import sqrt, log

from pylab import arange, axis, colorbar, figure, legend, meshgrid, pcolor, \
    plot, savefig, title, xlabel, ylabel, show, errorbar

d = {}
x = []
y = []
y_bar = []

def stats(l):
    v1 = min(l)
    v2 = max(l)

    avg = sum(l) / len(l)
    disp = sqrt(sum(map(lambda x: (x - avg)**2, l)) / len(l))
    return disp, avg

for line in sys.stdin:
    neurons, val = map(float, line.strip().split())
    if neurons not in d:
        d[neurons] = []
#    d[neurons].append(log(val))
    d[neurons].append(val)

for k, v in d.items():
    x.append(k)
    ybi, yi = stats(v)
    y.append(yi)
    y_bar.append(ybi)

figure(1)
errorbar(x, y, yerr=y_bar, fmt="o")
savefig(sys.argv[1])
