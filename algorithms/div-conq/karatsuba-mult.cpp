#include <iostream>
#include <algorithm>

using namespace std;

// Helper function to calculate the number of digits in a number
int getDigitLength(long long value) {
    int count = 0;
    while (value > 0) {
        count++;
        value /= 10;
    }
    return count;
}

// Helper function for integer exponentiation to avoid floating-point inaccuracies
long long intPow(long long base, int exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) result *= base;
        base *= base;
        exp /= 2;
    }
    return result;
}

long long karatsuba(long long x, long long y) {
    // Base case: If either number is a single digit, 
    // fall back to standard multiplication.
    if (x < 10 || y < 10) {
        return x * y;
    }
    // Determine the split point (m)
    int n = max(getDigitLength(x), getDigitLength(y));
    int m = n / 2;

    long long multiplier = intPow(10, m);

    // Split the numbers into halves
    long long x1 = x / multiplier;
    long long x0 = x % multiplier;
    long long y1 = y / multiplier;
    long long y0 = y % multiplier;

    // The three recursive calls
    long long z2 = karatsuba(x1, y1);
    long long z0 = karatsuba(x0, y0);
    long long z1 = karatsuba(x1 + x0, y1 + y0) - z2 - z0;

    // Reconstruct the final product
    return z2 * intPow(10, 2 * m) + z1 * multiplier + z0;
}

int main() {
    long long a = 12345;
    long long b = 6789;
    
    long long result = karatsuba(a, b);
    
    cout << "Multiplying " << a << " and " << b << endl;
    cout << "Result: " << result << endl;
    cout << "Verification (standard *): " << a * b << endl;

    return 0;
}