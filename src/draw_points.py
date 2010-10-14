import numpy as np            
from pylab import figure, show

data = map(float, raw_input().split())
x = map(lambda i: data[i], xrange(0, len(data), 2))
y = map(lambda i: data[i], xrange(1, len(data), 2))

fig = figure(facecolor='white')
ax = fig.add_subplot(111, frame_on=False)
ax.axison = False
ax.plot(x, y, 'd', markersize=8, markerfacecolor='blue')

show()

