#include <stdio.h>

int main() {
    int rows = 5, columns = 6;
    int arr[5][6] = {
        1,  2,  3,  4,  5,  6,
        18, 19, 20, 21, 22, 7,
        17, 28, 29, 30, 23, 8,
        16, 27, 26, 25, 24, 9,
        15, 14, 13, 12, 11, 10,
    };

    // print spiral matrix
    int dir = 0;
    for(int i = 0; i < rows; i++) {
        dir = !dir;
        if(dir)
            for(int j = 0; j < columns; j++) 
                printf("%-2d ", arr[i][j]);
        else            
            for(int j = 0; j < columns; j++) 
                printf("%-2d ", arr[j][i]);
        printf("\n");
    }
}
// TODO: finish this