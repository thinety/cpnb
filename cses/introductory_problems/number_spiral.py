def solve(y, x):
    layer = max(y, x)
    if layer % 2 == 0:
        pos = y + layer - x
    else:
        pos = x + layer - y
    return (layer-1)**2 + pos

t = int(input())
for _ in range(t):
    y, x = map(int, input().split())
    print(solve(y, x))
