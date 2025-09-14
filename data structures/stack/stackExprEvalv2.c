#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

void push(Stack* s, int value) {
    s->data[++s->top] = value;
}

int pop(Stack* s) {
    return s->data[s->top--];
}

int isOperator(char* token) {
    return (strlen(token) == 1 && (token[0] == '+' || token[0] == '-' || 
            token[0] == '*' || token[0] == '/'));
}

int evaluatePrefix(char* expression) {
    Stack s;
    initStack(&s);
    
    char* tokens[MAX_SIZE];
    int count = 0;
    
    char* token = strtok(expression, " ");
    while (token != NULL) {
        tokens[count++] = token;
        token = strtok(NULL, " ");
    }
    
    for (int i = count - 1; i >= 0; i--) {
        if (isOperator(tokens[i])) {
            int operand1 = pop(&s);
            int operand2 = pop(&s);
            int result;
            
            switch (tokens[i][0]) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/': result = operand1 / operand2; break;
            }
            push(&s, result);
        } else {
            push(&s, atoi(tokens[i]));
        }
    }
    return pop(&s);
}

int main() {
    char expression[1000];
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = 0;
    
    printf("%d\n", evaluatePrefix(expression));
    return 0;
}
