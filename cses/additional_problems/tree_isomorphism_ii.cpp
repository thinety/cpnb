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

u32 n;
vector<vector<u32>> g;

vector<u32> sz;
u32 dfs(u32 p, u32 u) {
    sz[u] = 1;
    for (auto v : g[u]) {
        if (v == p) continue;
        sz[u] += dfs(u, v);
    }
    return sz[u];
}
u32 centroid(u32 p, u32 u) {
    for (auto v : g[u]) {
        if (v == p) continue;
        if (2*sz[v] >= n) return centroid(u, v);
    }
    return u;
}

u32 ahu(u32 p, u32 u) {
    vector<u32> cur;
    for (auto v : g[u]) {
        if (v == p) continue;
        cur.emplace_back(ahu(u, v));
    }
    return hsh(cur);
}

void solve() {
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

    sz.assign(n, 0);
    dfs(0, 0);
    u32 c1 = centroid(0, 0);
    u32 h1 = ahu(c1, c1);

    g.assign(n, {});
    for (u32 e = 0; e < n-1; ++e) {
        u32 u, v;
        cin >> u >> v;
        u--, v--;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    dfs(0, 0);
    u32 c2 = centroid(0, 0);
    u32 h2 = ahu(c2, c2);
    if (h1 == h2) {
        cout << "YES\n";
        return;
    }

    dfs(c2, c2);
    c2 = centroid(c2, c2);
    h2 = ahu(c2, c2);
    if (h1 == h2) {
        cout << "YES\n";
        return;
    }

    cout << "NO\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 t;
    cin >> t;
    while (t--) solve();

    return 0;
}
