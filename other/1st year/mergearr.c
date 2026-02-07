#include <stdio.h>

int main(){
    int N, M;
    
    // input arrays are already sorted
    scanf("%d", &N);
    int arr[N];
    for(int i = 0; i < N; i++)
        scanf("%d", &arr[i]);
    
    scanf("%d", &M);
    int brr[M];
    for(int i = 0; i < M; i++)
        scanf("%d", &brr[i]);
    
    // actual merging
    int merr[N + M], i = 0, j = 0, k = 0;
    while(i < N && j < M){
        if(arr[i] < brr[j]) merr[k++] = arr[i++];
        else merr[k++] = brr[j++];
    }
    // if there are remaining elements in arr[]
    while (i < N) merr[k++] = arr[i++];
    // if there are remaining elements in brr[]
    while (j < M) merr[k++] = brr[j++];

    for(int i = 0; i < (N + M); i++)
        printf("%d ", merr[i]);
}