#include <stdio.h>

// uses maxHeapify
void heapify(int array[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && array[left] > array[largest])
        largest = left;

    if (right < n && array[right] > array[largest])
        largest = right;

    if (largest != i) {
        // swap largest node into parent place
        int temp = array[i];
        array[i] = array[largest];
        array[largest] = temp;
        // check the rest of the heap
        heapify(array, n, largest);
    }
}
void heapSort(int array[], int n) {
    // build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(array, n, i);

    // extract elements
    for (int i = n - 1; i > 0; i--) {
        // swap top of max heap with end of unsorted part
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;
        // re-heapify since heap property is broken
        heapify(array, i, 0);
    }
}

int main() {
    int array[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(array) / sizeof(array[0]);

    heapSort(array, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
    printf("\n");

    return 0;
}
