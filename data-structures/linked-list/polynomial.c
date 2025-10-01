#include <stdio.h>
#include <stdlib.h>

typedef struct Term {
    float coefficient;
    int exponent;
    struct Term* next;
} Term;

// creates new term for use in polynomial
Term* createTerm(float co, int exp) {
    Term* newTerm = (Term *)malloc(sizeof(Term));
    newTerm->coefficient = co;
    newTerm->exponent = exp;
    newTerm->next = NULL;
    return newTerm;
}
// displays currently stored polynomial
void printPolynomial(Term* head) {
    if(head == NULL) {
        printf("Empty polynomial!\n");
        return;
    }
    Term* temp = head;
    while(temp != NULL) {
        printf("(%.1fx^%d)", 
            temp->coefficient, temp->exponent);
        if (temp->next == NULL) 
             printf(" ");
        else printf(" + ");

        temp = temp->next;
    }
    printf("\n");
}
// inserts at the sorted position (descending exponents)
void insert(Term** head, float co, int exp) {
    Term* newTerm = createTerm(co, exp);

    if(*head == NULL || exp > (*head)->exponent) {
        newTerm->next = *head;
        *head = newTerm;
        return;
    } 
    Term* temp = *head;
    while(temp->next != NULL 
            && temp->next->exponent > exp)
        temp = temp->next;
    newTerm->next = temp->next;
    temp->next = newTerm;
}

int main() {
    printf("Enter the number of terms in the polynomial: ");
    int n, i = 1; scanf("%d", &n);

    Term* head = NULL;
    while(n--) {
        printf("Enter the coefficient and exponent for term %d: ", i++);
        float coefficient; int exponent;
        scanf("%f %d", &coefficient, &exponent);
        insert(&head, coefficient, exponent);
    }
    printPolynomial(head);
}