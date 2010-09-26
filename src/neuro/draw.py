# -*- coding: utf-8 -*-

from PIL import Image, ImageDraw

def draw(NN, box, filename):
    NN.neurons.sort(key = lambda n: -n.a)
    i = Image.new("RGB", [1000, 1000])
    d = ImageDraw.Draw(i)
    l, t, r, b = box
    d.rectangle((0, 0, 1000, 1000), fill=256 * 256 * 256 - 1)
    for n in NN.neurons:
        x_s = n.center[0]
        y_s = n.center[1]
        x_raw = 1000.0 * (x_s - l) / (l - r)
        y_raw = 1000.0 - 1000.0 * (y_s - t) / (b - t)
        r = 1000.0 * n.a / (r - l)
        d.ellipse((x_raw - r, y_raw - r, x_raw + r, y_raw + r), outline=0)
    i.save(filename, "PNG")