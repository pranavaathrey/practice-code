#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 101

// separate chaining - linked list
typedef struct Node {
    char *value;
    struct Node *next;
} Node;

// hash table
Node *table[TABLE_SIZE];
// hashing function (djb2-like)
unsigned int hash(const char *s) {
    unsigned int h = 0;
    while (*s) 
        h = h * 31 + *s++;
    return h % TABLE_SIZE;
}

// -----------SET FUNCTIONS-----------//

int contains(const char *s) {
    unsigned int idx = hash(s);
    Node *cur = table[idx];

    while (cur) {
        if (strcmp(cur->value, s) == 0) 
            return 1;
        cur = cur->next;
    }
    return 0;
}

void insert(const char *s) {
    if (contains(s)) 
        return;  // enforce no duplicates
        
    unsigned int idx = hash(s);
    Node *n = malloc(sizeof(Node));

    n->value = strdup(s);
    n->next = table[idx];
    table[idx] = n;
}
void delete(const char *s) {
    unsigned int idx = hash(s);
    Node *cur = table[idx];
    Node *prev = NULL;

    while(cur) {
        if(strcmp(cur->value, s) == 0) {
            if(prev) 
                prev->next = cur->next;
            else 
                table[idx] = cur->next;            
            free(cur->value);
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

void printSet() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *cur = table[i];
        while (cur) {
            printf("%s\n", cur->value);
            cur = cur->next;
        }
    }
}
void freeSet() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *cur = table[i];

        while (cur) {
            Node *next = cur->next;
            free(cur->value);
            free(cur);
            cur = next;
        }
        table[i] = NULL;
    }
}

int main() {
    insert("apple");
    insert("banana");
    insert("cherry");
    delete("banana");
    insert("apple");

    printSet();
    freeSet();

    return 0;
}