#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 n, m;
    cin >> n >> m;

    vector<vector<u32>> g(n);
    for (u32 e = 0; e < m; ++e) {
        u32 a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }

    vector<bool> visited(n, false);
    vector<u32> prev(n);
    deque<u32> queue;

    visited[n-1] = true;
    prev[n-1] = n-1;
    queue.emplace_back(n-1);

    while (queue.size() > 0) {
        auto u = queue.front(); queue.pop_front();
        for (auto v : g[u]) {
            if (visited[v]) continue;
            visited[v] = true;
            prev[v] = u;
            queue.emplace_back(v);
        }
    }

    if (!visited[0]) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<u32> ans;
    u32 u = 0;
    while (u != n-1) {
        ans.emplace_back(u);
        u = prev[u];
    }
    ans.emplace_back(u);

    cout << ans.size() << "\n";
    for (u32 i = 0; i < ans.size(); ++i) {
        cout << ans[i]+1 << " \n"[i+1==ans.size()];
    }

    return 0;
}
