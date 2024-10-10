#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 n, m;
    cin >> n >> m;

    vector<u32> h(n), t(m);
    for (auto& hi : h) cin >> hi;
    for (auto& ti : t) cin >> ti;

    multiset<u32> h_sorted(h.begin(), h.end());

    for (auto ti : t) {
        auto it = h_sorted.upper_bound(ti);
        if (it == h_sorted.begin()) cout << "-1\n";
        else {
            it = prev(it);
            cout << *it << "\n";
            h_sorted.erase(it);
        }
    }

    return 0;
}
