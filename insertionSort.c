#include <stdio.h>

void insertionSort(int list[], int n) {
    for(int i = 1; i < n; i++) {
        int key = list[i];
        int j = i - 1;

        while(j >= 0 && list[j] > key) {
            list[j + 1] = list[j];
            j--; // compare the next element (left)
        }
        list[j + 1] = key;
    }
}

int main() {
    int n; 
    printf("Enter the number of entries: ");
    scanf("%d", &n);

    int list[n];
    printf("Enter the list's elements: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &list[i]);
    
    // insertion sort
    insertionSort(list, n);

    printf("The sorted list: ");
    for(int i = 0; i < n; i++)
        printf("%d ", list[i]);
    return 0;
}