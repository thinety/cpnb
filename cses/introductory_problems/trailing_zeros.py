def solve(n):
    count_2 = 0
    pow_2 = 2
    while pow_2 <= n:
        count_2 += n // pow_2
        pow_2 *= 2

    count_5 = 0
    pow_5 = 5
    while pow_5 <= n:
        count_5 += n // pow_5
        pow_5 *= 5

    return min(count_2, count_5)

n = int(input())
print(solve(n))
