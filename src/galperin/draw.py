# -*- coding: utf-8 -*-
from PIL import Image, ImageDraw

def create_image(filename, X, Y, Z):
    i = Image.new("RGB", [100, 100])
    d = ImageDraw.Draw(i)
    for cube in X:
	    print [tuple(cube.left()), tuple(cube.right())]
	    d.rectangle([tuple(cube.left()), tuple(cube.right())], fill=255)
    for cube in Y:
	    d.rectangle([tuple(cube.left()), tuple(cube.right())], fill=255 * 256)
    for cube in Z:
	    d.rectangle([tuple(cube.left()), tuple(cube.right())], fill=255 * 256 * 256)
    i.save(filename, "BMP")