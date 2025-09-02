#include <stdio.h>

#define MAX 100

int stack[MAX];
int stackPointer = -1;

void nextGreaterElement(int array[], int n, int nextGreater[]) {
    // traverse in reverse; pop stack until top is greater 
    // than current element - if stack is empty, print -1, 
    // otherwise print top - and push current into stack.
    
    for(int i = n - 1; i >= 0; i--) {
        while(stack[stackPointer] <= array[i] 
                && stackPointer != -1)
            stack[stackPointer--];
        
        if(stackPointer == -1) 
            nextGreater[i] = -1;
        else
            nextGreater[i] = stack[stackPointer];
        
        stack[++stackPointer] = array[i];
    }
}

int main() {
    printf("Enter the number of entries: ");
    int n; scanf("%d", &n);
    int array[n], nextGreater[n];
    
    printf("Enter the array entries: ");
    for(int i = 0; i < n; i++) 
        scanf("%d", &array[i]);
    
    nextGreaterElement(array, n, nextGreater);
    
    printf("Next greater elements: ");
    for(int i = 0; i < n; i++) 
        printf("%d ", nextGreater[i]);
}