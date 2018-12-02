import sys

def count(arg, value):
    memo = {}

    for c in arg:
        if c in memo:
            memo[c] += 1
        else:
            memo[c] = 1

    return value in memo.values()

if __name__ == "__main__":
    cnt_two = 0
    cnt_three = 0

    for line in sys.stdin:
        if count(line, 2):
            cnt_two += 1
        if count(line, 3):
            cnt_three += 1

    print(cnt_two * cnt_three)
