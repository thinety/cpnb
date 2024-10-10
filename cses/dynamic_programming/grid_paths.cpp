#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;
using u64 = uint64_t;

u64 const M = 1000000007;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 n;
    cin >> n;

    vector<vector<char>> grid(n, vector<char>(n));
    for (u32 i = 0; i < n; ++i) {
        for (u32 j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }

    vector<vector<u64>> dp(n, vector<u64>(n));
    for (u32 i = 0; i < n; ++i) {
        for (u32 j = 0; j < n; ++j) {
            if (grid[i][j] == '*') {
                dp[i][j] = 0;
                continue;
            }

            if (i == 0 && j == 0) {
                dp[i][j] = 1;
                continue;
            }

            if (i > 0) {
                dp[i][j] = (dp[i][j] + dp[i-1][j]) % M;
            }
            if (j > 0) {
                dp[i][j] = (dp[i][j] + dp[i][j-1]) % M;
            }
        }
    }
    cout << dp[n-1][n-1] << "\n";

    return 0;
}
