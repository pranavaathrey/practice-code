#define MAX 100

typedef struct {
    char data[MAX];
    int top;
} Stack;

void initStack(Stack *s) { 
    s->top = -1; 
} int isEmpty(Stack *s) { 
    return s->top == -1; 
} int isFull(Stack *s) { 
    return s->top == MAX - 1; 
}
void push(Stack *s, char val) {
    if (!isFull(s)) 
        s->data[++s->top] = val;
}
char pop(Stack *s) {
    if (!isEmpty(s)) 
        return s->data[s->top--];
    return '\0';
}
char peek(Stack *s) {
    if (!isEmpty(s)) 
        return s->data[s->top];
    return '\0';
}

// just a data structure, no program here