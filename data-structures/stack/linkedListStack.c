#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void push(int data, Node** top) {
    Node* newNode = createNode(data);
    
    newNode->next = *top;
    *top = newNode;
}
int pop(Node** top) {
    if(*top == NULL) {
        printf("Stack empty!\n");
        return -1;
    }
    Node* temp = *top; int data = temp->data;
    *top = (*top)->next;
    free(temp); return data;
}

void printStack(Node* top) {
    Node* temp = top;
    while(temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
void clearStack(Node** top) {
    while(*top != NULL) 
        pop(top);
}

// just a data structure, no program here