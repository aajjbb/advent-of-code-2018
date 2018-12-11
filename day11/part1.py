SERIAL = int(input())

ROW_CNT = 301
COL_CNT = 301

def calculate_power(r, c, serial):
    rack_id = r + 10
    start = rack_id * c
    digit = ((start + serial) * rack_id // 100) % 10
    return digit - 5

best_sum = 0
top_r = 0
top_c = 0

grid = [[0 for c in range(COL_CNT)] for r in range(ROW_CNT)]

for r in range(1, ROW_CNT):
    for c in range(1, COL_CNT):
        grid[r][c] = calculate_power(r, c, SERIAL)

        if r - 2 >= 1 and c - 2 >= 1:
            local_sum = 0

            for r_sub in range(3):
                for c_sub in range(3):
                    local_sum += grid[r - r_sub][c - c_sub]

            if best_sum < local_sum:
                best_sum = local_sum
                top_r = r - 2
                top_c = c - 2

print(top_r, top_c, best_sum)
