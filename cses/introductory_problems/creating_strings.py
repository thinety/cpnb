from itertools import groupby

def go(m):
    ans = []
    for c, k in m.items():
        if k == 0: continue
        m[c] -= 1
        ans.extend(c + s for s in go(m))
        m[c] += 1
    if len(ans) == 0:
        ans = ['']
    return ans

def solve(s):
    m = {c: sum(1 for _ in group) for c, group in groupby(sorted(s))}
    return go(m)

s = input()
ans = solve(s)
print(len(ans))
print('\n'.join(ans))
