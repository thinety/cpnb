#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;
using u64 = uint64_t;

u64 const M = 1000000007;

u64 solve(u32 x, vector<u32> const& c) {
    u32 n = c.size();

    vector<vector<u64>> dp(2, vector<u64>(x+1));

    for (u32 i = 0; i < n; ++i) {
        for (u32 v = 0; v < x+1; ++v) {
            if (v > 0) {
                if (i > 0) {
                    dp[i%2][v] = dp[(i-1)%2][v];
                }
                else {
                    dp[i%2][v] = 0;
                }

                if (v >= c[i]) {
                    dp[i%2][v] = (dp[i%2][v] + dp[i%2][v-c[i]]) % M;
                }
            }
            else {
                dp[i%2][v] = 1;
            }
        }
    }

    return dp[(n-1)%2][x];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 n, x;
    cin >> n >> x;

    vector<u32> c(n);
    for (auto& ci : c) cin >> ci;

    cout << solve(x, c) << "\n";

    return 0;
}
