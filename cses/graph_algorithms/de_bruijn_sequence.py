from itertools import product

import sys
sys.setrecursionlimit(1000000)

def de_bruijn(alphabet, n):
    g = {}
    for u in product(alphabet, repeat=n-1):
        g[u] = set()
        for c in alphabet:
            v = (u + (c,))[1:]
            g[u].add((c, v))

    start = [alphabet[0]] * (n-1)

    euler = []
    def dfs(u):
        while len(g[u]) > 0:
            c, v = g[u].pop()
            dfs(v)
            euler.append(c)
    dfs(tuple(start))

    return start + euler[::-1]

n = int(input())
print(''.join(de_bruijn(['0', '1'], n)))
