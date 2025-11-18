#include <stdio.h>
#include <stdlib.h>

// modified counting sorts
static void countingSort(int *array, int n, int exp) {
    int output[n];
    int count[10] = {0};

    int i;
    for (i = 0; i < n; i++) {
        int digit = (array[i] / exp) % 10;
        count[digit]++;
    }
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        int digit = (array[i] / exp) % 10;
        output[count[digit] - 1] = array[i];
        count[digit]--;
    }
    for (i = 0; i < n; i++)
        array[i] = output[i];
}

void radixSort(int *array, int n) {
    int max = array[0];
    for (int i = 1; i < n; i++)
        if (array[i] > max)
            max = array[i];

    for (int exp = 1; max / exp > 0; exp *= 10)
        countingSort(array, n, exp);
}

int main(void) {
    int array[] = {329, 457, 657, 839, 436, 720, 355};
    int n = sizeof(array) / sizeof(array[0]);

    radixSort(array, n);

    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
    printf("\n");
    return 0;
}
