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
void insertEnd(Node **head, int data) {
    Node* newNode = createNode(data);
    if(*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while(temp->next != NULL) 
        temp = temp->next;
    temp->next = newNode;
}

int binaryToDecimal(Node *head) {
    int decimal = 0;
    while(head != NULL) {
        decimal = decimal * 2 + head->data;
        head = head->next;
    }
    return decimal;
}

int main() {
    int n, bit;
    Node *head = NULL;
    
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &bit);
        insertEnd(&head, bit);
    }
    if(head == NULL) {
        printf("List is empty");
        return 0;
    }
    printf("%d", binaryToDecimal(head));
    return 0;
}




