#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;
using u64 = uint64_t;

u32 n;
u64 x;
vector<u64> t;

unordered_map<u64, u32> m;
u64 ans;

void go1(u32 i, u64 s) {
    if (s > x) return;
    if (i >= n) {
        m[s] += 1;
        return;
    }
    go1(i+2, s);
    go1(i+2, s+t[i]);
}

void go2(u32 i, u64 s) {
    if (s > x) return;
    if (i >= n) {
        ans += m[x-s];
        return;
    }
    go2(i+2, s);
    go2(i+2, s+t[i]);
}

u64 solve() {
    go1(0, 0);
    go2(1, 0);
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> x;

    t.resize(n);
    for (auto& ti : t) cin >> ti;

    cout << solve() << "\n";

    return 0;
}
