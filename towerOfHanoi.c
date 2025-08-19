#include <stdio.h>

typedef struct {
    int rod_0;
    int rod_1;
    int rod_2;
} towerRods;

towerRods rods;

void towerOfHanoi(int n, int src, int dest, int aux) {
    static int count = 1;
    if(n == 0) 
        return;
    towerOfHanoi(n - 1, src, aux, dest);
    
    printf("#%d: Move disc %d from rod %d to rod %d\n", ++count, n, src, dest);
    if      (src == 0)      rods.rod_0--;
    else if (src == 1)      rods.rod_1--;
    else                    rods.rod_2--;

    if      (dest == 0)     rods.rod_0++;
    else if (dest == 1)     rods.rod_1++;
    else                    rods.rod_2++;

    printf("Current state: \n\trod 0 = %d\n\trod 1 = %d\n\trod 2 = %d\n\n", 
        rods.rod_0, rods.rod_1, rods.rod_2);

    towerOfHanoi(n - 1, aux, dest, src);
}

int main() {
    printf("Enter the number of discs: ");
    scanf("%d", &rods.rod_0);
    rods.rod_1 = 0; rods.rod_2 = 0;

    printf("#1: Initial state: \n\trod 0 = %d\n\trod 1 = %d\n\trod 2 = %d\n\n", 
        rods.rod_0, rods.rod_1, rods.rod_2);
    towerOfHanoi(rods.rod_0, 0, 2, 1);
    printf("Discs moved successfully.");
    return 0;
}