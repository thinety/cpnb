#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;
using u64 = uint64_t;

u32 n;
vector<u32> x;

vector<vector<u32>> table;

void build() {
    // floor(log2(n))
    u32 l = 0; for (u32 x = n; x > 1;) { l += 1; x /= 2; }
    l += 1;
    table.resize(l);
    table[0] = x;
    for (u32 i = 1; i < l; ++i) {
        table[i].resize(n-(1<<i)+1);
        for (u32 j = 0; j < n-(1<<i)+1; ++j) {
            table[i][j] = min(table[i-1][j], table[i-1][j+(1<<(i-1))]);
        }
    }
}

// min of [a, b)
u64 query(u32 a, u32 b) {
    // floor(log2(b-a))
    u32 l = 0; for (u32 x = b-a; x > 1;) { l += 1; x /= 2; }
    return min(table[l][a], table[l][b-(1<<l)]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 q;
    cin >> n >> q;

    x.resize(n);
    for (auto& xi : x) cin >> xi;

    build();

    while (q--) {
        u32 a, b;
        cin >> a >> b; a--;
        cout << query(a, b) << "\n";
    }

    return 0;
}
