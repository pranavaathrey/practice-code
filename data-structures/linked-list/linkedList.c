#include <stdio.h>
#include <stdlib.h>

// singly linked list node
typedef struct Node {
    int data;
    struct Node *next;
} Node;
 
// creates a new node with the given data
Node* createNode(int data) {
    Node* newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
// prints the contents of the linked list
void printList(Node* head) {
    if(head == NULL) {
        printf("Empty list!\n");
        return;
    }
    Node* temp = head;
    while(temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

//----------------||INSERTION OPERATIONS||----------------//

// inserts a new node at the end of the list
void insertEnd(int data, Node** head) {
    Node* newNode = createNode(data);
    
    if(*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    // traverse to the last node
    while(temp->next != NULL) 
        temp = temp->next;
    temp->next = newNode;
}
// inserts a new node at the start of the list
void insertStart(int data, Node** head) {
    Node* newNode = createNode(data);
    
    newNode->next = *head;
    *head = newNode;
}

// inserts a new node at index (0-based)
void insertAtIndex(int data, int index, Node** head) {
    Node* newNode = createNode(data);
    
    if(*head == NULL || index <= 0) {
        insertStart(data, head);
        return;
    }
    Node* temp = *head;
    while(index > 1 && temp->next != NULL) {
        temp = temp->next;
        index--;
    }
    Node* nextNode = temp->next;
    temp->next = newNode;
    newNode->next = nextNode;
}

//----------------||DELETION OPERATIONS||----------------//

// deletes the last node in the list
void deleteEnd(Node** head) {    
    if(*head == NULL) return;
    else if((*head)->next == NULL) {
        deleteStart(head);
        return;
    }    
    Node* temp = *head;
    // traverse to the second-to-last node
    while(temp->next->next != NULL) 
        temp = temp->next;
    free(temp->next);
    temp->next = NULL;
}
// deletes the first node in the list
void deleteStart(Node** head) {
    if(*head == NULL) return;

    Node* temp = *head;
    *head = (*head)->next;
    free(temp);
}

// deletes the node at index (0-based)
void deleteAtIndex(int index, Node** head) {   
    if(*head == NULL || index <= 0) {
        deleteStart(head);
        return;
    }
    Node* temp = *head;
    while(index > 1 && temp->next != NULL) {
        temp = temp->next;
        index--;
    }
    if(temp->next == NULL) return; // out of bounds

    Node* deletedNode = temp->next;
    temp->next = temp->next->next;
    free(deletedNode);
}
// deletes the first occurrence of a node with given value
void deleteByValue(int value, Node** head) {   
    if(*head == NULL || (*head)->data == value) {
        deleteStart(head);
        return;
    }
    Node* temp = *head;
    while(temp->next != NULL 
        && temp->next->data != value) 
        temp = temp->next;

    if(temp->next == NULL) return; // not found

    Node* deletedNode = temp->next;
    temp->next = temp->next->next;
    free(deletedNode);    
}
// frees memory occupied by the list
void clearList(Node** head) {
    while(*head != NULL) 
        deleteStart(head);
}


int main() {
    Node* list = NULL;
    
    while(1) {
        int choice; scanf("%d", &choice);
        
        switch(choice) {
            case 1: { // insert at start
                int data; scanf("%d", &data);
                insertStart(data, &list);
                break;
            } case 2: { // insert at end
                int data; scanf("%d", &data);
                insertEnd(data, &list);
                break;
            } case 3: { // insert at index
                int data, index; 
                scanf("%d %d", &index, &data); 
                insertAtIndex(data, index, &list);
                break;
            } case 4: // delete at start
                deleteStart(&list);
                break;
            case 5: // delete at end
                deleteEnd(&list);
                break;
            case 6: { // delete at index
                int index; scanf("%d", &index);
                deleteAtIndex(index, &list);
                break;
            } case 7: { // delete by value
                int value; scanf("%d", &value);
                deleteByValue(value, &list);
                break;
            } case 8: // print list
                printList(list);
                break;
            case 9: // exit program
                clearList(&list);
                printf("Exiting\n");
                return 0;
            default:
                printf("Wrong choice\n");
                break;
        }
    }
    return 0;
}
