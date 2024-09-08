#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;
using u64 = uint64_t;

char solve(u64 i) {
    u64 pos = 0;
    u32 len = 1;
    u64 add = 9;
    while (true) {
        if (pos + len*add >= i) break;
        pos += len*add;
        len += 1;
        add *= 10;
    }
    u64 n = (i - pos - 1) / len + 1; // ceil((i-pos)/len)
    u64 m = (i - pos - 1) % len;
    u64 x = add/9 - 1 + n;
    string s = to_string(x);
    return s[m];
}

int main() {
    u32 q;
    cin >> q;

    while (q--) {
        u64 k;
        cin >> k;
        cout << solve(k) << "\n";
    }

    return 0;
}
