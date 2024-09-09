#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;
using u64 = uint64_t;

u32 n;
string s;

u32 k;
vector<string> words;

u64 const M = 1000000007;

struct node {
    map<char, u32> next;
    bool word;

    node() : next(), word(false) {}
};

u64 solve() {
    vector<node> nodes;
    nodes.emplace_back(); // root

    for (auto& word : words) {
        u32 u = 0;
        for (auto c : word) {
            if (nodes[u].next.count(c) == 0) {
                nodes[u].next.emplace(c, nodes.size());
                nodes.emplace_back();
            }
            u = nodes[u].next[c];
        }
        nodes[u].word = true;
    }

    vector<u64> dp(n+1);
    dp[n] = 1;
    for (u32 i = n; i > 0;) { --i;
        dp[i] = 0;
        u32 u = 0;
        for (u32 j = i; j < n; ++j) {
            if (nodes[u].next.count(s[j]) == 0) break;
            u = nodes[u].next[s[j]];
            if (nodes[u].word) {
                dp[i] = (dp[i] + dp[j+1]) % M;
            }
        }
    }
    return dp[0];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> s;
    n = s.size();

    cin >> k;
    words.resize(k);
    for (auto& word : words) cin >> word;

    cout << solve() << "\n";

    return 0;
}
