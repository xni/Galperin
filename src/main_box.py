# -*- coding: utf-8 -*-
from time import time

from __init__ import to_minimize, neurons, dimensions, J_grad_wrap
from complex_box import complex_box
from first_order_methods.simulated_annealing import simulated_annealing
from report import generate_report


t_start = time()
l = complex_box(to_minimize, neurons * (2 + dimensions), 
                [-250.0, 1.0, -2.0, -2.0] * neurons, 
                [250.0, 10.0, 6.0, 6.0] * neurons)
l = simulated_annealing(l, J_grad_wrap, to_minimize)
t_end = time()


generate_report(l, t_start, t_end)

print u"Готово"