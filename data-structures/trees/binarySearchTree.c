#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;
// create a new tree node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// -----------TRAVERSALS----------- //

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
void preorder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}
void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// -----------OPERATIONS----------- //

// insert a node into BST
Node* insert(Node* root, int data) {
    if (root == NULL) 
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root; // unchanged root pointer
}
// delete a node
Node* delete(Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->data)
        root->left = delete(root->left, key);
    else if (key > root->data)
        root->right = delete(root->right, key);
    else { // node found
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } 
        if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        // two children: replace with inorder successor
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}

// search in BST
Node* search(Node* root, int key) {
    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}
// find minimum node
Node* findMin(Node* root) {
    while (root && root->left != NULL)
        root = root->left;
    return root;
}
// find maximum node
Node* findMax(Node* root) {
    while (root && root->right != NULL)
        root = root->right;
    return root;
}

// Finding kth minimum (inorder traversal)
void kthMinUtil(Node* root, int k, int* count, int* result) {
    if (root == NULL || *result != -1) return;

    kthMinUtil(root->left, k, count, result);
    (*count)++;
    if (*count == k) {
        *result = root->data;
        return;
    }
    kthMinUtil(root->right, k, count, result);
}
int kthMin(Node* root, int k) {
    int count = 0, result = -1;
    kthMinUtil(root, k, &count, &result);
    return result;
}

// Finding kth maximum (reverse inorder traversal)
void kthMaxUtil(Node* root, int k, int* count, int* result) {
    if (root == NULL || *result != -1) return;

    kthMaxUtil(root->right, k, count, result);
    (*count)++;
    if (*count == k) {
        *result = root->data;
        return;
    }
    kthMaxUtil(root->left, k, count, result);
}
int kthMax(Node* root, int k) {
    int count = 0, result = -1;
    kthMaxUtil(root, k, &count, &result);
    return result;
}

// copy tree into new root
Node* copyTree(Node* root) {
    if (root == NULL) return NULL;

    Node* newRoot = createNode(root->data);
    newRoot->left = copyTree(root->left);
    newRoot->right = copyTree(root->right);
    return newRoot;
}
// free entire tree
void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    Node* root = NULL;

    // insert nodes
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) {
        root = insert(root, values[i]);
    }
    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    printf("Preorder traversal: ");
    preorder(root);
    printf("\n");

    printf("Postorder traversal: ");
    postorder(root);
    printf("\n");

    // Search test
    int key = 40;
    Node* found = search(root, key);
    if (found) printf("Found %d in BST\n", key);
    else printf("%d not found in BST\n", key);

    // Delete test
    root = delete(root, 20);
    printf("Inorder after deleting 20: ");
    inorder(root);
    printf("\n");

    root = delete(root, 30);
    printf("Inorder after deleting 30: ");
    inorder(root);
    printf("\n");

    root = delete(root, 50);
    printf("Inorder after deleting 50: ");
    inorder(root);
    printf("\n");

    freeTree(root);
    return 0;
}
