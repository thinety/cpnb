#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;
using u64 = uint64_t;

u32 n, m;
vector<vector<char>> grid;

vector<vector<bool>> visited;

bool dfs(u32 i, u32 j) {
    if (grid[i][j] == '#') return false;
    if (visited[i][j]) return false;

    visited[i][j] = true;
    if (i > 0)   dfs(i-1, j  );
    if (i < n-1) dfs(i+1, j  );
    if (j > 0)   dfs(i  , j-1);
    if (j < m-1) dfs(i  , j+1);
    return true;
}

u64 solve() {
    visited.assign(n, vector<bool>(m, false));

    u32 ans = 0;
    for (u32 i = 0; i < n; ++i) {
        for (u32 j = 0; j < m; ++j) {
            if (dfs(i, j)) ans += 1;
        }
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    grid.assign(n, vector<char>(m));
    for (u32 i = 0; i < n; ++i) {
        for (u32 j = 0; j < m; ++j) {
            cin >> grid[i][j];
        }
    }

    cout << solve() << "\n";

    return 0;
}
