#include <iostream>
#include <vector>

using namespace std;

class rodCutting {
    vector<int> price4len;
    int len;
    vector<int> memo;
    vector<int> pos;
    
    public:
    rodCutting(vector<int> price): price4len(price) {
        len = price4len.size();

        memo = vector<int>(len + 1, 0);
        pos = vector<int>(len + 1, 0);
        maximizeRevenue();
    }
    friend ostream& operator<<(ostream& os, const rodCutting& info);
    // O(n^2) time complexity
    void maximizeRevenue() {
        for(int i = 1; i <= len; i++) {
            int maxRev = INT_MIN;

            for(int j = 1; j <= i; j++) {
                int rev = price4len[j - 1] + memo[i - j];
                if(rev > maxRev) {
                    maxRev = rev;
                    pos[i] = j;
                }
            }
            memo[i] = maxRev; 
        }
    }
};
// print algorithm
ostream& operator<<(ostream& os, const rodCutting& info) {
    int n = info.len;
    os << "Maximum revenue from optimal cut: \t " 
            << info.memo[n] << "\n";
    os << "Optimal cutting for rod (length " << n << "): \t|";
    while(n > 0) {
        os << info.pos[n] << "|";
        n = n - info.pos[n];
    }
    return os;
}

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
        1, 5, 8, 10, 13, 17, 18, 20
    });
    cout << cutRod << endl;
    return 0;
}