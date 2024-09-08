def solve(n):
    if n == 1:
        return ['0', '1']
    gray = solve(n-1)
    return ['0'+c for c in gray] + ['1'+c for c in reversed(gray)]

n = int(input())
print('\n'.join(solve(n)))
