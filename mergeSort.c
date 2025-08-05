#include <stdio.h>

void merge(int *list, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int L[n1], R[n2];
    
    // populate left & right subarrays (unsorted)
    for(int i = 0; i < n1; i++)
        L[i] = list[low + i];
    for(int j = 0; j < n2; j++)
        R[j] = list[mid + 1 + j];

    // merge the two subarrays back into the original (sorted)
    int i = 0, j = 0, k = low;
    while(i < n1 && j < n2) {
        if(L[i] <= R[j]) 
            list[k++] = L[i++];
        else 
            list[k++] = R[j++];
    }    
    while(i < n1) 
        list[k++] = L[i++];
    while(j < n2) 
        list[k++] = R[j++];
}

void mergeSort(int *list, int low, int high) {
    if(low < high) {
        int mid = low + (high - low) / 2;

        mergeSort(list, low, mid);
        mergeSort(list, mid + 1, high);

        merge(list, low, mid, high);
    }
}

int main() {
    int n;
    printf("Enter the number of entries: "); 
    scanf("%d", &n);

    int list[n];
    printf("Enter the entries: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &list[i]);
    
    // merge sort
    mergeSort(list, 0, n - 1);

    printf("The sorted list: ");
    for(int i = 0; i < n; i++)
        printf("%d ", list[i]);
    return 0;
}