"""
Advent of Code 2018 - Day 09 solution.
"""

from collections import deque

INPUT = input().split(' ')

PLAYERS = int(INPUT[0])
MARBLES = int(INPUT[6])

circle = deque([0])
players_score = [0 for _ in range(PLAYERS)]

for marble in range(1, MARBLES + 1):
    current_player = (marble - 1) % PLAYERS

    if marble % 23 != 0:
        circle.rotate(-1)
        circle.append(marble)
    else:
        players_score[current_player] += marble
        circle.rotate(7)
        players_score[current_player] += circle.pop()
        circle.rotate(-1)

print(max(players_score))
