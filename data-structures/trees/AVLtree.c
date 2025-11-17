#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
} Node;
// allocate a new node 
Node* createNode(int key) {
    Node *n = (Node*)malloc(sizeof(Node));
    n->key = key;
    n->left = n->right = NULL;
    n->height = 1;
    return n;
}

//--------UTILITY FUNCTIONS--------//

// return height of a node 
int height(Node *n) {
    if (n == NULL) return 0;
    return n->height;
}
// inorder traversal 
void inorder(Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}
// find node with minimum key 
Node* findMin(Node *root) {
    Node *curr = root;
    while (curr->left != NULL)
        curr = curr->left;
    return curr;
}
// return max of two integers 
int max(int a, int b) {
    return (a > b) ? a : b;
}

//-----------ROTATIONS-----------//

// right rotation 
Node* rotateRight(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}
// left rotation 
Node* rotateLeft(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

//-----------BALANCING-----------//

// get balance factor of node 
int getBalance(Node *n) {
    if (n == NULL) return 0;
    return height(n->left) - height(n->right);
}
// balance the tree
Node* balance_tree(Node *root) {
    int balance = getBalance(root);

    // LL case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);
    // LR case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    // RR case
    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);
    // RL case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

//--------INSERTIONS & DELETIONS--------//

// insert key into AVL 
Node* insert(Node* root, int key) {
    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root;

    root->height = 1 + max(height(root->left), height(root->right));
    return balance_tree(root);
}
// delete key from AVL 
Node* delete(Node *root, int key) {
    if (root == NULL) return root;

    if (key < root->key)
        root->left = delete(root->left, key);
    else if (key > root->key)
        root->right = delete(root->right, key);
    else {
        if (root->left == NULL || root->right == NULL) {
            Node *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            Node *temp = findMin(root->right);
            root->key = temp->key;
            root->right = delete(root->right, temp->key);
        }
    }
    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));
    return balance_tree(root);
}

int main() {
    Node *root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("Inorder traversal: ");
    inorder(root);

    printf("\nDeleting 40\n");
    root = delete(root, 40);

    printf("Inorder traversal: ");
    inorder(root);

    return 0;
}
