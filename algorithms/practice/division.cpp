#include <iostream>
#include <cstdint>

using namespace std;

class Solution {
public:
    // restoring division software implementation
    int divide(int dividend, int divisor) {
        if(dividend == INT_MIN && divisor == -1)
            return INT_MAX;
        if(divisor == INT_MIN) 
            return dividend == INT_MIN ? 1 : 0;

        uint64_t accQ = abs((int64_t)dividend);
        uint64_t M = abs((int64_t)divisor) << 32;
        for(int i = 0; i < 32; i++) {
            accQ <<= 1;
            if(accQ >= M) {
                accQ -= M;
                accQ++;
            }
        }
        uint32_t quotient = accQ;
        
        if((dividend < 0) ^ (divisor < 0)) 
            return -quotient;
        return quotient;
    }
};

int main() {
    Solution s;
    int a, b; cin >> a >> b;
    cout << s.divide(a, b);
    return 0;
}