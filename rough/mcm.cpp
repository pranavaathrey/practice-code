#include <iostream>
#include <vector>

using namespace std;

struct ChainInfo {
    vector<vector<int>> cost;
    vector<vector<int>> ktable;

    ChainInfo(int n) {
        cost = vector<vector<int>>(n, vector<int>(n, 0));
        ktable = vector<vector<int>>(n, vector<int>(n, 0));
    }
};

ChainInfo findMinCost(vector<int> p) {
    int n = p.size(); ChainInfo result(n);

    for(int L = 2; L < n; L++) 
        for(int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            result.cost[i][j] = INT_MAX;

            for(int k = i; k < j; k++) {
                int cost = result.cost[i][k] 
                         + result.cost[k + 1][j]
                         + (p[i - 1] * p[k] * p[j]);
                if(cost < result.cost[i][j]) {
                    result.cost[i][j] = cost;
                    result.ktable[i][j] = k;
                }
            }
        }
    return result;
}
void parenthesize(vector<vector<int>> kTable, int i, int j) {
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
    vector<int> p = {3, 2, 4, 2, 5};
    ChainInfo result = findMinCost(p);
    parenthesize(result.ktable, 1, p.size() - 1);
}