from itertools import groupby

def solve(xs):
    return sum(1 for _ in groupby(sorted(xs)))

n = int(input())
xs = map(int, input().split())
print(solve(xs))
