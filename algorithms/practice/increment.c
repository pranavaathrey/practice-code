#include <stdio.h>
#include <stdlib.h>

int* plusOne(int* digits, int digitsSize, int* returnSize) {
    if(digits[digitsSize - 1] != 9) {
        *returnSize = digitsSize;
        int* incremented = (int *)malloc(digitsSize * sizeof(int));

        for(int i = 0; i < digitsSize; i++) {
            if(i != digitsSize - 1) {
                incremented[i] = digits[i];
                continue;
            }
            incremented[i] = digits[i] + 1;
        }
        return incremented;
    } else {
        int* incremented = (int *)malloc((digitsSize + 1) * sizeof(int));
        incremented[digitsSize] = 0; 
        *returnSize = digitsSize;

        int carry = 1; // we know its gonna be 1
        for(int i = digitsSize - 1; i >= 0; i--) {
            if(digits[i] == 9 && carry) {
                incremented[i] = 0;
                continue;
            } if(carry) {
                carry = 0; // first non-nine digit
                incremented[i] = digits[i] + 1;
                continue;
            }
            incremented[i] = digits[i];
        }
        if(carry) {
            incremented[0] = 1;
            (*returnSize)++;
        }
        return incremented;
    }
}

int main() {
    int n; scanf("%d", &n);
    int num[n], returnSize;
    printf("Enter a number, digit by digit: ");
    for(int i = 0; i < n; i++) 
        scanf("%d", &num[i]);

    int* incremented = plusOne(num, n, &returnSize);    
    for(int i = 0; i < returnSize; i++) 
        printf("%d", incremented[i]);
    free(incremented);
    return 0;
}