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
best_size = 0

grid = [[0 for c in range(COL_CNT)] for r in range(ROW_CNT)]
rsum = [[0 for c in range(COL_CNT)] for r in range(ROW_CNT)]

for r in range(1, ROW_CNT):
    for c in range(1, COL_CNT):
        grid[r][c] = calculate_power(r, c, SERIAL)
        rsum[r][c] = rsum[r][c - 1] + grid[r][c]
for cl in range(1, COL_CNT):
    for cr in range(cl, COL_CNT):
        size = cr - cl + 1
        local_sum = 0

        for r in range(1, ROW_CNT):
            local_sum += rsum[r][cr] - rsum[r][cl - 1]

            if r - size >= 1:
                local_sum -= rsum[r - size][cr] - rsum[r - size][cl - 1]

            if r >= size and best_sum < local_sum:
                best_sum = local_sum
                top_r = r - size + 1
                top_c = cl
                best_size = size

print(top_r, top_c, best_size, best_sum)
