#!/usr/bin/env python
"""
See pcolor_demo2 for a much faster way of generating pcolor plots
"""
from __future__ import division
from pylab import *


size = int(raw_input())


# make these smaller to increase the resolution
dx = 1.0 / (size - 1)
dy = dx

x = arange(0.0, 1.00001, dx)
y = arange(0.0, 1.00001, dy)
X,Y = meshgrid(x, y)


R = []
for i in xrange(size):
    p = []
    R.append(p)
    for j in xrange(size):
        p.append(float(raw_input().split()[-1]))

ax = subplot(111)
im = imshow(R, cmap=cm.jet)
#im.set_interpolation('nearest')
#im.set_interpolation('bicubic')
im.set_interpolation('bilinear')
#ax.set_image_extent(-3, 3, -3, 3)
colorbar()
show()
