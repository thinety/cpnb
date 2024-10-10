#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;
using i64 = int64_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 n;
    cin >> n;

    vector<i64> x(n);
    for (u32 i = 0; i < n; ++i) cin >> x[i];

    vector<i64> psx(n+1);
    psx[0] = 0;
    for (u32 i = 0; i < n; ++i) psx[i+1] = psx[i] + x[i];

    i64 smallest = psx[0];
    i64 ans = psx[1] - smallest;
    for (u32 i = 2; i < n+1; ++i) {
        smallest = min(smallest, psx[i-1]);
        ans = max(ans, psx[i] - smallest);
    }

    cout << ans << "\n";

    return 0;
}
