def solve(a, b):
    a, b = min(a, b), max(a, b)

    k = min(b - a, a)
    a -= k
    b -= 2*k

    return a == b and a % 3 == 0


t = int(input())
for _ in range(t):
    a, b = map(int, input().split())
    print("YES" if solve(a, b) else "NO")
