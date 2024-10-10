#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;
using u64 = uint64_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 n;
    cin >> n;

    vector<u64> x(n);
    for (auto& xi : x) cin >> xi;

    sort(x.begin(), x.end());

    u64 last = 0;
    for (u32 i = 0; i < n; ++i) {
        if (x[i] > last+1) break;
        last += x[i];
    }
    cout << last+1 << "\n";

    return 0;
}
