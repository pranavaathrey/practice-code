#include <iostream>
#include <vector>

using namespace std;

class rodCutting {
    vector<int> price4len;
    int len;
    vector<int> memo;
    vector<int> pos;
    
    // O(n^2) time complexity
    int maximizeRevenue() {
        for(int i = 1; i <= len; i++) {
            int maxRev = INT_MIN;

            for(int j = 1; j <= i; j++) {
                int rev = price4len[j - 1] 
                        + memo[i - j];
                if(rev > maxRev) {
                    maxRev = rev;
                    pos[i] = j;
                }
            }
            memo[i] = maxRev; 
        }
        return memo[len];
    }

    public:
    rodCutting(vector<int> price): price4len(price) {
        len = price4len.size();

        memo = vector<int>(len + 1, 0);
        pos = vector<int>(len + 1, 0);
        maximizeRevenue();
    }    
    
    void printCutting() {
        cout << "Maximum revenue from optimal cut: \t " 
                << memo[len] << "\n";
        cout << "Optimal cutting for rod (length " << len << "): \t|";
        while(len > 0) {
            cout << pos[len] << "|";
            len -= pos[len];
        }
    }
};

// O(2^n) time complexity! for len > ~40 it will take forever
int maximizeRevenue2(int len, vector<int> &price4len) {
    if(len <= 0) return 0;

    int maxRevenue = 0;
    for(int i = 1; i <= len; i++) {
        int rev = price4len[i - 1] 
            + maximizeRevenue2(len - i, price4len);
        if(rev > maxRevenue) maxRevenue = rev;
    }
    return maxRevenue;
}

int main() {
    rodCutting cutRod({
        2, 3, 7, 8, 12
    });
    cutRod.printCutting();
    return 0;
}