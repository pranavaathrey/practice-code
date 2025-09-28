#include <stdio.h>
#include <stdlib.h>

// doubly linked list node
typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;
 
// creates a new node with the given data
Node* createNode(int data) {
    Node* newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
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

// inserts a new node at the start of the list
void insertStart(int data, Node** head) {
    Node* newNode = createNode(data);
    
    newNode->next = *head;
    if(*head != NULL)
        (*head)->prev = newNode;
    *head = newNode;
}
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
    newNode->prev = temp;
}
// inserts a new node at index (0-based)
void insertAtIndex(int data, int index, Node** head) {    
    if(*head == NULL || index <= 0) {
        insertStart(data, head);
        return;
    }
    Node* temp = *head;
    while(index > 1 && temp->next != NULL) {
        temp = temp->next;
        index--;
    }
    Node* newNode = createNode(data);
    newNode->next = temp->next;
    if(temp->next != NULL) 
        temp->next->prev = newNode;
    temp->next = newNode;
    newNode->prev = temp;
}

//----------------||DELETION OPERATIONS||----------------//

// deletes the first node in the list
void deleteStart(Node** head) {
    if(*head == NULL) return;

    Node* temp = *head;
    *head = (*head)->next;
    // when there's more than 1 node in the list
    if (*head != NULL) 
        (*head)->prev = NULL;
    free(temp);
}
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
    temp->next = deletedNode->next;
    if(deletedNode->next != NULL)
        deletedNode->next->prev = temp;
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
    temp->next = deletedNode->next;
    if(deletedNode->next != NULL) 
        deletedNode->next->prev = temp;
    free(deletedNode);    
}
// frees memory occupied by the list
void clearList(Node** head) {
    while(*head != NULL) 
        deleteStart(head);
}


int main() {
    Node* list = NULL;
    
    printf("Doubly Linked List Menu:\n");
    printf("1: Insert Start\n2: Insert End\n3: Insert at Index\n");
    printf("4: Delete Start\n5: Delete End\n6: Delete at Index\n7: Delete by Value\n");
    printf("8: Print List\n9: Exit\n");
    
    while(1) {
        int choice; 
        printf("> Enter choice: ");
        if (scanf("%d", &choice) != 1) { 
            printf("Invalid input. Please enter a number.\n");
            // clear input buffer
            while(getchar() != '\n'); 
            continue;
        }
        
        switch(choice) {
            case 1: { // insert at start
                int data; printf("Enter data: ");
                scanf("%d", &data);
                insertStart(data, &list);
                break;
            } case 2: { // insert at end
                int data; printf("Enter data: ");
                scanf("%d", &data);
                insertEnd(data, &list);
                break;
            } case 3: { // insert at index
                int data, index; printf("Enter index and data: ");
                scanf("%d %d", &index, &data); 
                // if beyond bounds, it just inserts at nearest position.
                insertAtIndex(data, index, &list);
                break;
            } case 4: // delete at start
                deleteStart(&list);
                break;
            case 5: // delete at end
                deleteEnd(&list);
                break;
            case 6: { // delete at index
                int index; printf("Enter index: ");
                scanf("%d", &index);
                deleteAtIndex(index, &list);
                break;
            } case 7: { // delete by value
                int value; printf("Enter value: ");
                scanf("%d", &value);
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
                printf("Incorrect choice\n");
                break;
        }
    }
    return 0;
}