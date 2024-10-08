#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;

vector<set<u32>> g;

vector<u32> euler;

void dfs(u32 u) {
    while (g[u].size() > 0) {
        u32 v = *g[u].begin();
        g[u].erase(v);
        dfs(v);
    }
    euler.push_back(u);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 n, m;
    cin >> n >> m;

    g.resize(n);
    vector<u32> indeg(n, 0);
    for (u32 e = 0; e < m; ++e) {
        u32 a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace(b);
        indeg[b] += 1;
    }

    u32 start = 0, end = n-1;

    bool ok = true;
    for (u32 u = 0; u < n; ++u) {
        if (u == start) {
            ok &= g[u].size() == indeg[u] + 1;
        }
        else if (u == end) {
            ok &= g[u].size() + 1 == indeg[u];
        }
        else {
            ok &= g[u].size() == indeg[u];
        }
    }

    if (!ok) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    dfs(start);
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
