#include <iostream>
#include <vector>

using namespace std;

class Sudoku {
    vector<vector<char>> sudokuBoard;

    // TODO: Finish implementation
    vector<vector<char>> generateSudokuBoard(float fill) {
        
    }
    vector<vector<char>> solveSudokuBoard(float fill) {
        
    }

    public:
    Sudoku() {}
    Sudoku(vector<vector<char>> givenBoard): sudokuBoard(givenBoard) {}

    bool isValidSudokuBoard() {
        for(int i = 0; i < 9; i++) {
            int subBox[10] = {0};
            int    row[10] = {0};
            int column[10] = {0};

            for(int j = 0; j < 9; j++) {
                int r = ((i / 3) * 3) + (j / 3);
                int c = ((i % 3) * 3) + (j % 3);

                if(isdigit(sudokuBoard[r][c])) // sub-box check
                    if(++subBox[sudokuBoard[r][c] - '0'] > 1)
                        return false;
                if(isdigit(sudokuBoard[i][j])) // row check
                    if(   ++row[sudokuBoard[i][j] - '0'] > 1)
                        return false;
                if(isdigit(sudokuBoard[j][i])) // column check
                    if(++column[sudokuBoard[j][i] - '0'] > 1)
                        return false;
            }
        }
        return true;
    }
    bool isValidSudokuSolution(vector<vector<char>>& board) {
        for(int i = 0; i < 9; i++) {
            int subBox[10] = {0};
            int    row[10] = {0};
            int column[10] = {0};

            for(int j = 0; j < 9; j++) {
                int r = ((i / 3) * 3) + (j / 3);
                int c = ((i % 3) * 3) + (j % 3);

                if(isdigit(board[r][c])) // sub-box check
                    subBox[board[r][c] - '0']++;
                if(isdigit(board[i][j])) // row check
                       row[board[i][j] - '0']++;
                if(isdigit(board[j][i])) // column check
                    column[board[j][i] - '0']++;
            }
            for(int digitCount: subBox)
                if(digitCount != 1) return false;
            for(int digitCount:    row)
                if(digitCount != 1) return false;
            for(int digitCount: column)
                if(digitCount != 1) return false;
        }
        return true;
    }
};