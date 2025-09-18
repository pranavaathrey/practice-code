#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// stack data structure (using arrays)
char stack[MAX]; // <-- stores operators
int stackPointer = -1;
void push(char val) {
    if(stackPointer < MAX - 1)
        stack[++stackPointer] = val;
}
char pop() {
    if(stackPointer < 0)
        return 0;
    return stack[stackPointer--];
}

int priority(char operator) {
    switch (operator) {
        case '^': return 3;
        break;

        case '/': 
        case '*': return 2;
        break;

        case '+': 
        case '-': return 1;
        break;

        case '(': return 0;
        break;
    }
    return -1;
}
void reverseString(char *str) {
    int len = strlen(str);
    
    for(int i = 0; i < len / 2; i++) {
        char tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
}

char infix[MAX], postfix[MAX];
void infixToPostfix() {
    int length = strlen(infix);
    int postfixPointer = -1;

    for(int i = 0; i < length; i++) {
        if(isdigit(infix[i])) { // on a digit
            postfix[++postfixPointer] = infix[i];

            if(!isdigit(infix[i + 1]) && (i + 1) < length) 
                postfix[++postfixPointer] = ' ';
        } 
        else if(priority(infix[i]) > 0) { // on an operator
            while (priority(infix[i]) <= priority(stack[stackPointer])) {
                postfix[++postfixPointer] = pop();
                postfix[++postfixPointer] = ' ';
            }
            push(infix[i]);
        }
        else if(infix[i] == '(') { // on an open parenthesis
            push(infix[i]);
        } else if(infix[i] == ')') { // on a close parenthesis
            while(stack[stackPointer] != '(') {
                postfix[++postfixPointer] = pop();
                postfix[++postfixPointer] = ' ';
            }
            if(stack[stackPointer] == '(')
                pop();
        }
    }
    while(stackPointer != -1) {
        postfix[++postfixPointer] = pop();
        postfix[++postfixPointer] = ' ';
    }
    postfix[++postfixPointer] = '\0'; // null terminate
    stackPointer = -1; // clearing memory
}
void infixToPrefix() {
    reverseString(infix);
    // swap parentheses
    for (int i = 0; i < strlen(infix); i++) {
        if (infix[i] == '(') 
            infix[i] = ')';
        else if (infix[i] == ')') 
            infix[i] = '(';
    }
    infixToPostfix();
    reverseString(postfix);
}

int main() {
    printf("Enter infix expression, in a format like this: 6 * (23 + 1) / 2\n>> ");
    fgets(infix, MAX, stdin);
    infix[strcspn(infix, "\n")] = '\0';
    
    // quite preposterous
    infixToPostfix();
    printf("Postfix expression: %s\n", postfix);
    infixToPrefix();
    printf("Prefix expression: %s\n", postfix);
}