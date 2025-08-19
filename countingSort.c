#include <stdio.h>

void countingSort(int list[], int output[], int n) {
    int max = list[0];
    // find the maximum element
    for(int i = 1; i < n; i++)
        if(list[i] > max) 
            max = list[i];
    // create a count array & initialize to 0's
    int count[max + 1];
    for(int i = 0; i <= max; i++)
        count[i] = 0;
    // count occurrences of each element
    for(int i = 0; i < n; i++)
        count[list[i]]++;
    // get cumulative counts
    for(int i = 1; i <= max; i++)
        count[i] += count[i - 1]; 
    
    // build the output array
    for(int i = n - 1; i >= 0; i--) {
        output[count[list[i]] - 1] = list[i];
        count[list[i]]--;
    }
}

int main() {
    int n; 
    printf("Enter the number of entries: ");
    scanf("%d", &n);

    int list[n], output[n];
    printf("Enter the list's elements: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &list[i]);
    
    // counting sort
    countingSort(list, output, n);

    printf("The sorted list: ");
    for(int i = 0; i < n; i++)
        printf("%d ", output[i]);
    return 0;
}