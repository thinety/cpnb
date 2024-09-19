#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;

u32 n;
vector<u32> x;

vector<u32> pxx;

void build() {
    pxx.resize(n+1);
    pxx[0] = 0;
    for (u32 i = 0; i < n; ++i) {
        pxx[i+1] = pxx[i] ^ x[i];
    }
}

// sum of [a, b)
u32 query(u32 a, u32 b) {
    return pxx[b] ^ pxx[a];
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
