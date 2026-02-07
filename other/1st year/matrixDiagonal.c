#include <stdio.h>

void sumMaindiagonal(int n, int matrix[][n][n], int *sum){
    for(int i = 0; i < n; i++){
        *sum += matrix[i][i][i];
    }
}

int main(){
    int rows, cols, heig;
    scanf("%d %d %d", &rows, &cols, &heig);
    
    if(rows == cols && cols == heig){
        int n = rows;
        int matrix[n][n][n];
        for(int k = 0; k < n; k++){
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    scanf("%d", &matrix[i][j][k]);
                }
            }
        }
        int sum = 0;
        sumMaindiagonal(n, matrix, &sum);
        printf("%d", sum);
    }else printf("Error");
}