#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;
using u64 = uint64_t;

u64 const M = 1000000007;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 n, m;
    cin >> n >> m;

    vector<u32> x(n);
    for (auto& xi : x) cin >> xi;

    vector<vector<u64>> dp(n, vector<u64>(m+1));

    for (u32 i = 0; i < n; ++i) {
        for (u32 v = 1; v < m+1; ++v) {
            if (x[i] > 0 && v != x[i]) {
                dp[i][v] = 0;
            }
            else if (i == 0) {
                dp[i][v] = 1;
            }
            else {
                dp[i][v] = dp[i-1][v];
                if (v > 1) dp[i][v] = (dp[i][v] + dp[i-1][v-1]) % M;
                if (v < m) dp[i][v] = (dp[i][v] + dp[i-1][v+1]) % M;
            }
        }
    }

    u64 ans = 0;
    for (u32 v = 1; v < m+1; ++v) {
        ans = (ans + dp[n-1][v]) % M;
    }
    cout << ans << "\n";

    return 0;
}
