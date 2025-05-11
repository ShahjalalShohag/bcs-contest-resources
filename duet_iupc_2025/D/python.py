import sys

def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    idx = 1
    out = []
    for _ in range(t):
        n = int(data[idx]); idx += 1
        s = data[idx]; idx += 1
        # A string is interesting iff all characters are distinct
        out.append("YES" if len(set(s)) == len(s) else "NO")
    sys.stdout.write("\n".join(out))

if __name__ == "__main__":
    main()
