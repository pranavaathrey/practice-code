#include <iostream>
#include <vector>

using namespace std;

// O(2^n) time complexity! 
int maximizeRevenue(int len, vector<int> &price4len) {
    if(len <= 0) return 0;

    int maxRevenue = 0;
    for(int i = 1; i <= len; i++) {
        int rev = price4len[i - 1] 
            + maximizeRevenue(len - i, price4len);
        if(rev > maxRevenue) maxRevenue = rev;
    }
    return maxRevenue;
}

int main() {
    vector<int> price4len = {27, 25, 29, 72, 11, 33, 70, 21, 30, 68, 47, 94, 25, 79, 45, 57, 26, 74, 13, 60, 27, 21, 85, 19, 80, 98, 51, 66, 55, 2};
    cout << maximizeRevenue(30, price4len);
    return 0;
}