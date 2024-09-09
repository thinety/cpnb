#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;
using u64 = uint64_t;

u32 n;
string t;

u32 m;
string p;

struct node {
    map<char, u32> next;
    u32 suffix;
};

u64 solve() {
    vector<node> nodes;
    nodes.emplace_back(); // root
    nodes[0].suffix = -1;

    u32 u = 0;
    for (auto c : p) {
        u32 v = nodes.size();
        nodes.emplace_back();
        nodes[u].next.emplace(c, v);

        u32 suffix = nodes[u].suffix;
        while (suffix != -1 && nodes[suffix].next.count(c) == 0) suffix = nodes[suffix].suffix;
        if (suffix != -1) nodes[v].suffix = nodes[suffix].next[c];
        else nodes[v].suffix = 0;

        u = nodes[u].next[c];
    }
    u32 word = u;

    auto go = [&] (u32 u, char c) {
        while (u != -1 && nodes[u].next.count(c) == 0) u = nodes[u].suffix;
        if (u != -1) u = nodes[u].next[c];
        else u = 0;
        return u;
    };

    u32 ans = 0;
    u = 0;
    for (u32 i = 0; i < n; ++i) {
        u = go(u, t[i]);
        if (u == word) ans += 1;
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> t;
    n = t.size();

    cin >> p;
    m = p.size();

    cout << solve() << "\n";

    return 0;
}
