#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void printList(Node *head) {
    if(head == NULL) return;

    Node* temp = head;
    while(temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void insertStart(int data, Node** head) {
    Node* newNode = createNode(data);
    if(*head == NULL) {
        *head = newNode;
        return;
    }
    newNode->next = *head;
    (*head)->prev = newNode;
    *head = newNode;
}

void insertEnd(int data, Node** head) {
    Node* newNode = createNode(data);
    if(*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while(temp->next != NULL)
        temp = temp->next;  

    temp->next = newNode;
    newNode->prev = temp;
}

void insertAtIndex(int data, int index, Node** head) {
    if(*head == NULL) 
        return;
    Node* newNode = createNode(data);

    Node* temp = *head;
    while(index > 0 && temp != NULL) {
        temp = temp->next;  
        index--;
    }
    if(temp == NULL) return;
    if(temp == *head) {
        insertStart(data, head);
        return;
    }
    newNode->next = temp;
    newNode->prev = temp->prev;
    temp->prev->next = newNode;
    temp->prev = newNode;
}