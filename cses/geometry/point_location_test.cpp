#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;
using i64 = int64_t;

struct pt { i64 x = 0, y = 0, z = 0; };
struct vec { i64 x = 0, y = 0, z = 0; };

vec operator-(pt a, pt b) {
    return {
        a.x - b.x,
        a.y - b.y,
        a.z - b.y,
    };
}

vec cross(vec u, vec v) {
    return {
        u.y*v.z - u.z*v.y,
        u.z*v.x - u.x*v.z,
        u.x*v.y - u.y*v.x,
    };
}

char const* solve(pt p1, pt p2, pt p3) {
    vec u = p2 - p1, v = p3 - p1;
    vec w = cross(u, v);
    if (w.z > 0) return "LEFT";
    if (w.z < 0) return "RIGHT";
    return "TOUCH";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 t; cin >> t;
    while (t--) {
        pt p1, p2, p3;
        cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;
        cout << solve(p1, p2, p3) << "\n";
    }

    return 0;
}
