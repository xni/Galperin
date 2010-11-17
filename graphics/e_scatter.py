from pylab import *

file = open(raw_input("Enter filename: "), "r")

colours = {"1": "red", "6": "green", "11": "yellow", "16": "blue", "21": "green", "26": "red", "31": "orange", "36": "pink", "41": "white", "46": "brown"}

x = []
y = []
s = []
c = []

fig = figure()

for line in file:
    _, _, neurons, inner, border, delta, J, E = line.split()
#    if float(E) > 10000: continue
    if neurons != "31": continue
    if delta == "1000": continue
#    c = "red" if delta == "1" else "green"
#    if neurons == "1": continue
    x.append(float(inner) / (float(delta) * float(border) * 4.0))
#    x.append(int(inner))
#    x.append(int(border))
#    if delta == "1":
#        col = "red"
#        x.append(float(border) + 5)
#    else:
#        col = "green"
#        x.append(float(border))
    y.append(float(E))
#    c.append(col)
#    c.append(colours[neurons])
    
scatter(x, y, s=1, c=c)

show()
