#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;
using u64 = uint64_t;

u64 const M = 1000000007;

u64 solve(u32 n) {
    vector<u64> dp(n+1);
    dp[0] = 1;
    for (u32 i = 0; i < n+1; ++i) {
        for (u32 j = 1; j < min(7U, i+1); ++j) {
            dp[i] = (dp[i] + dp[i-j]) % M;
        }
    }
    return dp[n];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 n; cin >> n;
    cout << solve(n) << "\n";

    return 0;
}
