from itertools import groupby

def solve(s):
    ans = []
    middle = ''

    for c, group in groupby(sorted(s)):
        k = sum(1 for _ in group)
        if k % 2 == 1:
            if middle != '':
                return "NO SOLUTION"
            middle = c
            k -= 1
        ans.extend([c] * (k//2))

    return ''.join(ans) + middle + ''.join(reversed(ans))

s = input()
print(solve(s))
