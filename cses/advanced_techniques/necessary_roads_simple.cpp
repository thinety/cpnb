#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;

vector<vector<u32>> g;

vector<u32> lvl;
vector<u32> p;
vector<u32> dp; // how many edges pass over the edge p[u] - u

void dfs(u32 u) {
    dp[u] = 0;
    for (auto v : g[u]) {
        if (lvl[v] == 0) { // child
            lvl[v] = lvl[u]+1;
            p[v] = u;
            dfs(v);
            dp[u] += dp[v];
        }
        else if (v != p[u]) { // descendant or ascendent (except parent)
            assert(lvl[u] != lvl[v]);
            if (lvl[u] < lvl[v]) dp[u] -= 1;
            else dp[u] += 1;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 n, m;
    cin >> n >> m;

    g.resize(n);
    for (u32 i = 0; i < m; ++i) {
        u32 a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }

    lvl.resize(n, 0);
    p.resize(n);
    dp.resize(n);

    lvl[0] = 1;
    p[0] = 0;
    dfs(0);

    vector<tuple<u32, u32>> bridges;
    for (u32 u = 1; u < n; ++u) {
        if (dp[u] == 0) bridges.emplace_back(p[u], u);
    }

    cout << bridges.size() << "\n";
    for (auto [a, b] : bridges) {
        cout << a+1 << " " << b+1 << "\n";
    }

    return 0;
}
