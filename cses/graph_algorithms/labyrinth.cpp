#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 n, m;
    cin >> n >> m;

    vector<vector<char>> grid(n, vector<char>(m));
    for (u32 i = 0; i < n; ++i) {
        for (u32 j = 0; j < m; ++j) {
            cin >> grid[i][j];
        }
    }

    u32 ai, aj, bi, bj;
    for (u32 i = 0; i < n; ++i) {
        for (u32 j = 0; j < m; ++j) {
            if (grid[i][j] == 'A') {
                ai = i;
                aj = j;
            }
            else if (grid[i][j] == 'B') {
                bi = i;
                bj = j;
            }
        }
    }

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<vector<char>> prev(n, vector<char>(m));
    deque<tuple<u32, u32>> queue;

    visited[bi][bj] = true;
    prev[bi][bj] = -1;
    queue.emplace_back(bi, bj);

    while (queue.size() > 0) {
        auto [i, j] = queue.front(); queue.pop_front();

        auto go = [&] (u32 ii, u32 jj, char p) {
            if (grid[ii][jj] == '#') return;
            if (visited[ii][jj]) return;
            visited[ii][jj] = true;
            prev[ii][jj] = p;
            queue.emplace_back(ii, jj);
        };
        if (i > 0)   go(i-1, j, 'D');
        if (i < n-1) go(i+1, j, 'U');
        if (j > 0)   go(i, j-1, 'R');
        if (j < m-1) go(i, j+1, 'L');
    }

    if (!visited[ai][aj]) {
        cout << "NO\n";
        return 0;
    }

    vector<char> ans;
    u32 i = ai, j = aj;
    while (i != bi || j != bj) {
        ans.emplace_back(prev[i][j]);
        switch (prev[i][j]) {
            case 'U':
                i = i-1;
                break;
            case 'D':
                i = i+1;
                break;
            case 'L':
                j = j-1;
                break;
            case 'R':
                j = j+1;
                break;
            default:
                assert(0);
        }
    }

    cout << "YES\n";
    cout << ans.size() << "\n";
    for (auto c : ans) cout << c; cout << "\n";

    return 0;
}
