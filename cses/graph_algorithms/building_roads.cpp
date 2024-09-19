#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;

vector<vector<u32>> g;

vector<bool> visited;
void dfs(u32 u) {
    visited[u] = true;
    for (auto v : g[u]) {
        if (visited[v]) continue;
        dfs(v);
    }
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
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }

    visited.resize(n, false);

    vector<u32> nodes;
    for (u32 u = 0; u < n; ++u) {
        if (visited[u]) continue;
        dfs(u);
        nodes.emplace_back(u);
    }

    cout << nodes.size()-1 << "\n";;
    for (u32 i = 1; i < nodes.size(); ++i) {
        cout << nodes[i-1]+1 << " " << nodes[i]+1 << "\n";
    }

    return 0;
}
