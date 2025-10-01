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
void printReversedList(Node* head) {
    if(head == NULL) {
        printf("EMPTY");
        return;
    }
    Node* temp = head;
    while(temp->next != NULL) 
        temp = temp->next;
    
    while(temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

void insertStart(int data, Node** head) {
    Node* newNode = createNode(data);
    
    newNode->next = *head;
    if(*head != NULL)
        (*head)->prev = newNode;
    *head = newNode;
}

Node* removeDuplicates(Node* head) {
    Node* uniques = NULL;
    
    Node* i = head;
    while(i != NULL) {
        Node* j = uniques;
        int unique = 1;
        while(j != NULL) {
            if(j->data == i->data) {
                unique = 0;
                break;
            } else j = j->next;
        }
        if(unique) 
            insertStart(i->data, &uniques);
        i = i->next;
    }
    return uniques;
}

int main() {
    printf("Enter the number of entries: ");
    int n; scanf("%d", &n);
    
    printf("Enter list: ");
    Node *list = NULL;
    while(n--) {
        int data; scanf("%d", &data);
        insertStart(data, &list);
    }
    Node *uniques = removeDuplicates(list);
    
    printReversedList(uniques);
    return 0;
}
