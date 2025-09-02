#include <stdio.h>
#include <string.h>

void selectionSort(int list[], int n) {
    for(int i = 0; i < n - 1; i++) {
        int min = i;

        for(int j = i + 1; j < n; j++) {
            if(list[j] < list[min]) 
                min = j;
        }
        // swap
        int temp = list[i];
        list[i] = list[min];
        list[min] = temp;
    }
}

int main() {
    int n;
    printf("Enter the number of entries: ");
    scanf("%d", &n); getchar();
    
    int list[n];
    printf("Enter the list's elements: ");
    for(int i = 0; i < n; i++)
        scanf("%d", list + i);
    
    // selection sort
    selectionSort(list, n);

    printf("Sorted list: ");
    for(int i = 0; i < n; i++)
        printf("%d ", list[i]);
    
    return 0;
}
