#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 n;
    cin >> n;

    vector<tuple<u32, bool>> events;
    for (u32 i = 0; i < n; ++i) {
        u32 a, b;
        cin >> a >> b;
        events.emplace_back(a, true);
        events.emplace_back(b, false);
    }

    sort(events.begin(), events.end());

    u32 total = 0, ans = 0;
    for (auto [_, arriving] : events) {
        if (arriving) total += 1;
        else total -= 1;
        ans = max(ans, total);
    }

    cout << ans << "\n";

    return 0;
}
