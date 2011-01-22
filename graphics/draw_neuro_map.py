# -*- coding: utf-8 -*-

from PIL import Image, ImageDraw

W_MIN = -1000
W_MAX = 1000

CX_MIN = -3
CX_MAX = 3
CY_MIN = -3
CY_MAX = 3

AREA_LEFT = 0
AREA_RIGHT = 1
AREA_BOTTOM = 0
AREA_TOP = 1

data = [[1, 2, 1, 1], [1, 2, 1, 0], [1, 2, 0, 1], [1, 2, 0, 0]]

data.sort(key=lambda x: -x[1])
i = Image.new("RGB", [1000, 1000])
d = ImageDraw.Draw(i)

d.rectangle((0, 0, 1000, 1000), fill="#7f7f7f")

for n in data:
    x_s = n[2]
    y_s = n[3]
    x_raw = 1000.0 * (x_s - CX_MIN) / (CX_MAX - CX_MIN)
    y_raw = 1000.0 * (CY_MAX - y_s) / (CY_MAX - CY_MIN)
    rad = 1000.0 * n[1] / (CX_MAX - CX_MIN)
    color = int(float(n[0] - W_MIN) / (W_MAX - W_MIN) * 255)
    d.ellipse((x_raw - rad, y_raw - rad, x_raw + rad, y_raw + rad), fill=(color, color, color), outline=0)
        
for n in data:
    x_s = n[2]
    y_s = n[3]
    x_raw = 1000.0 * (x_s - CX_MIN) / (CX_MAX - CX_MIN)
    y_raw = 1000.0 * (CY_MAX - y_s) / (CY_MAX - CY_MIN)
    rad = 2
    d.ellipse((x_raw - rad, y_raw - rad, x_raw + rad, y_raw + rad), fill=0)
        
x_raw = 1000.0 * (AREA_LEFT - CX_MIN) / (CX_MAX - CX_MIN)
y_raw = 1000.0 * (CY_MAX - AREA_TOP) / (CY_MAX - CY_MIN)
r_raw = 1000.0 * (AREA_RIGHT - AREA_LEFT) / (CX_MAX - CX_MIN)
d.rectangle((x_raw, y_raw, x_raw + r_raw, y_raw + r_raw), outline="#000000")
    
i.save("/tmp/1.png", "PNG")
