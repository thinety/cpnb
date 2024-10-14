#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;

struct BlockCutTree {
    vector<vector<u32>> graph;
    vector<vector<u32>> tree;

    vector<vector<u32>> graph_to_tree;
    vector<vector<u32>> tree_to_graph;

    u32 t;
    vector<u32> tin;
    vector<u32> low;
    vector<u32> stack;

    void dfs(int u, int p) {
        tin[u] = t++;
        low[u] = tin[u];
        stack.push_back(u);

        for (auto v : graph[u]) {
            if (tin[v] == -1) { // child
                dfs(v, u);

                if (low[v] >= tin[u]) {
                    u32 c = tree.size(); tree.emplace_back(); tree_to_graph.emplace_back();

                    while (true) {
                        u32 x = stack.back(); stack.pop_back();
                        graph_to_tree[x].push_back(c);
                        tree_to_graph[c].push_back(x);
                        if (x == v) break;
                    }

                    graph_to_tree[u].push_back(c);
                    tree_to_graph[c].push_back(u);
                }

                low[u] = min(low[u], low[v]);
            }
            else if (v != p) { // descendant or ascendent (except parent)
                low[u] = min(low[u], tin[v]);
            }
        }
    }

    void init(vector<vector<u32>> graph_)
    {
        graph = move(graph_);
        u32 n = graph.size();

        graph_to_tree.resize(n);

        t = 0;
        tin.resize(n, -1);
        low.resize(n);

        for (u32 u = 0; u < n; ++u) {
            if (tin[u] != -1) continue;
            dfs(u, u);
        }

        for (u32 u = 0; u < n; ++u) {
            if (graph_to_tree[u].size() > 1) { // articulation point
                u32 c = tree.size(); tree.emplace_back(); tree_to_graph.emplace_back();

                for (auto v : graph_to_tree[u]) {
                    tree[c].push_back(v);
                    tree[v].push_back(c);
                }

                graph_to_tree[u].push_back(c);
                tree_to_graph[c].push_back(u);
            }
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 n, m;
    cin >> n >> m;

    vector<vector<u32>> g(n);
    for (u32 i = 0; i < m; ++i) {
        u32 a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }

    BlockCutTree bct; bct.init(move(g));

    vector<u32> articulation_points;
    for (u32 u = 0; u < n; ++u) {
        if (bct.graph_to_tree[u].size() > 1) articulation_points.emplace_back(u);
    }

    u32 k = articulation_points.size();
    cout << k << "\n";
    for (u32 i = 0; i < k; ++i) {
        cout << articulation_points[i]+1 << " \n"[i+1==k];
    }

    return 0;
}
