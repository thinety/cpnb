#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;

struct BridgeTree {
    vector<vector<u32>> graph;
    vector<vector<u32>> tree;

    vector<u32> graph_to_tree;
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

                low[u] = min(low[u], low[v]);
            }
            else if (v != p) { // descendant or ascendent (except parent)
                low[u] = min(low[u], tin[v]);
            }
        }

        if (low[u] == tin[u]) {
            u32 c = tree.size(); tree.emplace_back(); tree_to_graph.emplace_back();

            while (true) {
                u32 x = stack.back(); stack.pop_back();
                graph_to_tree[x] = c;
                tree_to_graph[c].push_back(x);
                if (x == u) break;
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
            for (auto v : graph[u]) {
                if (graph_to_tree[u] != graph_to_tree[v]) { // bridge
                    tree[graph_to_tree[u]].push_back(graph_to_tree[v]);
                }
            }
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 n, m;
    cin >> n >> m;

    vector<tuple<u32, u32>> edges;
    vector<vector<u32>> g(n);
    for (u32 i = 0; i < m; ++i) {
        u32 a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
        edges.emplace_back(a, b);
    }

    BridgeTree bt; bt.init(move(g));

    vector<tuple<u32, u32>> bridges;
    for (auto [a, b] : edges) {
        if (bt.graph_to_tree[a] != bt.graph_to_tree[b]) {
            bridges.emplace_back(a, b);
        }
    }

    cout << bridges.size() << "\n";
    for (auto [a, b] : bridges) {
        cout << a+1 << " " << b+1 << "\n";
    }

    return 0;
}
