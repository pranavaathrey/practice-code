#include <stdio.h>
#define ll long long

ll largestPowerOfTwo(ll n) {
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n |= n >> 32; 
    return n + 1 >> 1;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        ll n;
        scanf("%lld", &n);
        if (n & (n - 1)) { 
            ll nextPowerOfTwo = largestPowerOfTwo(n);
            printf("%lld\n", (n ^ nextPowerOfTwo) << 1);
        } else { 
            printf("%lld\n", n);
        }
    }
    return 0;
}
