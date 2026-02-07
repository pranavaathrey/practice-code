#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void display(Node* head) {
    if(head==NULL) return;
    Node* temp=head;
    do {
        printf("%d ",temp->data);
        temp=temp->next;
    } while(temp!=head);
    printf("\n");
}

void insert(Node** head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    
    if (*head == NULL) {
        *head = newNode;
        newNode->next = *head; 
    } else {
        Node* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head;  
    }
}

void filterEvenDigitSums(Node **head) {
    if(*head == NULL) return;
    Node *curr = *head;
    Node *prev = NULL;
    do {
        int digitSum = 0, n = curr->data;
        while(n != 0) {
            digitSum += n % 10;
            n /= 10;
        }
        Node *nextNode = curr->next;
        if(digitSum % 2 == 0) {
            if(curr->next == curr) {
                free(curr);
                *head = NULL;
                return;
            } if(curr == *head) {
                Node *last = *head;
                while (last->next != *head) 
                    last = last->next;
                *head = curr->next;
                last->next = *head;
                free(curr);
                curr = *head;
                continue;
            }
            prev->next = curr->next;
            free(curr);
            curr = nextNode;
            continue;
        }
        prev = curr;
        curr = nextNode;
    } while(curr != *head);
}

int main() {
    Node* head = NULL;
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        int value;
        scanf("%d", &value);
        insert(&head, value);
    }
    filterEvenDigitSums(&head);
    display(head);
    return 0;
}
