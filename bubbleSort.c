#include <stdio.h>
#include <string.h>

#define MAX_SIZE 99

int main() {
    int n, flag;
    printf("Enter the number of entries: ");
    scanf("%d", &n); getchar();
    
    char strings[n][MAX_SIZE];
    printf("Enter the strings: ");
    for(int i = 0; i < n; i++)
        scanf("%s", strings + i);
    
    // bubble sort
    do{ flag = 0;
        for(int i = 0; i < n - 1; i++) 
            if(strcmpi(strings[i + 1], strings[i]) < 0) {
                char temp[MAX_SIZE];
                strcpy(temp, strings[i]);
                strcpy(strings[i], strings[i + 1]);
                strcpy(strings[i + 1], temp);
                flag = 1;
            }
    } while(flag != 0);

    printf("Sorted Alphabetically: ");
    for(int i = 0; i < n; i++)
        printf("%s ", strings[i]);
    
    return 0;
}
