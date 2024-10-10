#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 n, x;
    cin >> n >> x;

    vector<u32> a(n);
    for (u32 i = 0; i < n; ++i) cin >> a[i];

    map<u32, vector<u32>> indices;
    for (u32 i = 0; i < n; ++i) {
        indices[a[i]].push_back(i);
    }

    for (u32 i = 0; i < n; ++i) {
        u32 b = x-a[i];
        if (b != a[i]) {
            if (indices.count(b) > 0) {
                cout << indices[a[i]][0]+1 << " " << indices[b][0]+1 << "\n";
                return 0;
            }
        }
        else {
            if (indices[a[i]].size() > 1) {
                cout << indices[a[i]][0]+1 << " " << indices[a[i]][1]+1 << "\n";
                return 0;
            }
        }
    }

    cout << "IMPOSSIBLE\n";

    return 0;
}
