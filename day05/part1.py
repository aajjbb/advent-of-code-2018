import sys

def reacts(ua, ub):
    return ua != ub and ua.lower() == ub.lower()

def process(seq):
    n = len(seq)

    for i in range(n - 1):
        if reacts(seq[i], seq[i + 1]):
            return process(seq[:i] + seq[i + 2:])

    return len(seq)

if __name__ == "__main__":
    sys.setrecursionlimit(100500)

    seq = str(input())

    print(process(seq))
