#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 n;
    cin >> n;

    vector<u32> x(n);
    for (auto& xi : x) cin >> xi;

    vector<u32> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&] (u32 i, u32 j) {
        return x[i] < x[j];
    });

    u32 ans = 1;
    for (u32 i = 1; i < n; ++i) {
        if (idx[i] < idx[i-1]) ans += 1;
    }
    cout << ans << "\n";

    return 0;
}
