def solve(xs):
    ans = 0
    largest = xs[0]
    for x in xs[1:]:
        ans += max(0, largest - x)
        largest = max(largest, x)
    return ans

n = int(input())
xs = list(map(int, input().split()))
print(solve(xs))
