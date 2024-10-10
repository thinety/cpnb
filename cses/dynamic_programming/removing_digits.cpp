#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 n;
    cin >> n;

    vector<u32> dp(n+1);
    dp[0] = 0;
    for (u32 x = 1; x < n+1; ++x) {
        dp[x] = -1;
        u32 y = x;
        while (y > 0) {
            if (y%10 > 0) dp[x] = min(dp[x], dp[x-y%10]+1);
            y /= 10;
        }
    }

    cout << dp[n] << "\n";

    return 0;
}
