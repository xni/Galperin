# -*- coding: utf-8 -*-

from PIL import Image, ImageDraw

def draw(NN, box, area, filename):
    NN.neurons.sort(key = lambda n: -n.a)
    i = Image.new("RGB", [1000, 1000])
    d = ImageDraw.Draw(i)
    l, b, r, t = box
    l1, b1, r1, t1 = area
    d.rectangle((0, 0, 1000, 1000), fill="#7f7f7f")
    for ll in xrange(int(l), int(r+1)):
        x_raw = 1000.0 * (ll - l) / (r - l)
        d.line((x_raw, 0.0, x_raw, 1000.0), fill="#cccccc")
    for ll in xrange(int(b), int(t+1)):
        y_raw = 1000.0 * (ll - t) / (b - t)
        d.line((0.0, y_raw, 1000.0, y_raw), fill="#cccccc")

    for n in NN.neurons:
        x_s = n.c[0]
        y_s = n.c[1]
        x_raw = 1000.0 * (x_s - l) / (r - l)
        y_raw = 1000.0 * (t - y_s) / (t - b)
        rad = 1000.0 * n.a / (r - l)
        color = int((n.w + 250) / 500.0 * 255)
        d.ellipse((x_raw - rad, y_raw - rad, x_raw + rad, y_raw + rad), fill=(color, color, color), outline=0)
        
    for n in NN.neurons:
        x_s = n.c[0]
        y_s = n.c[1]
        x_raw = 1000.0 * (x_s - l) / (r - l)
        y_raw = 1000.0 * (t - y_s) / (t - b)
        rad = 2
        d.ellipse((x_raw - rad, y_raw - rad, x_raw + rad, y_raw + rad), fill=0)
        
    x_raw = 1000.0 * (l1 - l) / (r - l)
    y_raw = 1000.0 * (t - t1) / (t - b)
    r_raw = 1000.0 * (r1 - l1) / (r - l)
    d.rectangle((x_raw, y_raw, x_raw + r_raw, y_raw + r_raw), outline="#000000")
    
    i.save(filename, "PNG")