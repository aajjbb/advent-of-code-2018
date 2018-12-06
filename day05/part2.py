from string import ascii_uppercase

def reacts(ua, ub):
    return ua != ub and ua.lower() == ub.lower()

def process(seq):
    while True:
        n = len(seq)
        found = False

        for i in range(n - 1):
            if reacts(seq[i], seq[i + 1]):
                seq = seq[:i] + seq[i + 2:]
                found = True
                break

        if not found:
            break

    return len(seq)

if __name__ == "__main__":
    seq = str(input())
    best_len = 10*10000

    for c in ascii_uppercase:
        new_seq = seq.replace(c, '').replace(c.lower(), '')

        best_len = min(best_len, process(new_seq))

    print(best_len)
