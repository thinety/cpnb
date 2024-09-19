#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;
using u64 = uint64_t;

u64 const M = 1000000007;

u64 binexp(u64 a, u64 b) {
    if (b == 0) return 1;
    if (b & 1) return (a * binexp(a, b-1)) % M;
    auto x = binexp(a, b/2);
    return (x * x) % M;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 n;
    cin >> n;

    while (n--) {
        u64 a, b;
        cin >> a >> b;
        cout << binexp(a, b) << "\n";
    }

    return 0;
}
