#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 n, m;
    cin >> n >> m;

    vector<u32> x(n);
    for (auto& xi : x) { cin >> xi; xi--; }

    vector<u32> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&] (u32 i, u32 j) {
        return x[i] < x[j];
    });

    u32 ans = 1;
    for (u32 i = 1; i < n; ++i) {
        if (idx[i-1] > idx[i]) ans += 1;
    }

    for (u32 q = 0; q < m; ++q) {
        u32 a, b;
        cin >> a >> b;
        a--, b--;

        assert(idx[x[a]] == a);
        assert(idx[x[b]] == b);

        set<u32> is;
        if (x[a] > 0) is.emplace(x[a]);
        if (x[a] < n-1) is.emplace(x[a]+1);
        if (x[b] > 0) is.emplace(x[b]);
        if (x[b] < n-1) is.emplace(x[b]+1);

        for (auto i : is) if (idx[i-1] > idx[i]) ans -= 1;
        swap(idx[x[a]], idx[x[b]]);
        for (auto i : is) if (idx[i-1] > idx[i]) ans += 1;
        swap(x[a], x[b]);

        cout << ans << "\n";
    }

    return 0;
}
