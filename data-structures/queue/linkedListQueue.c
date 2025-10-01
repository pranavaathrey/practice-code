#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;
 
Node* createNode(int data) {
    Node* newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void enqueue(int data, Node** front, Node** rear) {
    Node* newNode = createNode(data);

    if(*front == NULL) {
        *front = newNode;
        *rear = newNode;
        return;
    }
    (*rear)->next = newNode;
    newNode->prev = *rear;
    *rear = newNode;
}
int dequeue(Node** front) {
    if(*front == NULL) return;

    Node* temp = *front; 
    int data = (*front)->data;
    *front = (*front)->next;
    // when there's more than 1 node in the list
    if (*front != NULL) 
        (*front)->prev = NULL;
    free(temp); return data;
}

void printQueue(Node* front) {
    if(front == NULL) {
        printf("Empty list!\n");
        return;
    }
    Node* temp = front;
    while(temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
void clearQueue(Node** front) {
    while(*front != NULL) 
        dequeue(front);
}

// just a data structure, no program here