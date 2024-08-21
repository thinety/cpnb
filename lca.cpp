struct LowestCommonAncestor {
    vector<vector<u32>> tree;
    u32 l;

    u32 t;
    vector<u32> tin, tout;
    vector<vector<u32>> up;

    // O(N logN)
    void init(vector<vector<u32>> tree_, u32 root) {
        tree = move(tree_);
        u32 n = tree.size();

        // ceil(log2(n))
        l = 0; for (u32 x = 1; x < n;) { l += 1; x *= 2; }
        l = max(l, 1u);

        t = 0;
        tin.resize(n);
        tout.resize(n);
        up.resize(n, vector<u32>(l));

        dfs(root, root);
    }

    void dfs(u32 u, u32 p) {
        up[u][0] = p;
        for (u32 i = 1; i < l; ++i) {
            up[u][i] = up[up[u][i-1]][i-1];
        }

        tin[u] = t++;
        for (auto v : tree[u]) {
            if (v == p) continue;
            dfs(v, u);
        }
        tout[u] = t++;
    }

    // O(logN)
    u32 lca(u32 u, u32 v) {
        if (is_ancestor(u, v)) return u;
        if (is_ancestor(v, u)) return v;

        for (u32 i = l; i > 0;) { --i;
            if (is_ancestor(up[u][i], v)) continue;
            u = up[u][i];
        }

        return up[u][0];
    }

    // O(1)
    bool is_ancestor(u32 u, u32 v) {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }
};
