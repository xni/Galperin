from pylab import *

file = open(raw_input("Enter filename: "), "r")

colours = {"1": "red", "6": "green", "11": "yellow", "16": "blue", "21": "black", "26": "gray"}

x = []
y = []
s = []
c = []

fig = figure()

for line in file:
    _, _, neurons, inner, border, delta, J, E = line.split()
    x.append(int(inner) + 4 * int(border) * int(delta))
    y.append(float(E))
    c.append(colours[neurons])
    
scatter(x, y, s=25, c=c)

show()
