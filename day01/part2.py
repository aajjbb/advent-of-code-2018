import sys

if __name__ == "__main__":

    sign_list = []
    number_list = []

    for line in sys.stdin:
        sign = line[0]
        number = int(line[1:])

        sign_list.append(sign)
        number_list.append(number)

    pos, freq = 0, 0
    length = len(sign_list)
    memo = set()

    while True:
        if sign_list[pos] == '+':
            freq += number_list[pos]
        else:
            freq -= number_list[pos]

        if freq in memo:
            break

        memo.add(freq)

        pos = (pos + 1) % length


    print(freq)