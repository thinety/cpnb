#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;
using u64 = uint64_t;

u64 const M = 1000000007;

u64 binexp(u64 a, u64 b, u64 m) {
    if (b == 0) return 1;
    if (b & 1) return (a * binexp(a, b-1, m)) % m;
    auto x = binexp(a, b/2, m);
    return (x * x) % m;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 n;
    cin >> n;

    while (n--) {
        u64 a, b, c;
        cin >> a >> b >> c;
        cout << binexp(a, binexp(b, c, M-1), M) << "\n";
    }

    return 0;
}
