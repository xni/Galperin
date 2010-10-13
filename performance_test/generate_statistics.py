"""
Утилита для генерации статистики по лог-файлам.

Рекомендуемый формат использования:
    ls log*.dat | python generate_statistics.py
"""

import string
import sys

files = sys.stdin.read().strip().split('\n')

print "{0:<20} | {1:>10} | {2:>10} | {3:>10} | {4:>10}".format('filename', 'min_val', 'max_val', 'avg', 'max_prob')

for filename in files:
    with open(filename, "r") as file:
        data = {}
        for (line_num, line) in enumerate(file):
            if line_num % 2 != 0:
                continue
            c = float(line)
            data[c] = data.get(c, 0) + 1
        min_val = min(data.keys())
        max_val = max(data.keys())
        avg = sum(map(lambda (k, v): k * v, data.items())) / sum(data.values())
        max_prob = reduce(lambda (k, v), (nk, nv): (k, v) if v >= nv else (nk, nv), data.items())[0]
        print "{0:<20} | {1:>10} | {2:>10} | {3:>10} | {4:>10}".format(filename, min_val, max_val, avg, max_prob)
