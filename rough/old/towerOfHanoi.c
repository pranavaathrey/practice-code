#include <stdio.h>

void towerOfHanoi(int n, int src, int dest, int aux) {
    if(n == 0) 
        return;
    towerOfHanoi(n - 1, src, aux, dest);
    printf("Move disc %d from rod %d to rod %d\n", n, src, dest);
    towerOfHanoi(n - 1, aux, dest, src);
}

int main() {
    printf("Enter the number of discs: ");
    int discCount; scanf("%d", &discCount);

    towerOfHanoi(discCount, 0, 2, 1);
    return 0;
}


