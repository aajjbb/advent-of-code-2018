"""
Advent of Code 2018 - Day 10 part 1 solution.
"""

import re
import sys

INF = 10*1000
MAP_ROW = 10
MAP_COL = 63

DATA = [map(int, re.findall(r'-?\d+', i)) for i in sys.stdin.readlines()]

# Defined by hand by watching the visualization

pos_x = []
pos_y = []
vel_x = []
vel_y = []

global_dist = INF
ideal_it = 0

for x, y, vx, vy, in DATA:
    pos_x.append(x)
    pos_y.append(y)
    vel_x.append(vx)
    vel_y.append(vy)

point_len = len(pos_x)

# Find the ideal iteration with brute_force
for it in range(10000, 12000):
    min_x = +INF
    max_x = -INF
    min_y = +INF
    max_y = -INF

    for i in range(point_len):
        pt = (
            pos_x[i] + it * vel_x[i],
            pos_y[i] + it * vel_y[i]
        )

        min_x = min(min_x, pt[0])
        max_x = max(max_x, pt[0])
        min_y = min(min_y, pt[1])
        max_y = max(max_y, pt[1])

    dist = (max_x - min_x + 1) + (max_y - min_y + 1)

    if dist < global_dist:
        global_dist = dist
        ideal_it = it

min_x = INF
min_y = INF

for i in range(point_len):
    pos_x[i] += ideal_it * vel_x[i]
    pos_y[i] += ideal_it * vel_y[i]

    min_x = min(min_x, pos_x[i])
    min_y = min(min_y, pos_y[i])

char_map = [[ '.' for col in range(MAP_COL)] for row in range(MAP_ROW)]

print(ideal_it)

for i in range(point_len):
    char_map[pos_y[i] - min_y][pos_x[i] - min_x] = '#'

for row in range(MAP_ROW):
    for col in range(MAP_COL):
        print(char_map[row][col], end='')
    print()
