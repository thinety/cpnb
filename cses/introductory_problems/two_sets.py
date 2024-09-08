def solve(n):
    s = (n+1)*n // 2
    if s % 2 == 1:
        return

    target = s//2
    sum1 = 0
    s1 = []
    sum2 = 0
    s2 = []
    for x in range(n, 0, -1):
        if sum1 + x <= target:
            sum1 += x
            s1.append(x)
        else:
            sum2 += x
            s2.append(x)

    assert(sum(s1) == target)
    assert(sum(s2) == target)

    return s1, s2

n = int(input())
ans = solve(n)
if ans:
    print("YES")
    s1, s2 = ans
    print(len(s1))
    print(' '.join(map(str, s1)))
    print(len(s2))
    print(' '.join(map(str, s2)))
else:
    print("NO")
