#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, K;
vector<vector<int>> grid;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

vector<vector<vector<int>>> dp;

int dfs(int i, int j, int depth) {
    if (depth >= K) return 0;
    if (dp[i][j][depth] != -1) return dp[i][j][depth];

    int best_max_diff = 1e9;

    for (int d=0; d<4; d++) {
        int nx = i + dx[d];
        int ny = j + dy[d];
        if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
            int diff = grid[nx][ny] - grid[i][j];
            if (diff > 0)
                best_max_diff = min(best_max_diff, max(diff, dfs(nx, ny, depth+1)));
        }
    }

    return dp[i][j][depth] = best_max_diff;
}

int main() {
    cin >> N >> K;

    grid.resize(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
        }
    }

    // Please write your code here.
    dp.resize(N, vector<vector<int>>(N, vector<int>(K+1, -1)));
    int result = 1e9;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            result = min(result, dfs(i, j, 1));
        }
    }

    if (result == 1e9) cout << -1 << '\n';
    else cout << result << '\n';

    return 0;
}
