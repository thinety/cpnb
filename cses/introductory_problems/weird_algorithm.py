def solve(n):
    x = n
    ans = [x]
    while x > 1:
        if x % 2 == 0:
            x = x//2;
        else:
            x = 3*x + 1
        ans.append(x)
    return ans

n = int(input())
ans = solve(n)
print(' '.join(map(str, ans)))
