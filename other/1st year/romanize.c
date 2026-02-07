#include <stdio.h>
#include <string.h>

int main(){
    char *roman[] = {"M", "XM", "D", "CD", "C", "XC",  "L", "XL", "X", "IX", "V", "IV", "I"};
    int nums[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

    long num; 
    scanf("%ld", &num);

    for (int i = 0; i < 13; i++) {
        while (num >= nums[i]) {
            printf("%s", roman[i]);
            num -= nums[i];
        }
    }
}