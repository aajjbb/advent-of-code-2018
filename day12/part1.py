import sys

GENERATIONS = 500
HALO_SIZE = 50

state = list(input().split(' ')[2].rstrip())
mapping = {}

for line in sys.stdin.readlines():
    splt = line.split(' ')
    slice_state, result = splt[0].rstrip(), splt[2].rstrip()

    mapping[slice_state] = result

# add halo

state = ['.' for _ in range(HALO_SIZE)] + state + ['.' for _ in range(HALO_SIZE)]

states_set = set()

for gen in range(GENERATIONS):
    state_len = len(state)
    new_state = ['.' for _ in range(state_len)]

    for i in range(2 , state_len - 2):
        slice = ''.join(state[i-2:i+3])

        if slice in mapping:
            new_state[i] = mapping[slice]


    state_as_string = str(new_state)

    if state_as_string in states_set:
        print(gen)
        break

    states_set.add(state_as_string)

    state = new_state

plant_indexes = [i - HALO_SIZE for i, j in enumerate(state) if j == '#']
print(plant_indexes)
print(sum(plant_indexes))
