#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from pylab import arange, axis, colorbar, figure, legend, meshgrid, pcolor, \
    plot, savefig, title, xlabel, ylabel, show

x = arange(0, 1.00000, 0.01)
f = open(sys.argv[1])

y1, y2, y3 = [map(float, line.split()) for line in f]

figure(1)
xlabel('$x$')
ylabel('$y$')
print len(x), len(y1)
plot(x, y1, label=ur'точное', color='green')
plot(x, y2, label=ur'прямое', color='orange')
plot(x, y3, label=ur'обратное', color='red')    
legend(loc='upper right')
show()
    
