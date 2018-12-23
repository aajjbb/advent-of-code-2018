"""
Advent of Code 2018 - Day 20
"""

from collections import deque

INF = 10**10

ROWS = 600
COLS = 600
START_X = 300
START_Y = 300

DX = {'N': -1, 'E': 0, 'S': +1, 'W':  0}
DY = {'N':  0, 'E': 1, 'S':  0, 'W': -1}

DOOR = {
    'N': '-',
    'S': '-',
    'W': '|',
    'E': '|',
}

def process_regex(regex):
    """
    Receives the problem's regex string
    and creates a maze as described in
    the statement.
    """
    x, y = START_X, START_Y
    pos_history = []

    board = [['#' for c in range(COLS)] for r in range(ROWS)]
    board[x][y] = 'X'

    for char in regex[1:-1]:
        if char == '(':
            pos_history.append((x, y))
        elif char == ')':
            x, y = pos_history.pop()
        elif char == '|':
            x, y = pos_history[-1]
        else:
            x += DX[char]
            y += DY[char]

            board[x][y] = DOOR[char]

            x += DX[char]
            y += DY[char]

            board[x][y] = '.'

    return board

def inside(x, y):
    """
    Checks whether (x, y) lies
    inside the board.
    """
    return min(x, y) >= 0 and x < ROWS and y < COLS

def shortest_path(board, x, y):
    dist = [[INF for c in range(COLS)] for r in range(ROWS)]
    q = deque()

    ans = 0

    dist[x][y] = 0
    q.append((x, y))

    while len(q) > 0:
        cx, cy = q.pop()

        ans = max(ans, dist[cx][cy])

        for direction in 'NEWS':
            nx = cx + DX[direction]
            ny = cy + DY[direction]

            if not inside(nx, ny) or (board[nx][ny] not in '-|'):
                continue

            nx += DX[direction]
            ny += DY[direction]

            if not inside(nx, ny) or board[nx][ny] != '.':
                continue

            if dist[nx][ny] > dist[cx][cy] + 1:
                dist[nx][ny] = dist[cx][cy] + 1
                q.append((nx, ny))

    return ans

if __name__ == "__main__":
    regex = str(input())
    maze = process_regex(regex)

    print(shortest_path(maze, START_X, START_Y))
