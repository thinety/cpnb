#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;

struct SuffixAutomaton {
    using Char = char;
    using Word = string;

    struct State {
        map<Char, u32> next;
        u32 link;
        u32 len;
        vector<u32> link_t;
        vector<u32> prefix, suffix;
    };

    vector<State> state;

    u32 split(u32 p, u32 q, Char c) {
        u32 clone = state.size();
        state.emplace_back();

        state[clone].next = state[q].next;
        state[clone].link = state[q].link;
        state[clone].len = state[p].len + 1;

        state[q].link = clone;

        while (state[p].next[c] == q) {
            state[p].next[c] = clone;
            p = state[p].link;
        }

        return clone;
    }

    u32 update(u32 last, Char c) {
        if (state[last].next.count(c) > 0) {
            u32 curr = state[last].next[c];
            if (state[curr].len > state[last].len + 1) curr = split(last, curr, c);
            return curr;
        }

        u32 curr = state.size();
        state.emplace_back();

        u32 p = last;
        while (state[p].next.count(c) == 0) {
            state[p].next[c] = curr;
            p = state[p].link;
        }

        u32 q = state[p].next[c];
        if (q == curr) q = 0;
        else if (state[q].len > state[p].len + 1) q = split(p, q, c);

        state[curr].link = q;
        state[curr].len = state[last].len + 1;

        return curr;
    }

    void build(vector<Word> const& word) {
        u32 n = word.size();

        // root
        state.emplace_back();
        state[0].link = 0;
        state[0].len = 0;

        for (u32 i = 0; i < n; ++i) {
            u32 last = 0;
            for (auto c : word[i]) {
                last = update(last, c);
            }
        }

        // root points to itself, so start at t=1
        for (u32 t = 1; t < state.size(); ++t) {
            state[state[t].link].link_t.emplace_back(t);
        }

        for (u32 i = 0; i < n; ++i) {
            u32 t = 0;
            for (auto c : word[i]) {
                t = state[t].next[c];
                state[t].prefix.emplace_back(i);
            }
            while (t != 0) {
                state[t].suffix.emplace_back(i);
                t = state[t].link;
            }
        }
    }

    vector<u32> index, length;
    vector<bool> visited;
    vector<u32> first, jump, last;

    void dfs(u32 t, u32 len) {
        visited[t] = true;
        first[t] = index.size();

        for (auto idx : state[t].suffix) {
            index.emplace_back(idx);
            length.emplace_back(len);
        }

        for (auto [c, s] : state[t].next) {
            if (visited[s]) {
                u32 delta = (len+1 + jump[s]) - length[first[s]];
                for (u32 i = first[s]; i < last[s]; ++i) {
                    index.emplace_back(index[i]);
                    length.emplace_back(length[i] + delta);
                }
            }
            else {
                dfs(s, len+1);
            }
        }

        jump[t] = length[first[t]] - len;
        last[t] = index.size();
    }

    vector<tuple<u32, u32>> suffix_array(vector<Word> const& word) {
        u32 n = 0; for (auto& w : word) n += w.size();

        index.reserve(n);
        length.reserve(n);
        visited.resize(state.size(), false);
        first.resize(state.size());
        jump.resize(state.size());
        last.resize(state.size());
        dfs(0, 0);

        vector<tuple<u32, u32>> suffix(n);
        for (u32 i = 0; i < n; ++i) {
            suffix[i] = make_tuple(index[i], word[index[i]].size() - length[i]);
        }

        index = {};
        length = {};
        visited = {};
        first = {};
        jump = {};
        last = {};

        return suffix;
    }
};

int main() {
    u32 n;
    cin >> n;
    vector<string> s(n);
    for (auto& si : s) cin >> si;

    SuffixAutomaton saut;
    saut.build(s);

    auto sarr = saut.suffix_array(s);
    for (auto [i, j] : sarr) cout << i << " " << j << "\n";

    return 0;
}
