def solve(n):
    ans = []

    for k in range(1, n+1):
        if k == 1:
            """
            a
            """
            ans.append(0)
            continue

        if k == 2:
            """
            aa
            aa
            """
            ans.append(4*3//2)
            continue

        if k == 3:
            """
            aaa
            aba
            aaa
            """
            a = 8 * (3**2 - 1 - 2)
            b = 1 * (3**2 - 1)
            ans.append((a+b)//2)
            continue

        """
        abcc...ccba
        bcdd...ddcb
        cdee...eedc
        cdee...eedc
        ....   ....
        ....   ....
        ....   ....
        cdee...eedc
        cdee...eedc
        bcdd...ddcb
        abcc...ccba
        """
        a = 4 * 1 * (k**2 - 1 - 2)
        b = 4 * 2 * (k**2 - 1 - 3)
        c = 4 * (k-3) * (k**2 - 1 - 4)
        d = 4 * (k-4) * (k**2 - 1 - 6)
        e = (k-4)**2 * (k**2 - 1 - 8)

        ans.append((a+b+c+d+e)//2)

    return ans

n = int(input())
print(' '.join(map(str, solve(n))))
