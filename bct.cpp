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
    u32 N, M; cin >> N >> M;

    vector<vector<u32>> g(N);
    for (u32 e = 0; e < M; ++e) {
        u32 U, V; cin >> U >> V; U--, V--;
        g[U].push_back(V);
        g[V].push_back(U);
    }

    BlockCutTree bct; bct.init(g);
    u32 NN = bct.tree.size();

    cout << "graph" << endl;
    for (u32 u = 0; u < N; ++u) {
        cout << "u=" << u+1 << ":";
        for (auto v : bct.graph[u]) {
            cout << " " << v+1;
        }
        cout << endl;
    }
    cout << endl;

    cout << "graph_to_tree" << endl;
    for (u32 u = 0; u < N; ++u) {
        cout << "u=" << u+1 << ":";
        for (auto v : bct.graph_to_tree[u]) {
            cout << " " << v+1;
        }
        cout << endl;
    }
    cout << endl;

    cout << "tree_to_graph" << endl;
    for (u32 u = 0; u < NN; ++u) {
        cout << "u=" << u+1 << ":";
        for (auto v : bct.tree_to_graph[u]) {
            cout << " " << v+1;
        }
        cout << endl;
    }
    cout << endl;

    cout << "tree" << endl;
    for (u32 u = 0; u < NN; ++u) {
        cout << "u=" << u+1 << ":";
        for (auto v : bct.tree[u]) {
            cout << " " << v+1;
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}
