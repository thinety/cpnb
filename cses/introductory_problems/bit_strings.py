M = 1000000007

def solve(n):
    return pow(2, n, M)

n = int(input())
print(solve(n))
