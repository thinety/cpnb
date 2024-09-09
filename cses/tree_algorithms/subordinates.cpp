#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;

u32 n;

vector<vector<u32>> g;
vector<u32> p;

vector<u32> subordinates;
void dfs(u32 u) {
    for (auto v : g[u]) {
        dfs(v);
        subordinates[u] += subordinates[v] + 1;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    g.resize(n);
    p.resize(n); p[0] = 0;
    for (u32 u = 1; u < n; ++u) {
        u32 pu; cin >> pu; pu--;
        g[pu].push_back(u);
        p[u] = pu;
    }

    subordinates.resize(n, 0);
    dfs(0);

    for (u32 u = 0; u < n; ++u) {
        cout << subordinates[u] << " \n"[u==n-1];
    }

    return 0;
}
