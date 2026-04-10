#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void printBoard(const vector<int> &board, int n) {
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cout << (board[r] == c ? 'Q' : '.') << (c + 1 == n ? '\n' : ' ');
        }
    }
    cout << "\n";
}

bool isSafe(const vector<int> &board, int row, int col) {
    for (int prev = 0; prev < row; prev++) {
        if (board[prev] == col || abs(board[prev] - col) == abs(prev - row)) return false;
    }
    return true;
}

void solveNQueens(vector<int> &board, int row, int n, int &count) {
    for (int col = 0; col < n; col++) {
        if (!isSafe(board, row, col)) continue;
        board[row] = col;
        if (row == n - 1) {
            count++;
            printBoard(board, n);
        } else {
            solveNQueens(board, row + 1, n, count);
        }
    }
}

int main() {
    int n;
    if (!(cin >> n) || n <= 0) return 0;
    vector<int> board(n, 0);
    int count = 0;
    solveNQueens(board, 0, n, count);
    cout << count << "\n";
    return 0;
}