#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 n;
    cin >> n;

    vector<u32> a(n), b(n);
    for (u32 i = 0; i < n; ++i) cin >> a[i] >> b[i];

    vector<u32> movies(n);
    iota(movies.begin(), movies.end(), 0);
    sort(movies.begin(), movies.end(), [&] (u32 i, u32 j) {
        return b[i] < b[j];
    });

    u32 last_seen = 0;
    u32 ans = 0;
    for (auto i : movies) {
        if (a[i] >= last_seen) {
            ans += 1;
            last_seen = b[i];
        }
    }
    cout << ans << "\n";

    return 0;
}
