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

// evaluate postfix expression (single digit positive integers only)
int evaluateExpression(char postfix[]) {
    for(int i = 0; i < strlen(postfix); i++) {
        if(isdigit(postfix[i])) 
            push(postfix[i] - '0');
        else {
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
    printf("Enter postfix expression: \n(with only single digit positive integer operands)\n>> ");
    scanf("%s", &postfix);

    printf("Evaluated expression: %d", evaluateExpression(postfix));
}