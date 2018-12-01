import sys

if __name__ == "__main__":
    freq = 0

    for line in sys.stdin:
        sign = line[0]
        number = int(line[1:])

        if sign == '+':
            freq += number
        else:
            freq -= number

    print(freq)