#include <stdio.h>

int swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int list[], int left, int right) {
    swap(&list[left + (right - left)/2], &list[right]);
    int pivot = list[right];

    int i = left - 1;
    for(int j = left; j < right; j++) {
        if(list[j] < pivot) {
            i++;
            swap(&list[i], &list[j]);
        }
    }
    swap(&list[i + 1], &list[right]);
    return i + 1;
}

void quickSort(int list[], int left, int right) {
    if(left < right) {
        int pi = partition(list, left, right);

        quickSort(list, left, pi - 1);
        quickSort(list, pi + 1, right);
    }
}

int main() {
    int n; scanf("%d", &n);

    int arr[n];
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    
    // quick sort
    quickSort(arr, 0, n - 1);

    printf("The sorted list: ");
    for(int i = 0; i < n; i++) 
        printf("%d ", arr[i]);
    
    return 0;
}