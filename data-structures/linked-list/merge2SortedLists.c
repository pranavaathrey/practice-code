#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = 
            (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* insertSorted(Node* root, int data) {
    if(root == NULL)
        return createNode(data);
    if(data < root->data) {
        Node* newNode = createNode(data);
        newNode->next = root;
        return newNode;
    }            
    root->next = insertSorted(root->next, data);
    return root;
}

Node* mergeTwoLists(Node* list1, Node* list2) {
    Node* temp = list2;

    while(temp != NULL) {
        list1 = insertSorted(list1, temp->data);
        temp = temp->next;
    }
    return list1;
}
