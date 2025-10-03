#include <stdio.h>
#include <stdlib.h>

typedef struct Term {
    int coefficient;
    int exponent;
    struct Term* next;
} Term;

Term* createTerm(int co, int exp) {
    Term* newTerm = (Term*)malloc(sizeof(Term));
    newTerm->coefficient = co;
    newTerm->exponent = exp;
    newTerm->next = NULL;
    return newTerm;
}

void insert(Term** head, int co, int exp) {
    Term* newTerm = createTerm(co, exp);
    if(*head == NULL || exp > (*head)->exponent) {
        newTerm->next = *head;
        *head = newTerm;
        return;
    }
    Term* temp = *head;
    while(temp->next != NULL && temp->next->exponent > exp)
        temp = temp->next;
    newTerm->next = temp->next;
    temp->next = newTerm;
}

void printPolynomial(Term* head) {
    Term* temp = head;
    int first = 1;
    while(temp != NULL) {
        if(!first) printf(" + ");
        printf("(%dx^%d)", temp->coefficient, temp->exponent);
        first = 0;
        temp = temp->next;
    }
    printf("\n");
}

int areEqual(Term* p1, Term* p2) {
    while(p1 != NULL && p2 != NULL) {
        if(p1->coefficient != p2->coefficient 
            || p1->exponent != p2->exponent)
            return 0;
        p1 = p1->next;
        p2 = p2->next;
    }
    if(p1 == NULL && p2 == NULL) return 1;
    return 0;
}

int main() {
    int n, m, i;
    scanf("%d", &n);
    Term* poly1 = NULL;
    for(i=0; i<n; i++) {
        int co, exp;
        scanf("%d %d", &co, &exp);
        insert(&poly1, co, exp);
    }
    scanf("%d", &m);
    Term* poly2 = NULL;
    for(i=0; i<m; i++) {
        int co, exp;
        scanf("%d %d", &co, &exp);
        insert(&poly2, co, exp);
    }
    
    printf("Polynomial 1: ");
    printPolynomial(poly1);
    printf("Polynomial 2: ");
    printPolynomial(poly2);
    
    if(areEqual(poly1, poly2))
    printf("Polynomials are Equal.\n");
    else
    printf("Polynomials are Not Equal.\n");
    
    return 0;
}
