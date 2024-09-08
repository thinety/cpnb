from itertools import groupby

def solve(s):
    ans = 0
    for _, group in groupby(s):
        length = sum(1 for _ in group)
        ans = max(ans, length)
    return ans

s = input()
print(solve(s))
