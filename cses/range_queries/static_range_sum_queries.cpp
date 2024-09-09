#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;
using u64 = uint64_t;

u32 n;
vector<u64> x;

vector<u64> psx;

void build() {
    psx.resize(n+1);
    psx[0] = 0;
    for (u32 i = 0; i < n; ++i) {
        psx[i+1] = psx[i] + x[i];
    }
}

// sum of [a, b)
u64 query(u32 a, u32 b) {
    return psx[b] - psx[a];
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
