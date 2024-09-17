def solve(k, a, b):
    n = len(a)
    m = len(b)

    a = sorted(a)
    b = sorted(b)

    ans = 0
    i = 0
    j = 0
    while i < n and j < m:
        if a[i] + k < b[j]:
            i += 1
        elif b[j] < a[i] - k:
            j += 1
        else:
            ans += 1
            i += 1
            j += 1

    return ans

n, m, k = map(int, input().split())
a = list(map(int, input().split()))
b = list(map(int, input().split()))
print(solve(k, a, b))
