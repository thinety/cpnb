#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;

struct CondensedDAG {
    vector<vector<u32>> graph;
    vector<vector<u32>> reverse_graph;
    vector<vector<u32>> dag;

    vector<u32> graph_to_dag;
    vector<vector<u32>> dag_to_graph;

    vector<u32> mark;
    vector<u32> order;

    void dfs1(u32 u) {
        mark[u] = 1;
        for (auto v : graph[u]) {
            if (mark[v] == 1) continue;
            dfs1(v);
        }
        order.push_back(u);
    }

    void dfs2(u32 u, u32 c) {
        mark[u] = 2;
        graph_to_dag[u] = c;
        dag_to_graph[c].push_back(u);
        for (auto v : reverse_graph[u]) {
            if (mark[v] == 2) continue;
            dfs2(v, c);
        }
    }

    void init(vector<vector<u32>> graph_, vector<vector<u32>> reverse_graph_)
    {
        graph = move(graph_);
        reverse_graph = move(reverse_graph_);

        u32 n = graph.size();

        graph_to_dag.resize(n);

        mark.resize(n, 0);

        for (u32 u = 0; u < n; ++u) {
            if (mark[u] == 1) continue;
            dfs1(u);
        }
        
        reverse(order.begin(), order.end());

        for (auto u : order) {
            if (mark[u] == 2) continue;
            u32 c = dag.size(); dag.emplace_back(); dag_to_graph.emplace_back();
            dfs2(u, c);
        }

        for (u32 u = 0; u < n; ++u) {
            for (auto v : graph[u]) {
                if (graph_to_dag[u] != graph_to_dag[v]) {
                    dag[graph_to_dag[u]].push_back(graph_to_dag[v]);
                }
            }
        }
    }
};

int main() {
    u32 N, M; cin >> N >> M;

    vector<vector<u32>> g(N), g_t(N);
    for (u32 e = 0; e < M; ++e) {
        u32 U, V; cin >> U >> V; U--, V--;
        g[U].push_back(V);
        g_t[V].push_back(U);
    }

    CondensedDAG cdag; cdag.init(g, g_t);
    u32 NN = cdag.dag.size();

    cout << "graph" << endl;
    for (u32 u = 0; u < N; ++u) {
        cout << "u=" << u+1 << ":";
        for (auto v : cdag.graph[u]) {
            cout << " " << v+1;
        }
        cout << endl;
    }
    cout << endl;

    cout << "graph_to_dag" << endl;
    for (auto c : cdag.graph_to_dag) {
        cout << c+1 << " ";
    }
    cout << endl;
    cout << endl;

    cout << "dag_to_graph" << endl;
    for (u32 u = 0; u < NN; ++u) {
        cout << "u=" << u+1 << ":";
        for (auto v : cdag.dag_to_graph[u]) {
            cout << " " << v+1;
        }
        cout << endl;
    }
    cout << endl;

    cout << "dag" << endl;
    for (u32 u = 0; u < NN; ++u) {
        cout << "u=" << u+1 << ":";
        for (auto v : cdag.dag[u]) {
            cout << " " << v+1;
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}
