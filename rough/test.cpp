#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public:
    int climbStairs(int n) {
        if(n <= 0) return 0;
        int a = 0, b = 1;

        for(int i = 1; i < n + 1; i++) {
            swap(a, b); b += a;
        }
        return b;
    }
};

int main() {
    Solution s;
    for(int i = 0; i < 40; i++) 
        cout << s.climbStairs(i) << " ";
    return 0;
}