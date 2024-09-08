#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;
using u64 = uint64_t;

u32 n;
vector<u64> p;

u64 go(u32 i, u64 sumx, u64 sumy) {
    if (i == n) {
        return max(sumx, sumy) - min(sumx, sumy);
    }
    sumx += p[i];
    u64 ans1 = go(i+1, sumx, sumy);
    sumx -= p[i];
    sumy += p[i];
    u64 ans2 = go(i+1, sumx, sumy);
    sumy -= p[i];
    return min(ans1, ans2);
}

u64 solve() {
    return go(0, 0, 0);
}

int main() {
    cin >> n;

    p.resize(n);
    for (auto& pi : p) cin >> pi;

    cout << solve() << "\n";

    return 0;
}
