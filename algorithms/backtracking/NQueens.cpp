#include <iostream>
#include <vector>
#include <cmath> 

using namespace std;

void printBoard(const vector<int> &board, int size) {
    static int solutionCount = 0;
    cout << "Solution " << ++solutionCount << ":" << endl;
    
    for(int row = 0; row < size; row++) {
        for(int col = 0; col < size; col++) {
            if(board[row] == col) cout << " Q ";
            else                  cout << " . ";
        } cout << endl;
    } cout << endl;
}

bool isSafe(const vector<int> &board, int row, int col) {
    for(int prevRow = 0; prevRow < row; prevRow++) 
        if(board[prevRow] == col      // if same column 
        || abs(board[prevRow] - col) 
        == abs(prevRow - row))        // if same diagonal 
            return false;
    return true;
}
void nQueens(vector<int> &board, int row, int size) {
    for(int col = 0; col < size; col++) 
        if(isSafe(board, row, col)) {
            board[row] = col;         // place the queen            
            // if we've placed all queens successfully
            if(row == size - 1) 
                printBoard(board, size);
            else 
                nQueens(board, row + 1, size);
        }
}

int main() {
    cout << "Enter the value of N for the N-Queens problem: ";
    int size; cin >> size;

    vector<int> board(size, 0);
    nQueens(board, 0, size);
    return 0;
}