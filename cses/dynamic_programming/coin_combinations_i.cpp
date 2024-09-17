#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;
using u64 = uint64_t;

u64 const M = 1000000007;

u64 solve(u32 x, vector<u32> const& c) {
    u32 n = c.size();

    vector<u64> dp(x+1);

    for (u32 v = 0; v < x+1; ++v) {
        if (v > 0) {
            dp[v] = 0;
            for (u32 i = 0; i < n; ++i) {
                if (v >= c[i]) {
                    dp[v] = (dp[v] + dp[v-c[i]]) % M;
                }
            }
        }
        else {
            dp[v] = 1;
        }
    }

    return dp[x];
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
