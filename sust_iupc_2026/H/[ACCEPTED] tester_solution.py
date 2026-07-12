t = int(input())
for _ in range(t):
    s = input()
    n = len(s)
    all_same = True
    for i in range(1, n):
        all_same = all_same and (s[i] == s[i - 1])
    if all_same:
        print(0)
    else:
        print(n + n - 2)