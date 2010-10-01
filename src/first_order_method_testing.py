# -*- coding: utf-8 -*0
from time import time

from __init__ import J_grad_wrap, to_minimize
from first_order_methods.rummelhart import rummelhart
from report import generate_report


t_start = time()
l = rummelhart([5] * 12, J_grad_wrap, to_minimize)
t_end = time()

generate_report(l, t_start, t_end)

print u"Готово"