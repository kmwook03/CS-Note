#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

#define MAX_CELLS 16

using namespace std;

struct Module {
    int energy;
    bitset<MAX_CELLS> cells;
};

vector<Module> modules;

int N, M;
vector<vector<int>> board;
vector<vector<bool>> visited;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bitset<MAX_CELLS> current_cells;


void dfs(int x, int y, int depth, int sum) {
    if (depth == 5) {
        modules.push_back({sum, current_cells});
        return;
    }

    for (int d=0; d<4; d++) {
        int nx = x + dx[d];
        int ny = y + dy[d];

        if (0<=nx && nx<N && 0<=ny && ny<M && !visited[nx][ny]) {
            visited[nx][ny] = true;
            current_cells.set(nx*M+ny);
            dfs(x, y, depth+1, sum+board[nx][ny]);
            dfs(nx, ny, depth+1, sum+board[nx][ny]);
            current_cells.reset(nx*M+ny);
            visited[nx][ny] = false;
        }
    }
}

int main() {
    // Please write your code here.
    cin >> N >> M;
    board.resize(N, vector<int>(M));
    visited.resize(N, vector<bool>(M));

    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++)
            cin >> board[i][j];
    
    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) {
            visited[i][j] = true;
            current_cells.set(i*M+j);
            dfs(i, j, 1, board[i][j]);
            current_cells.reset(i*M+j);
            visited[i][j] = false;
        }
    }

    int max_energy = -9999999;

    int K = modules.size();

    for (int i=0; i<K; i++) {
        for (int j=i+1; j<K; j++) {
            if ((modules[i].cells & modules[j].cells).count() == 2) {
                int current_total = modules[i].energy + modules[j].energy;
                max_energy = max(current_total, max_energy);
            }
        }
    }

    cout << max_energy << '\n';

    return 0;
}
