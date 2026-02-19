#include <iostream>
#include <vector>

using namespace std;

struct rodCutInfo {
    vector<int> memo;
    vector<int> pos;
};
// O(n^2) time complexity
rodCutInfo maximizeRevenue(vector<int> &price4len) {
    int len = price4len.size();
    vector<int> memo(len + 1, 0);
    vector<int> pos(len + 1, 0);

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
    return {memo, pos};
}
void printCutting(rodCutInfo &info) {
    int n = info.memo.size() - 1;
    cout << "(Length " << n << ")\n";
    while(n > 0) {
        cout << info.pos[n] << "|";
        n = n - info.pos[n];
    }
    cout << endl;
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
    vector<int> price4len = {
        1, 5, 8, 10, 13, 17, 18, 20
    };
    rodCutInfo info = maximizeRevenue(price4len);
    cout << "Maximum revenue from optimal cut: \n" 
         << info.memo[price4len.size()] << endl;
    cout << "Optimal cutting for rod "; printCutting(info);
    // cout << maximizeRevenue2(price4len.size(), price4len);
    return 0;
}