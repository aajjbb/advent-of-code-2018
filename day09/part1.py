"""
Advent of Code 2018 - Day 09 solution.
"""

INPUT = input().split(' ')

PLAYERS = int(INPUT[0])
MARBLES = int(INPUT[6])

circle = [0]
current_pos = 0
players_score = [0 for _ in range(PLAYERS)]

for marble in range(1, MARBLES + 1):
    current_player = (marble - 1) % PLAYERS

    if marble % 23 != 0:
        new_position = 1 + (current_pos + 1) % (len(circle))
        circle.insert(new_position, marble)
        current_pos = new_position
    else:
        players_score[current_player] += marble
        removed_position = (current_pos - 7 + len(circle)) % len(circle)
        players_score[current_player] += circle[removed_position]
        circle.pop(removed_position)
        current_pos = removed_position

print(max(players_score))
