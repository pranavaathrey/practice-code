#include <stdio.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int stackPtr = -1;

int isBracket(char input) {
    if(input == ')' || input == '('
    || input == ']' || input == '['
    || input == '}' || input == '{')
        return 1;
    return 0;
}

int main() {
    printf("Enter expression: ");
    char brackets[MAX];
    fgets(brackets, MAX, stdin);
    
    int len = strlen(brackets);
    for(int i = 0; i < len && stackPtr >= -1; i++) {
        if(brackets[i] == '('
        || brackets[i] == '['
        || brackets[i] == '{')
            stack[++stackPtr] = brackets[i];
        else if((brackets[i] == ')' && stack[stackPtr] == '(')
             || (brackets[i] == ']' && stack[stackPtr] == '[')
             || (brackets[i] == '}' && stack[stackPtr] == '{'))
            stack[stackPtr--];
        else if(!isBracket(brackets[i]))
            continue;
        else
            break;
    }
    
    if(stackPtr == -1)
        printf("Brackets are balanced.");
    else
        printf("Brackets are not balanced.");
    
    return 0;
}