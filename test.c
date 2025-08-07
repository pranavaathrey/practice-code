#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int list[], int low, int high) {
    swap(&list[low + (high - low) / 2], &list[high]);
    int pivot = list[high];

    int i = low - 1;
    for(int j = low; j < high; j++) 
        if(list[j] < pivot) {
            i++;
            swap(&list[i], &list[j]);
        }
    swap(&list[i + 1], &list[high]);
    return i + 1;
}

void quickSort(int list[], int low, int high) {
    if(high > low) {
        int pi = partition(list, low, high);

        quickSort(list, low, pi - 1);
        quickSort(list, pi + 1, high);
    }
}

int main() {
    int n;
    printf("Enter the qsortnumber of entries: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the list's elements: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    
    // quick sort
    quickSort(arr, 0, n - 1);

    printf("The sorted list: ");
    for(int i = 0; i < n; i++) 
        printf("%d ", arr[i]);
    
    return 0;
}