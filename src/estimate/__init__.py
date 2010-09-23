# -*- coding: utf-8 -*-

import math


def make_quad_estimate(NN, solution, left, bottom, right, top, dx, dy):
    """
    Только для двумера. Импортируем сетко-генератор из Галперина прям скоро-прескоро
    """
    res = 0.0
    cur_x = left
    while cur_x <= right:
        cur_y = bottom
        while cur_y <= top:
            res += math.pow(NN([cur_x, cur_y]) - solution([cur_x, cur_y]), 2.0)
            cur_y += dy
        cur_x += dx
    return math.sqrt(res)