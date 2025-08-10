#include <stdio.h>
#include <stdlib.h>

int main() {
    for(int i = 0; i <= 39999; i++) {
        printf("%-5d ", i);
        if(i % 10 == 9) 
            printf("\n");
    }    
    return 0;
}