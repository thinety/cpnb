struct VirtualTree {
    LowestCommonAncestor lca;
    vector<vector<u32>> virtual_tree;
    vector<u32> nodes;

    // O(N logN)
    void init(vector<vector<u32>> tree) {
        lca.init(move(tree), 0);
        virtual_tree.resize(lca.tree.size());
    }

    // O(K (logK + logN))
    // builds virtual tree with O(K) nodes
    u32 build(vector<u32> nodes_) {
        nodes = move(nodes_);

        u32 n = nodes.size();
        auto cmp = [&] (auto& u, auto& v) { return lca.tin[u] < lca.tin[v]; };

        sort(nodes.begin(), nodes.end(), cmp);

        nodes.resize(2*n-1);
        for (u32 i = 0; i < n-1; ++i) {
            nodes[n+i] = lca.lca(nodes[i], nodes[i+1]);
        }

        sort(nodes.begin(), nodes.end(), cmp);
        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

        n = nodes.size();

        vector<u32> stack;
        stack.push_back(nodes[0]);

        for (u32 i = 1; i < n; ++i) {
            u32 u = nodes[i];
            while (!lca.is_ancestor(stack.back(), u)) stack.pop_back();
            u32 p = stack.back();

            virtual_tree[u].push_back(p);
            virtual_tree[p].push_back(u);
            stack.push_back(u);
        }

        return nodes[0];
    }

    // O(K)
    void clear() {
        for (auto u : nodes) {
            virtual_tree[u].clear();
        }
        nodes.clear();
    }
};
