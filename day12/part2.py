import sys

def calculate(state, offset):
    plant_indexes = [i - offset for i, j in enumerate(state) if j == '#']
    return sum(plant_indexes)

CYCLE_LEN = 100
CYCLE_CONST = 62
GENERATIONS = 50000000000

state = list(input().split(' ')[2].rstrip())
mapping = {}

for line in sys.stdin.readlines():
    splt = line.split(' ')
    slice_state, result = splt[0].rstrip(), splt[2].rstrip()

    mapping[slice_state] = result

offset = 0

for gen in range(CYCLE_LEN):
    state = ['.', '.', '.'] + state + ['.', '.', '.']
    offset += 3

    state_len = len(state)
    new_state = ['.' for _ in range(state_len)]

    for i in range(2 , state_len - 2):
        slice = ''.join(state[i-2:i+3])

        if slice in mapping:
            new_state[i] = mapping[slice]

    # clean borders
    while len(new_state) > 0 and new_state[0] == '.':
        offset -= 1
        new_state.pop(0)

    while len(new_state) > 0 and new_state[-1] == '.':
        new_state.pop()

    state = new_state

print((GENERATIONS - CYCLE_LEN) * CYCLE_CONST + calculate(state, offset))
