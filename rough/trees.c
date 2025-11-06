#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void inorder(Node* root) {
    if(root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

Node* findMin(Node* root) {
    while(root && root->left) 
        root = root->left;
    return root;
}

Node* insert(Node* root, int data) {
    if(!root) return createNode(data);

    if(root->data < data)
        root->right = insert(root->right, data);
    else if(root->data > data)
        root->left = insert(root->left, data);
    
    return root;
}

Node* delete(Node* root, int key) {
    if(!root) return root;

    if(root->data < key) 
        root->right = delete(root->right, key);
    else if(root->data > key) 
        root->left = delete(root->left, key);
    else {
        if(root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        if(root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = delete(root->right, root->data);
    }
    return root;
}

void kthMinUtil(Node* root, int k, int *count, int *result) {
    if(!root || *result != -1) return;

    kthMinUtil(root->left, k, count, result);
    (*count)++;
    if(*count == k) {
        *result = root->data;
        return;
    }
    kthMinUtil(root->right, k, count, result);
}
int kthMin(Node*root, int k) {
    int count = 0, result = -1;
    kthMinUtil(root, k, &count, &result);
    return result;
}

