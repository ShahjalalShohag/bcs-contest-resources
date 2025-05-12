import sys

input = sys.stdin.readline
tt = int(input())
for _ in range(tt):
    n = int(input())
    s = input()
    a = s.count('A')
    b = s.count('B')
    if a == 0 and b == 0:
        print(2)
    elif a > 0 and b > 0:
        print(1)
    else:
        print(a + b)

