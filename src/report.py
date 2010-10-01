import math
from os.path import abspath, dirname, join
from time import time

from src import network_from_list, f, g


report_dir = join(dirname(dirname(abspath(__file__))), "reports")


def generate_report(l):
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
    folder = join(report_dir, str(time()))
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