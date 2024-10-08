#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;

vector<set<u32>> g;

vector<u32> euler;

void dfs(u32 u) {
    while (g[u].size() > 0) {
        u32 v = *g[u].begin();
        g[u].erase(v);
        g[v].erase(u);
        dfs(v);
    }
    euler.push_back(u);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 n, m;
    cin >> n >> m;

    g.resize(n);
    for (u32 e = 0; e < m; ++e) {
        u32 a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace(b);
        g[b].emplace(a);
    }

    bool ok = true;
    for (u32 u = 0; u < n; ++u) {
        ok &= g[u].size() % 2 == 0;
    }

    if (!ok) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    dfs(0);
    reverse(euler.begin(), euler.end());

    if (euler.size() < m+1) {
        // graph is disconnected
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (u32 i = 0; i < m+1; ++i) {
        cout << euler[i]+1 << " \n"[i+1==m+1];
    }

    return 0;
}
