#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;
using u64 = uint64_t;

u32 const n = 8;
vector<vector<char>> grid;

bool ok(u32 i, u32 j) {
    bool ok = true;
    for (u32 ii = 0; ii < n; ++ii)
        ok &= grid[ii][j] != 'Q';
    for (u32 jj = 0; jj < n; ++jj)
        ok &= grid[i][jj] != 'Q';
    for (u32 ii = i-min(i,j), jj = j-min(i,j); ii < n && jj < n; ++ii, ++jj)
        ok &= grid[ii][jj] != 'Q';
    for (u32 ii = i-min(i,n-1-j), jj = j+1+min(i,n-1-j); ii < n && jj > 0; ++ii, --jj)
        ok &= grid[ii][jj-1] != 'Q';
    return ok;
}

u64 go(u32 q, u32 i, u32 j) {
    if (q == 8) {
        return 1;
    }

    u64 ans = 0;
    for (; i < n; ++i) {
        for (; j < n; ++j) {
            if (grid[i][j] == '*') continue;
            if (ok(i, j)) {
                grid[i][j] = 'Q';
                ans += go(q+1, i, j+1);
                grid[i][j] = '.';
            }
        }
        j = 0;
    }
    return ans;
}

u64 solve() {
    return go(0, 0, 0);
}

int main() {
    grid.resize(n, vector<char>(n));
    for (u32 i = 0; i < n; ++i) {
        for (u32 j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }

    cout << solve() << "\n";

    return 0;
}
