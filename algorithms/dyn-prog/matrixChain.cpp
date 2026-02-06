#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class ChainInfo {
    public:
    vector<vector<int>> cost, kTable;

    ChainInfo(int n): 
        cost(n, vector<int>(n, 0)), 
        kTable(n, vector<int>(n, 0)) 
    {}
};

ChainInfo optimalMatrixChain(vector<int> p) {
    int n = p.size(); ChainInfo result(n);
    
    // base cost for 1 matrix, no multiplication
    // (redundant as vectors are init to 0's, but here for clarity)
    for(int i = 1; i < n; i++) 
        result.cost[i][i] = 0;
    
    // L is the chain length; now we deal with chain lengths >1
    for(int L = 2; L < n; L++) {
        for(int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1; // end of matrix chain
            result.cost[i][j] = INT_MAX;

            // consider every k value
            for(int k = i; k < j; k++) {
                int cost = result.cost[i][k] + result.cost[k + 1][j]
                         + (p[i - 1] * p[k] * p[j]);
                if(cost < result.cost[i][j]) {
                    result.cost[i][j] = cost;
                    result.kTable[i][j] = k;
                }
                // this greedily populates the kTable and the cost table
                // with the best values for lowest cost. 
            }
        }
    }
    return result;
}

void printChain(const vector<int> p) {
    for(int i = 1; i < p.size(); i++) {
        cout <<"A"<< i <<"["<< p[i - 1] <<"x"<< p[i] <<"]";
        if(i != p.size() - 1) cout << " * ";
    }
}
void parenthesize(const vector<vector<int>>& kTable, int i, int j) {
    if(i == j)
        cout << "A" << i;
    else {
        cout << "(";
        parenthesize(kTable, i, kTable[i][j]);
        parenthesize(kTable, kTable[i][j] + 1, j);
        cout << ")";
    }
}

int main() {
    // matrix dimensions d0, d1, d2, d3...
    // the dimensions of ith matrix A = p[i - 1] * p[i]
    vector<int> p = {3, 2, 4, 2, 5};

    cout << "For the matrix chain: "; printChain(p);
    cout << endl << "The optimal order of operations is: ";
    ChainInfo result = optimalMatrixChain(p);
    parenthesize(result.kTable, 1, p.size() - 1);
}