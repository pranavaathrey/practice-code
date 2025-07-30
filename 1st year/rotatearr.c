#include <stdio.h>
#include <stdlib.h>

void rotate_array(int arr[], int size, int k, int direction){
    int *rotatedArray = (int *)malloc(size * sizeof(int));
    k = k % size;
    if(k < 0) k += size;

    if(direction == 1){
        for(int i = 0; i < size; i++){
            if(i + k >= size)
                *(rotatedArray + i + k - size) = *(arr + i);
            else
                *(rotatedArray + i + k) = *(arr + i);
        }
    }else if(direction == -1){
        for(int i = 0; i < size; i++){
            if(i - k < 0)
                *(rotatedArray + i - k + size) = *(arr + i);
            else
                *(rotatedArray + i - k) = *(arr + i);
        }
    }else  
        printf("Invalid direction.");
    
    for(int i = 0; i < size; i++){
        *(arr + i) = *(rotatedArray + i);
    }
    free(rotatedArray);
}

int main(){
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int k, direction;
    
    // User input
    printf("Enter number of positions to rotate: ");
    scanf("%d", &k);
    printf("Enter direction (1 for Right, -1 for Left): ");
    scanf("%d", &direction);

    printf("\nOriginal Array: ");
    for(int i = 0; i < size; i++)
        printf("%d ", arr[i]);

    rotate_array(arr, size, k, direction);
    printf("\nRotated Array: ");
    for(int i = 0; i < size; i++)
        printf("%d ", arr[i]);

    return 0;
}

/*
int main(){
    int N, M;
    scanf("%d", &N);
    
    int arr[N], rotatedarr[N];
    for(int i = 0; i < N; i++)
        scanf("%d", &arr[i]);
    
    scanf("%d", &M);
    for(int i = 0; i < (N + M); i++){
        if((i + M) < N)  rotatedarr[i + M] = arr[i];
        else rotatedarr[i - N] = arr[i - M];
    }
    for(int i = 0; i < N; i++)
        printf("%d ", rotatedarr[i]);
}
*/