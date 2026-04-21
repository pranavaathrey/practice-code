#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int knapsack(int W, vector<int>& values, vector<int>& weights) {
    int n = values.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // bottom-up DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (weights[i - 1] <= w) 
                dp[i][w] = max(
                    values[i - 1] 
                      + dp[i - 1][w - weights[i - 1]], // include
                    dp[i - 1][w]                       // exclude
                );
            else // item is too heavy for the current capacity
                dp[i][w] = dp[i - 1][w];
        }
    }
    // bottom-right cell holds the answer for all items and full capacity
    return dp[n][W];
}

int main() {
    vector<int> values = {60, 100, 120};
    vector<int> weights = {10, 20, 30};
    int W = 50; 

    cout << "Knapsack Capacity: " << W << endl;
    cout << "Maximum achievable value: " 
         << knapsack(W, values, weights) << endl;

    return 0;
}