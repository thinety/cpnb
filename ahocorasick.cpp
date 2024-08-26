struct AhoCorasick {
    using Char = char;
    using Word = string;

    struct Node {
        map<Char, u32> next;
        u32 word;
        u32 suffix;
        u32 output;
    };

    vector<Node> nodes;

    void build(vector<Word> const& words) {
        // root
        nodes.emplace_back();
        nodes.back().word = -1;

        for (u32 w = 0; w < words.size(); ++w) {
            u32 u = 0;
            for (auto c : words[w]) {
                if (nodes[u].next.count(c) == 0) {
                    nodes[u].next.emplace(c, nodes.size());
                    nodes.emplace_back();
                    nodes.back().word = -1;
                }
                u = nodes[u].next[c];
            }
            nodes[u].word = w;
        }

        deque<u32> queue;

        nodes[0].suffix = -1;
        nodes[0].output = -1;
        queue.emplace_back(0);

        while (queue.size() > 0) {
            u32 u = queue.front(); queue.pop_front();

            for (auto [c, v] : nodes[u].next) {
                u32 suffix = nodes[u].suffix;
                while (suffix != -1 && nodes[suffix].next.count(c) == 0) suffix = nodes[suffix].suffix;
                if (suffix != -1) nodes[v].suffix = nodes[suffix].next[c];
                else nodes[v].suffix = 0;

                u32 output = nodes[v].suffix;
                if (nodes[output].word != -1) nodes[v].output = output;
                else nodes[v].output = nodes[output].output;

                queue.emplace_back(v);
            }
        }
    }

    u32 go(u32 u, Char c) {
        while (u != -1 && nodes[u].next.count(c) == 0) u = nodes[u].suffix;
        if (u != -1) u = nodes[u].next[c];
        else u = 0;
        return u;
    }

    template <typename F>
    void foreach_word(u32 u, F f) {
        if (nodes[u].word != -1) f(nodes[u].word);
        u = nodes[u].output;
        while (u != -1) {
            f(nodes[u].word);
            u = nodes[u].output;
        }
    }
};
