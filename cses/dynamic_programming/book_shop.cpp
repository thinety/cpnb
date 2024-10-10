#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 n, x;
    cin >> n >> x;

    vector<u32> h(n), s(n);
    for (auto& hi : h) cin >> hi;
    for (auto& si : s) cin >> si;

    // knapsack
    vector<vector<u32>> dp(n+1, vector<u32>(x+1));
    for (u32 i = 0; i < n+1; ++i) {
        for (u32 k = 0; k < x+1; ++k) {
            if (i == 0) {
                dp[i][k] = 0;
                continue;
            }

            dp[i][k] = dp[i-1][k];
            if (h[i-1] <= k) dp[i][k] = max(dp[i][k], dp[i-1][k-h[i-1]] + s[i-1]);
        }
    }

    cout << dp[n][x] << "\n";

    return 0;
}
