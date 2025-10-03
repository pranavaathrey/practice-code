#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// create a new tree node
Node* createNode(int data) {
    if (data == -1) return NULL; // -1 means no node
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ---------TREE PROPERTIES--------- //

// returns the height/depth of tree
int height(Node* root) {
    if (!root) return 0;
    int lh = height(root->left);
    int rh = height(root->right);
    return (lh > rh ? lh : rh) + 1;
}
int countNodes(Node* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) 
        + countNodes(root->right);
}
int countLeaves(Node* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return countLeaves(root->left) 
        + countLeaves(root->right);
}

// --------BUILDING TREES-------- //

// build tree (static)
Node* buildManualTree() {
    Node* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(20);
    root->left->left = createNode(3);
    root->left->right = createNode(7);
    return root;
}

// queue for level-order tree construction
typedef struct {
    Node* arr[256];
    int front, rear;
} Queue;

void initQueue(Queue* q) {
    q->front = q->rear = 0;
}
int isEmpty(Queue* q) {
    return q->front == q->rear;
}
void enqueue(Queue* q, Node* node) {
    q->arr[q->rear++] = node;
}
Node* dequeue(Queue* q) {
    return q->arr[q->front++];
}

// build tree from level-order input
Node* buildTreeLevelOrder(int n, int arr[]) {
    if (n == 0 || arr[0] == -1) return NULL;

    Node* root = createNode(arr[0]);
    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    int i = 1;
    while (i < n) {
        Node* parent = dequeue(&q);
        
        if (i < n) { // left child
            parent->left = createNode(arr[i]);
            if (parent->left) enqueue(&q, parent->left);
            i++;
        }      
        if (i < n) { // right child
            parent->right = createNode(arr[i]);
            if (parent->right) enqueue(&q, parent->right);
            i++;
        }
    }
    return root;
}

// build tree from pre-order input (-1: null markers)
Node* buildPreorder(int arr[], int* idx, int n) {
    if (*idx >= n || arr[*idx] == -1) {
        (*idx)++;
        return NULL;
    }
    Node* root = createNode(arr[*idx]);
    (*idx)++;
    root->left = buildPreorder(arr, idx, n);
    root->right = buildPreorder(arr, idx, n);
    return root;
}

// --------TREE TRAVERSALS-------- //

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
void levelorder(Node* root) {
    if (!root) return;
    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while (!isEmpty(&q)) {
        Node* cur = dequeue(&q);
        printf("%d ", cur->data);
        if (cur->left) enqueue(&q, cur->left);
        if (cur->right) enqueue(&q, cur->right);
    }
}
// zigzag / spiral level order traversal
void zigzagTraversal(Node* root) {
    if (!root) return;
    Queue q;
    initQueue(&q);
    enqueue(&q, root);
    int leftToRight = 1; // direction flag

    while (!isEmpty(&q)) {
        int size = q.rear - q.front;
        int* level = (int*)malloc(size * sizeof(int));
        for (int i = 0; i < size; i++) {
            Node* cur = dequeue(&q);
            int idx = leftToRight ? i : (size - 1 - i);
            level[idx] = cur->data;
            if (cur->left) enqueue(&q, cur->left);
            if (cur->right) enqueue(&q, cur->right);
        }
        for (int i = 0; i < size; i++) printf("%d ", level[i]);
        free(level);
        leftToRight = !leftToRight;
    }
}

// ----------TREE SEARCH---------- //

// depth first search (recursive)
int dfs(Node* root, int key) {
    if (!root) return 0;
    if (root->data == key) return 1;
    return dfs(root->left, key) || dfs(root->right, key);
}
// breadth first search
int bfs(Node* root, int key) {
    if (!root) return 0;
    Queue q;
    initQueue(&q);
    enqueue(&q, root);
    while (!isEmpty(&q)) {
        Node* cur = dequeue(&q);
        if (cur->data == key) return 1;
        if (cur->left) enqueue(&q, cur->left);
        if (cur->right) enqueue(&q, cur->right);
    }
    return 0;
}

// --------- EXTRA BINARY TREE UTILITIES --------- //

// check if tree is BST (helper with min/max constraints)
int isBSTUtil(Node* root, int min, int max) {
    if (!root) return 1;
    if (root->data <= min || root->data >= max) return 0;
    return isBSTUtil(root->left, min, root->data) &&
           isBSTUtil(root->right, root->data, max);
}
int isBST(Node* root) {
    return isBSTUtil(root, -1e9, 1e9); // assume int range
}

// find min value in tree (any binary tree, not just BST)
int findMin(Node* root) {
    if (!root) return 1e9;
    int left = findMin(root->left);
    int right = findMin(root->right);
    int min = root->data;
    if (left < min) min = left;
    if (right < min) min = right;
    return min;
}
int findMax(Node* root) {
    if (!root) return -1e9;
    int left = findMax(root->left);
    int right = findMax(root->right);
    int max = root->data;
    if (left > max) max = left;
    if (right > max) max = right;
    return max;
}

// check if two trees are identical
int areEqual(Node* t1, Node* t2) {
    if (!t1 && !t2) return 1;
    if (!t1 || !t2) return 0;
    return (t1->data == t2->data) &&
           areEqual(t1->left, t2->left) &&
           areEqual(t1->right, t2->right);
}

// Lowest Common Ancestor (general binary tree, not BST)
Node* LCA(Node* root, int n1, int n2) {
    if (!root) return NULL;
    if (root->data == n1 || root->data == n2) return root;

    Node* left = LCA(root->left, n1, n2);
    Node* right = LCA(root->right, n1, n2);

    if (left && right) return root;
    return left ? left : right;
}

// check if tree is height-balanced
int checkBalanced(Node* root) {
    if (!root) return 0;
    int lh = checkBalanced(root->left);
    if (lh == -1) return -1;
    int rh = checkBalanced(root->right);
    if (rh == -1) return -1;
    if (abs(lh - rh) > 1) return -1;
    return (lh > rh ? lh : rh) + 1;
}
int isBalanced(Node* root) {
    return checkBalanced(root) != -1;
}

// diameter of tree (longest path between 2 nodes)
int diameterUtil(Node* root, int* height) {
    if (!root) { *height = 0; return 0; }
    int lh = 0, rh = 0;
    int ld = diameterUtil(root->left, &lh);
    int rd = diameterUtil(root->right, &rh);
    *height = (lh > rh ? lh : rh) + 1;
    int diameterThroughRoot = lh + rh + 1;
    return (ld > rd ? (ld > diameterThroughRoot ? ld : diameterThroughRoot)
                    : (rd > diameterThroughRoot ? rd : diameterThroughRoot));
}
int diameter(Node* root) {
    int h = 0;
    return diameterUtil(root, &h);
}

// --------TREE OPERATIONS-------- //

// copy tree and return copy's root node
Node* copyTree(Node* root) {
    if (root == NULL) return NULL;
    
    Node* newRoot = createNode(root->data);
    newRoot->left = copyTree(root->left);
    newRoot->right = copyTree(root->right);
    
    return newRoot;
}

// invert tree (mirror)
Node* invertTree(Node* root) {
    if (!root) return NULL;
    Node* left = invertTree(root->left);
    Node* right = invertTree(root->right);
    root->left = right;
    root->right = left;
    return root;
}

// free memory occupied by tree
void freeTree(Node* root) {
    if (root == NULL) return;
    
    freeTree(root->left);
    freeTree(root->right);
    
    free(root);
}


int main() {
    int arr[] = {10, 5, 20, 3, 7, -1, 30};
    int n = sizeof(arr)/sizeof(arr[0]);
    Node* root = buildTreeLevelOrder(n, arr);

    printf("Inorder: ");
    inorder(root); printf("\n");

    printf("Preorder: ");
    preorder(root); printf("\n");

    printf("Postorder: ");
    postorder(root); printf("\n");

    printf("Level-order: ");
    levelorder(root); printf("\n");

    printf("Height = %d\n", height(root));
    printf("Depth = %d\n", height(root) - 1);
    printf("Nodes = %d\n", countNodes(root));
    printf("Leaves = %d\n", countLeaves(root));

    printf("DFS(7) = %d\n", dfs(root, 7));
    printf("BFS(99) = %d\n", bfs(root, 99));

    Node* mirrored = copyTree(root);
    invertTree(mirrored);
    printf("Mirrored tree inorder: ");
    inorder(mirrored); printf("\n");

    printf("Is BST? %d\n", isBST(root));
    printf("Min = %d, Max = %d\n", findMin(root), findMax(root));
    printf("Is Balanced? %d\n", isBalanced(root));
    printf("Diameter = %d\n", diameter(root));

    Node* lca = LCA(root, 3, 7);
    if (lca) printf("LCA of 3 and 7 = %d\n", lca->data);

    printf("Zigzag order: ");
    zigzagTraversal(root); printf("\n");

    freeTree(root);
    freeTree(mirrored);
    return 0;
}