#include <iostream>

using namespace std;

struct powerCheck {
    static bool isPowerOfTwo(int n) {
        // we simply need to check if only one bit is set.
        // eg: checking 64: 0100 0000 & 0011 1111 = 0000 0000 
        // (no overlapping of bits). also skip negatives & zero. 
        return (n > 0) && (n & (n-1)) == 0;
    }
    static bool isPowerOfThree(int n) {
        // can simply check if its divisible by the maximum power of 3 
        // that is representable by an int (32-bit, signed).
        int maxPowOf3 = 1162261467;
        return (n > 0) && (maxPowOf3 % n == 0);
    }
    static bool isPowerOfFour(int n) {
        // powers of 4 do not show up in even bit positions.
        int mask = 0xAAAAAAAA;
        return isPowerOfTwo(n) && ((n & mask) == 0);
    }
};

int main() {
    cout << "Enter a number to check: ";
    int n; cin >> n;
    cout << endl << "Power of 2: ";
    cout << powerCheck::isPowerOfTwo(n);
    cout << endl << "Power of 3: ";
    cout << powerCheck::isPowerOfThree(n);
    cout << endl << "Power of 4: ";
    cout << powerCheck::isPowerOfFour(n);
}