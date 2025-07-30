#include <stdio.h>
#include <stdlib.h>

int binarySearch(int *list, int n, int key) {
    int low = 0, high = n-1, mid;
    
    while(low <= high) {
        mid = low + (high - low) / 2;
        
        if(list[mid] == key)
            return mid;
        if(list[mid] < key)
            low = mid + 1;
        if(list[mid] > key)
            high = mid - 1;
    }
    // key not present, but still return the closest index
    if(low >= n) low = n - 1;
    if(high < 0) high = 0;

    if((abs(key - list[low]) <= abs(key - list[high])))
        return low;
    else 
        return high;
}

int main() {
    printf("Enter the number of entries: ");
    int entries;
    scanf("%d", &entries);
    
    printf("Enter the entries in a sorted order: ");
    int list[entries];
    for(int i = 0; i < entries; i++)
        scanf("%d", list + i);
    
    printf("Enter the key and number of results to return: ");
    int key, numberOfResults;
    scanf("%d %d", &key, &numberOfResults);
    
    int centre = binarySearch(list, entries, key);
    int left = centre, right = centre;

    printf("%d ", list[centre]);
    numberOfResults--;

    while(numberOfResults > 0) {
        if(left > 0 && (right >= entries - 1
        || (abs(key - list[left - 1]) <= abs(key - list[right + 1])) ))
            printf("%d ", list[--left]);
        else if(right < entries - 1) 
            printf("%d ", list[++right]);
        else
            break; // run out of elements
        numberOfResults--;
    }
    return 0;
}