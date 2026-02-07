#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
void insertEnd(int data, Node** head) {
    Node *newNode = createNode(data);
    
    if(*head == NULL) {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while(temp->next != NULL) 
        temp = temp->next;
    temp->next = newNode;
}
void insertStart(int data, Node** head) {
    Node *newNode = createNode(data);
    
    newNode->next = *head;
    *head = newNode;
}

void printList(Node *head) {
    Node *temp = head;
    while(temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

int main() {
    int n; scanf("%d", &n);
    
    Node *oddList = NULL, *evenList = NULL;
    for(int i = 0; i < n; i++) {
        int data; scanf("%d", &data);
        
        if(data % 2 == 0)
            insertStart(data, &evenList);
        else
            insertStart(data, &oddList);
    }
    printList(evenList);
    printList(oddList);
    
    return 0;
}









