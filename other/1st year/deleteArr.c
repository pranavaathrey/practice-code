#include <stdio.h>

int main(){
    int len, rem;
    scanf("%d", &len);
    int arr[len], newarr[len - 1];
    
    int flag = 0, index = 0;

    for (int i = 0; i < len; i++) {
        if (arr[i] == rem && !flag) {
            flag = 1;
            continue;
        }
        if (index < len - 1) {
            newarr[index++] = arr[i];
        }
    }

    for (int i = 0; i < len - 1; i++){
        printf("%d", newarr[i]);
    }
    
}

