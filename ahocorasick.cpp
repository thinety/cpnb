struct AhoCorasick {
    using Char = char;
    using Word = string;

    struct Node {
        map<Char, u32> next;
        u32 word;
        u32 suffix;
        u32 output;
    };

    vector<Node> node;

    void build(vector<Word> const& words) {
        // root
        node.emplace_back();
        node.back().word = -1;

        for (u32 w = 0; w < words.size(); ++w) {
            u32 u = 0;
            for (auto c : words[w]) {
                if (node[u].next.count(c) == 0) {
                    node[u].next.emplace(c, node.size());
                    node.emplace_back();
                    node.back().word = -1;
                }
                u = node[u].next[c];
            }
            node[u].word = w;
        }

        deque<u32> queue;

        node[0].suffix = -1;
        node[0].output = -1;
        queue.emplace_back(0);

        while (queue.size() > 0) {
            u32 u = queue.front(); queue.pop_front();

            for (auto [c, v] : node[u].next) {
                u32 suffix = node[u].suffix;
                while (suffix != -1 && node[suffix].next.count(c) == 0) suffix = node[suffix].suffix;
                if (suffix != -1) node[v].suffix = node[suffix].next[c];
                else node[v].suffix = 0;

                u32 output = node[v].suffix;
                if (node[output].word != -1) node[v].output = output;
                else node[v].output = node[output].output;

                queue.emplace_back(v);
            }
        }
    }

    u32 go(u32 u, Char c) {
        while (u != -1 && node[u].next.count(c) == 0) u = node[u].suffix;
        if (u != -1) u = node[u].next[c];
        else u = 0;
        return u;
    }

    template <typename F>
    void foreach_word(u32 u, F f) {
        if (node[u].word != -1) f(node[u].word);
        u = node[u].output;
        while (u != -1) {
            f(node[u].word);
            u = node[u].output;
        }
    }
};
