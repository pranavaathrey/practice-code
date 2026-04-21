#include <iostream>
#include <vector>

using namespace std;
using Grid = vector<vector<int>>;

bool isSafe(const Grid &puzzle, int row, int col, int val) {
    for(int i = 0; i < 9; i++) 
        if(puzzle[row][i] == val 
        || puzzle[i][col] == val) 
            return false;    
    int sr = 3 * (row / 3);
    int sc = 3 * (col / 3);
    for(int i = 0; i < 3; i++) 
        for(int j = 0; j < 3; j++) 
            if(puzzle[sr + i][sc + j] == val) 
                return false;
    return true;
}

bool findEmpty(const Grid &puzzle, int &row, int &col) {
    for(int i = 0; i < 9; i++) 
        for(int j = 0; j < 9; j++) 
            if(puzzle[i][j] == 0) {
                row = i; col = j;
                return true;
            }
    return false;
}

bool solveSudoku(Grid &puzzle) {
    int row, col;
    if(!findEmpty(puzzle, row, col)) 
        return true;

    for(int val = 1; val <= 9; val++) 
        if(isSafe(puzzle, row, col, val)) {
            puzzle[row][col] = val;
            if(solveSudoku(puzzle)) 
                return true;
            puzzle[row][col] = 0;
        }
    return false;
}

int main() {
    Grid puzzle(9, vector<int>(9));
    cout << "Enter Sudoku puzzle: " << endl;
    for (int i = 0; i < 9; i++) 
        for (int j = 0; j < 9; j++) {
            if (!(cin >> puzzle[i][j])) 
                return 0;
        }
    
    if (!solveSudoku(puzzle)) {
        cout << endl << "No solution exists.\n";
        return 0;
    }
    cout << endl << "Solution: " << endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) 
            cout << puzzle[i][j] << (j + 1 == 9 ? '\n' : ' ');
    }
    return 0;
}