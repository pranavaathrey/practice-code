#include <stdio.h>
#define ll long long

//function to find the largest power of 2 less than or equal to 'n'
ll largestPowerOfTwo(ll n) {
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n |= n >> 32; //for 64-bit integers
    return n + 1 >> 1;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        ll n;
        scanf("%lld", &n);
        if (n & (n - 1)) { //check if 'n' is not a power of 2
            ll nextPowerOfTwo = largestPowerOfTwo(n);
            printf("%lld\n", (n ^ nextPowerOfTwo) << 1);
        } else { //'n' is already a power of 2
            printf("%lld\n", n);
        }
    }
    return 0;
}
