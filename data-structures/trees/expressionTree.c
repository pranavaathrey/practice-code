#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
    char data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int isOperator(char c) {
    return (c == '+' || c == '-' 
         || c == '*' || c == '/');
}

// Build expression tree from postfix input
Node* buildTree(char postfix[]) {
    Node* stack[100];
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isspace(postfix[i])) continue;

        if (!isOperator(postfix[i])) {
            stack[++top] = createNode(postfix[i]);
        } else {
            Node* node = createNode(postfix[i]);
            node->right = stack[top--];
            node->left = stack[top--];
            stack[++top] = node;
        }
    }
    return stack[top];
}

// ---------------TRAVERSALS--------------- //

void inorder(Node* root) {
    if (root != NULL) {
        if (isOperator(root->data)) printf("(");
        inorder(root->left);
        printf("%c", root->data);
        inorder(root->right);
        if (isOperator(root->data)) printf(")");
    }
}
void preorder(Node* root) {
    if (root != NULL) {
        printf("%c", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}
void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%c", root->data);
    }
}

// Evaluate expression tree
int evaluate(Node* root) {
    if (!isOperator(root->data))
        return root->data - '0'; 

    int leftVal = evaluate(root->left);
    int rightVal = evaluate(root->right);

    switch (root->data) {
        case '+': return leftVal + rightVal;
        case '-': return leftVal - rightVal;
        case '*': return leftVal * rightVal;
        case '/': return leftVal / rightVal;
    }
    return 0;
}

int main() {
    char postfix[256]; // eg: 96+831-/* : (9 + 6) * (8 / (3 - 1))
    printf("Enter postfix input: ");
    scanf("%s", &postfix); 

    Node* root = buildTree(postfix);

    printf("Infix   : "); inorder(root); printf("\n");
    printf("Prefix  : "); preorder(root); printf("\n");
    printf("Postfix : "); postorder(root); printf("\n");

    printf("Evaluated Result: %d\n", evaluate(root));

    return 0;
}
