#include <iostream>
#include <vector>

using namespace std;

bool solveMaze(const vector<vector<int>> &maze, vector<vector<int>> &path, vector<vector<int>> &vis,
               int r, int c, int er, int ec) {
    int rows = (int)maze.size();
    int cols = (int)maze[0].size();
    if (r < 0 || c < 0 || r >= rows || c >= cols) return false;
    if (maze[r][c] == 0 || vis[r][c]) return false;

    vis[r][c] = 1;
    path[r][c] = 1;
    if (r == er && c == ec) return true;

    static int dr[4] = {1, 0, -1, 0};
    static int dc[4] = {0, 1, 0, -1};
    for (int k = 0; k < 4; k++) {
        if (solveMaze(maze, path, vis, r + dr[k], c + dc[k], er, ec)) return true;
    }

    path[r][c] = 0;
    return false;
}

int main() {
    int rows, cols;
    if (!(cin >> rows >> cols) || rows <= 0 || cols <= 0) return 0;

    vector<vector<int>> maze(rows, vector<int>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) cin >> maze[i][j];
    }

    int sr, sc, er, ec;
    if (!(cin >> sr >> sc >> er >> ec)) return 0;
    if (sr < 0 || sc < 0 || sr >= rows || sc >= cols || er < 0 || ec < 0 || er >= rows || ec >= cols) return 0;

    vector<vector<int>> path(rows, vector<int>(cols, 0));
    vector<vector<int>> vis(rows, vector<int>(cols, 0));
    bool ok = solveMaze(maze, path, vis, sr, sc, er, ec);

    if (!ok) {
        cout << "No path found\n";
        return 0;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) cout << path[i][j] << (j + 1 == cols ? '\n' : ' ');
    }
    return 0;
}