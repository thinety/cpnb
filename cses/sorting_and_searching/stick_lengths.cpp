#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;
using u64 = int64_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 n;
    cin >> n;

    vector<u64> p(n);
    for (auto& pi : p) cin >> pi;

    sort(p.begin(), p.end());

    u64 final = p[n/2]; // median

    u64 ans = 0;
    for (auto pi : p) {
        if (pi > final) ans += pi - final;
        else ans += final - pi;
    }
    cout << ans << "\n";

    return 0;
}
