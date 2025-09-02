#include <stdio.h>
#include <string.h>

#define MAX_ENTRIES 100
#define MAX_LENGTH 100

int binarySearch(char list[MAX_ENTRIES][MAX_LENGTH], char key[MAX_LENGTH], int high, int low) {
    if(low <= high) {
        int mid = low + (high - low) / 2;
        int comp = strcmp(list[mid], key);

        if(comp == 0)
            return mid;
        else if(comp < 0)
            return binarySearch(list, key, mid - 1, low);
        else
            return binarySearch(list, key, high, mid + 1);
    } else  
        return -1;
}

int main() {
    int n;
    printf("Enter the number of entries: ");
    scanf("%d", &n);

    char list[MAX_ENTRIES][MAX_LENGTH];
    printf("Enter the strings:\n");
    for(int i = 0; i < n; i++)
        scanf("%s", list[i]);

    printf("Enter the string to search: ");
    char key[MAX_LENGTH];
    scanf("%s", key);

    int result = binarySearch(list, key, n - 1, 0);
    if(result != -1)
        printf("Found %s at index %d\n", key, result);
    else
        printf("Not Found\n");

    return 0;
}