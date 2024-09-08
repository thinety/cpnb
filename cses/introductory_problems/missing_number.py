def solve(n, xs):
    seen = [False]*n
    for x in xs:
        seen[x-1] = True
    for i in range(n):
        if not seen[i]: return i+1
    raise

n = int(input())
xs = map(int, input().split())
print(solve(n, xs))
