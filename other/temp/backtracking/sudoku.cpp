#include <iostream>
#include <vector>

using namespace std;

const int N = 9;

bool isSafe(const vector<vector<int>> &grid, int row, int col, int val) {
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == val || grid[i][col] == val) return false;
    }

    int sr = (row / 3) * 3;
    int sc = (col / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[sr + i][sc + j] == val) return false;
        }
    }
    return true;
}

bool findEmpty(const vector<vector<int>> &grid, int &row, int &col) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 0) {
                row = i;
                col = j;
                return true;
            }
        }
    }
    return false;
}

bool solveSudoku(vector<vector<int>> &grid) {
    int row, col;
    if (!findEmpty(grid, row, col)) return true;

    for (int val = 1; val <= 9; val++) {
        if (isSafe(grid, row, col, val)) {
            grid[row][col] = val;
            if (solveSudoku(grid)) return true;
            grid[row][col] = 0;
        }
    }
    return false;
}

int main() {
    vector<vector<int>> grid(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!(cin >> grid[i][j])) return 0;
        }
    }

    if (!solveSudoku(grid)) {
        cout << "No solution exists\n";
        return 0;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) cout << grid[i][j] << (j + 1 == N ? '\n' : ' ');
    }
    return 0;
}