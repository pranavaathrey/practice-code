#include <stdio.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int stackPtr = -1;

int isValid(char* str) {
    int stack[256];
    int stackPtr = -1;
    int len = strlen(str);

    for(int i = 0; i < len; i++) {
        if(str[i] == '(' || str[i] == '[' || str[i] == '{')
            stack[++stackPtr] = str[i];
        else if(str[i] == ')') 
            if(stackPtr < 0 || stack[stackPtr--] != '(') return 0;
        else if(str[i] == ']') 
            if(stackPtr < 0 || stack[stackPtr--] != '[') return 0;
        else if(str[i] == '}') 
            if(stackPtr < 0 || stack[stackPtr--] != '{') return 0;
    }
    return (stackPtr == -1);
}

int main() {
    printf("Enter expression: ");
    char brackets[MAX];
    fgets(brackets, MAX, stdin);
    
    if(isValid(brackets))
        printf("Brackets are balanced.");
    else
        printf("Brackets are not balanced.");
    
    return 0;
}