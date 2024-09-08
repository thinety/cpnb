def solve(n):
    if n == 1:
        return [1]
    if n < 4:
        return None
    even = [x for x in range(n, 0, -1) if x % 2 == 0]
    odd = [x for x in range(n, 0, -1) if x % 2 == 1]
    return odd + even

n = int(input())
ans = solve(n)
print(' '.join(map(str, ans)) if ans else "NO SOLUTION")
