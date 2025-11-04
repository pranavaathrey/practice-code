#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// stack data structure (using arrays)
int stack[MAX];
int stackPointer = -1;

void push(int val) {
    if(stackPointer < MAX - 1)
        stack[++stackPointer] = val;
}
int pop() {
    if(stackPointer < 0)
        return 0;
    return stack[stackPointer--];
}

// evaluate postfix expression 
int evaluateExpression(char postfix[]) {
    int len = strlen(postfix);    
    int currNum = 0;

    for(int i = 0; i < len; i++) {
        if(isdigit(postfix[i])) {
            currNum = (currNum * 10) + (postfix[i] - '0');

            if(i + 1 < len && !isdigit(postfix[i + 1])) {
                push(currNum);
                currNum = 0;
            }
        } else if(postfix[i] != ' ') {
            int rightOperand = pop();
            int leftOperand = pop();

            if(postfix[i] == '+')
                push(leftOperand + rightOperand);
            else if (postfix[i] == '-')
                push(leftOperand - rightOperand);
            else if (postfix[i] == '*')
                push(leftOperand * rightOperand);
            else if (postfix[i] == '/')
                push(leftOperand / rightOperand);
        }
    }
    return pop();
}

int main() {
    char postfix[MAX];
    printf("Enter postfix expression: \n(In this format: 6 23 1 + * 2 /)\n>> ");

    fgets(postfix, MAX, stdin);
    postfix[strlen(postfix) - 1] = '\0';

    printf("Evaluated expression: %d", evaluateExpression(postfix));
}