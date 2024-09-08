def hanoi(n, a, b, c):
    if n == 1:
        return [(a, b)]
    return hanoi(n-1, a, c, b) + [(a, b)] + hanoi(n-1, c, b, a)

def solve(n):
    return hanoi(n, '1', '3', '2')

n = int(input())
moves = solve(n)
print(len(moves))
print('\n'.join(map(lambda m: f'{m[0]} {m[1]}', moves)))
