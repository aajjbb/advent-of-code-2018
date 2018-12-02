import sys

def diff(arg_a, arg_b):
    if len(arg_a) != len(arg_b):
        raise ValueError()

    diff_count = 0

    for i in range(len(arg_a)):
        if arg_a[i] != arg_b[i]:
            diff_count += 1

    return diff_count

if __name__ == "__main__":
    line_list = []
    final_id_a = ""
    final_id_b = ""
    id_diff = ""

    for line in sys.stdin:
        line_list.append(line)

    for i in range(len(line_list)):
        for j in range(i):
            if diff(line_list[i], line_list[j]) == 1:
                final_id_a = line_list[i]
                final_id_b = line_list[j]

    for i in range(len(final_id_a)):
        if final_id_a[i] == final_id_b[i]:
            id_diff += final_id_a[i]

    print(id_diff)
