#include <stdio.h>

int main() {
    int n; 
    printf("Enter the number of entries: ");
    scanf("%d", &n);

    int list[n];
    printf("Enter the entries: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &list[i]);
    
    // counting sort
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
    int output[n]; 
    for(int i = n - 1; i >= 0; i--) {
        output[count[list[i]] - 1] = list[i];
        count[list[i]]--;
    }

    printf("The sorted list: ");
    for(int i = 0; i < n; i++)
        printf("%d ", output[i]);
    return 0;
}