# -*- coding: utf-8 -*-
import random
from time import time

from __init__ import J_grad_wrap, to_minimize
from first_order_methods.rummelhart import rummelhart
from first_order_methods.simulated_annealing import simulated_annealing
from report import generate_report


t_start = time()
l = simulated_annealing([random.uniform(2, 10) for i in range(12)], J_grad_wrap, to_minimize)
t_end = time()

generate_report(l, t_start, t_end)

print u"Готово"