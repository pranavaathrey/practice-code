#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

Node* insertEnd(int data, Node** head) {
    Node* newNode = createNode(data);
    if(*head == NULL) {
        *head = newNode;
        return newNode;
    }
    Node* temp = *head;
    while(temp->next != NULL) 
        temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
    return newNode;
}

int isPalindrome(Node* head, Node* rear) {
    while(head != NULL && rear != NULL &&
        head != rear && head->prev != rear) {
        if(head->data != rear->data)
            return 0;
        head = head->next;
        rear = rear->prev;
    }
    return 1;
}
 
void printList(Node* head) {
    if(head == NULL) {
        printf("List empty!\n");
        return;
    }
    Node* temp = head;
    while(temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
void printRevList(Node* rear) {
    if(rear == NULL) {
        printf("List empty!\n");
        return;
    }
    Node* temp = rear;
    while(temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

int main() {
    printf("Enter the number of entries: ");
    int n; scanf("%d", &n);
    
    printf("Enter list: ");
    Node *listHead = NULL;
    Node *listRear = NULL;
    while(n--) {
        int data; scanf("%d", &data);
        listRear = insertEnd(data, &listHead);
    }
    printList(listHead);
    printRevList(listRear);
    
    if(isPalindrome(listHead, listRear)) 
        printf("The doubly linked list is a palindrome\n");
    else
        printf("The doubly linked list is not a palindrome\n");
    return 0;
}