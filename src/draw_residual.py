import math

from pylab import arange, axis, colorbar, figure, legend, meshgrid, pcolor, \
    plot, show, title, xlabel, ylabel

from __init__ import network_from_list


print "Enter NN1"
NN1 = network_from_list(map(float, raw_input().split()))

print "Enter NN2"
NN2 = network_from_list(map(float, raw_input().split()))


def residual(x, y):
    c = []
    for j in xrange(len(x)):
        cur_c = []
        for i in xrange(len(x[j])):
            cur_x = x[j][i]
            cur_y = y[j][i]
            cur_c.append(math.fabs(NN1([cur_x, cur_y]) - 
                                   NN2([cur_x, cur_y])))
        c.append(cur_c)
    return c

dx, dy = 0.005, 0.005
ax = arange(0, 1.0001, dx)
ay = arange(0.0, 1.0001, dy)
X, Y = meshgrid(ax, ay)

Z = residual(X, Y)
figure(5)
pcolor(X, Y, Z)
colorbar()
axis([0,1,0,1])
show()