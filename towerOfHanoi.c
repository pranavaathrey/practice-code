#include <stdio.h>

typedef struct {
    int rod_0;
    int rod_1;
    int rod_2;
} towerRods;

towerRods rods;

void displayDiscs(int n) {
    for(int i = 0; i < n; i++) 
        printf("|");
}

void towerOfHanoi(int n, int src, int dest, int aux) {
    static int count = 1;
    if(n == 0) 
        return;
    towerOfHanoi(n - 1, src, aux, dest);
    
    printf("\n\n#%d: Move disc %d from rod %d to rod %d", ++count, n, src, dest);
    if      (src == 0)      rods.rod_0--;
    else if (src == 1)      rods.rod_1--;
    else                    rods.rod_2--;

    if      (dest == 0)     rods.rod_0++;
    else if (dest == 1)     rods.rod_1++;
    else                    rods.rod_2++;

    printf("\nCurrent state: ");
    printf("\n\trod 0: (%d) ", rods.rod_0); displayDiscs(rods.rod_0);
    printf("\n\trod 1: (%d) ", rods.rod_1); displayDiscs(rods.rod_1);
    printf("\n\trod 2: (%d) ", rods.rod_2); displayDiscs(rods.rod_2);

    towerOfHanoi(n - 1, aux, dest, src);
}

int main() {
    printf("Enter the number of discs: ");
    scanf("%d", &rods.rod_0);
    rods.rod_1 = 0; rods.rod_2 = 0;

    printf("\n#1: Initial state: ");
    printf("\n\trod 0: (%d) ", rods.rod_0); displayDiscs(rods.rod_0);
    printf("\n\trod 1: (%d) ", rods.rod_1); displayDiscs(rods.rod_1);
    printf("\n\trod 2: (%d) ", rods.rod_2); displayDiscs(rods.rod_2);

    towerOfHanoi(rods.rod_0, 0, 2, 1);
    printf("\n\nDiscs moved successfully.");
    return 0;
}