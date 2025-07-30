#include <stdio.h>
#include <string.h>

#define MAX_SIZE 99

int main() {
    int n;
    printf("Enter the number of entries: ");
    scanf("%d", &n); getchar();
    
    char strings[n][MAX_SIZE];
    printf("Enter the strings: ");
    for(int i = 0; i < n; i++)
        scanf("%s", strings + i);
    
    // bubble sort
    while(1) {
        int flag = 0;
        for(int i = 0; i < n - 1; i++) {
            if(strcmpi(strings[i + 1], strings[i]) < 0) {
                char temp[MAX_SIZE];
                strcpy(temp, strings[i]);
                strcpy(strings[i], strings[i + 1]);
                strcpy(strings[i + 1], temp);
                flag = 1;
            }
        }
        if(flag == 0) break;
    }

    printf("Sorted Alphabetically: ");
    for(int i = 0; i < n; i++)
        printf("%s ", strings[i]);
    
    return 0;
}
