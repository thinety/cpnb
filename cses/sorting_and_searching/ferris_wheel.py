def solve(p, x):
    n = len(p)
    p = sorted(p)

    ans = 0
    i = 0
    j = n
    while i < j:
        ans += 1
        if p[i] + p[j-1] <= x:
            i += 1
            j -= 1
        else:
            j -= 1

    return ans

n, x = map(int, input().split())
p = list(map(int, input().split()))
print(solve(p, x))
