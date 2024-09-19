#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;

struct SuffixAutomaton {
    using Char = char;
    using Word = string;

    struct State {
        array<u32, 26> next = {};
        u32 link;
        u32 len;
        bool suffix = false;
    };

    vector<State> state;

    u32 split(u32 p, u32 q, Char c) {
        u32 clone = state.size();
        state.emplace_back();

        state[clone].next = state[q].next;
        state[clone].link = state[q].link;
        state[clone].len = state[p].len + 1;

        state[q].link = clone;

        while (state[p].next[c-'a'] == q) {
            state[p].next[c-'a'] = clone;
            p = state[p].link;
        }

        return clone;
    }

    u32 update(u32 last, Char c) {
        if (state[last].next[c-'a'] > 0) {
            u32 curr = state[last].next[c-'a'];
            if (state[curr].len > state[last].len + 1) curr = split(last, curr, c);
            return curr;
        }

        u32 curr = state.size();
        state.emplace_back();

        u32 p = last;
        while (state[p].next[c-'a'] == 0) {
            state[p].next[c-'a'] = curr;
            p = state[p].link;
        }

        u32 q = state[p].next[c-'a'];
        if (q == curr) q = 0;
        else if (state[q].len > state[p].len + 1) q = split(p, q, c);

        state[curr].link = q;
        state[curr].len = state[last].len + 1;

        return curr;
    }

    void build(Word const& word) {
        // root
        state.emplace_back();
        state[0].link = 0;
        state[0].len = 0;

        u32 last = 0;
        for (auto c : word) {
            last = update(last, c);
        }

        u32 t = 0;
        for (auto c : word) {
            t = state[t].next[c-'a'];
        }
        while (t != 0) {
            state[t].suffix = true;
            t = state[t].link;
        }
    }
};

int main() {
    string s;
    cin >> s;
    u32 n = s.size();

    SuffixAutomaton sa;
    sa.build(s);

    vector<u32> ans;
    u32 t = 0;
    for (u32 i = 0; i < n-1; ++i) {
        t = sa.state[t].next[s[i]-'a'];
        if (sa.state[t].suffix) ans.emplace_back(i);
    }

    char const* prefix = "";
    for (auto x : ans) {
        cout << prefix << x+1;
        prefix = " ";
    }
    cout << "\n";

    return 0;
}
