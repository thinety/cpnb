#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;

u32 const len = 48;
string path;

u32 const n = 7;
bool grid[n][n];

u32 const i_dest = 6;
u32 const j_dest = 0;

u32 ans;

void go(u32 i, u32 j, u32 pos) {
    if (i == i_dest && j == j_dest) {
        if (pos == len) ans += 1;
        return;
    }

    bool up    = (path[pos] == 'U' || path[pos] == '?') && i > 0   && !grid[i-1][j  ];
    bool down  = (path[pos] == 'D' || path[pos] == '?') && i < n-1 && !grid[i+1][j  ];
    bool left  = (path[pos] == 'L' || path[pos] == '?') && j > 0   && !grid[i  ][j-1];
    bool right = (path[pos] == 'R' || path[pos] == '?') && j < n-1 && !grid[i  ][j+1];

    if (up && down && !left && !right) return;
    if (!up && !down && left && right) return;

    grid[i][j] = true;

    if (up)    go(i-1, j  , pos+1);
    if (down)  go(i+1, j  , pos+1);
    if (left)  go(i  , j-1, pos+1);
    if (right) go(i  , j+1, pos+1);

    grid[i][j] = false;
}

int main() {
    cin >> path;

    go(0, 0, 0);

    cout << ans << "\n";

    return 0;
}
