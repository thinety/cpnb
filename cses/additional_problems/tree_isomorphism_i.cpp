#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;
using i32 = int32_t;
using u64 = uint64_t;
using i64 = int64_t;

map<vector<u32>, u32> h;
u32 hsh(vector<u32>& vec) {
    sort(vec.begin(), vec.end());
    if (h.count(vec) == 0) h[vec] = h.size();
    return h[vec];
}

vector<vector<u32>> g;
u32 ahu(u32 p, u32 u) {
    vector<u32> cur;
    for (auto v : g[u]) {
        if (v == p) continue;
        cur.emplace_back(ahu(u, v));
    }
    return hsh(cur);
}

void solve() {
    u32 n;
    cin >> n;

    h.clear();

    g.assign(n, {});
    for (u32 e = 0; e < n-1; ++e) {
        u32 u, v;
        cin >> u >> v;
        u--, v--;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    u32 h1 = ahu(0, 0);

    g.assign(n, {});
    for (u32 e = 0; e < n-1; ++e) {
        u32 u, v;
        cin >> u >> v;
        u--, v--;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    u32 h2 = ahu(0, 0);

    if (h1 == h2) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 t;
    cin >> t;
    while (t--) solve();

    return 0;
}
