#define MAX 100

typedef struct {
    char data[MAX];
    int stackPtr;
} Stack;

void initStack(Stack *s) { 
    s->stackPtr = -1; 
} int isEmpty(Stack *s) { 
    return s->stackPtr == -1; 
} int isFull(Stack *s) { 
    return s->stackPtr == MAX - 1; 
}
void push(Stack *s, char val) {
    if (!isFull(s)) 
        s->data[++s->stackPtr] = val;
}
char pop(Stack *s) {
    if (!isEmpty(s)) 
        return s->data[s->stackPtr--];
    return '\0';
}
char peek(Stack *s) {
    if (!isEmpty(s)) 
        return s->data[s->stackPtr];
    return '\0';
}

// just a data structure, no program here