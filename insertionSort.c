#include <stdio.h>

int main() {
    int n; 
    printf("Enter the number of entries: ");
    scanf("%d", &n);

    int list[n];
    printf("Enter the entries: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &list[i]);
    
    // insertion sort
    for(int i = 1; i < n; i++) {
        int key = list[i];
        int j = i - 1;

        while(j >= 0 && list[j] > key) {
            list[j + 1] = list[j];
            j--;
        }
        list[j + 1] = key;
    }
    printf("The sorted list: ");
    for(int i = 0; i < n; i++)
        printf("%d ", list[i]);
    return 0;
}