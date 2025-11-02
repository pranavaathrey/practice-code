#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// singly linked node
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

// returns the sum of two polynomials
Term* findSum(Term* poly1, Term* poly2) {
    Term* sum = NULL;
    while(poly1 != NULL && poly2 != NULL) {
        if(poly1->exponent == poly2->exponent) {
            float sumCo = poly1->coefficient + poly2->coefficient;
            insert(&sum, sumCo, poly1->exponent);

            poly1 = poly1->next;
            poly2 = poly2->next;
        } else if(poly1->exponent > poly2->exponent) {
            insert(&sum, poly1->coefficient, poly1->exponent);

            poly1 = poly1->next;
        } else if(poly1->exponent < poly2->exponent) {
            insert(&sum, poly2->coefficient, poly2->exponent);

            poly2 = poly2->next;
        }
    }
    while(poly1 != NULL) {
        insert(&sum, poly1->coefficient, poly1->exponent);
        poly1 = poly1->next;
    }
    while(poly2 != NULL) {
        insert(&sum, poly2->coefficient, poly2->exponent);
        poly2 = poly2->next;
    }  
    return sum;
}

// returns the product of two polynomials
Term* findProduct(Term* poly1, Term* poly2) {
    Term* product = NULL;
    // check for empty polynomials
    if(poly1 == NULL) return poly2;
    if(poly2 == NULL) return poly1;
    // get product
    while(poly1 != NULL) {
        Term* temp = poly2;
        while(temp != NULL) {
            float coeff = poly1->coefficient * temp->coefficient;
            int exp = poly1->exponent + temp->exponent;

            insert(&product, coeff, exp);
            temp = temp->next;
        }
        poly1 = poly1->next;
    }
    // simplify product
    Term* temp = product, *deletedTerm = NULL;
    while(temp->next != NULL) {
        if(temp->exponent == temp->next->exponent) {
            temp->coefficient += temp->next->coefficient;
            deletedTerm = temp->next;
            temp->next = temp->next->next;
            free(deletedTerm); continue;
        }  
        temp = temp->next;
    }
    return product;
}

// displays currently stored polynomial
void printPolynomial(Term* head) {
    if(head == NULL) {
        printf("Empty polynomial!\n");
        return;
    }
    Term* temp = head; int printed = 0;
    while(temp != NULL) {
        if(temp->coefficient == 0)
            goto next;
        // sign handling
        printed = 1;
        if(temp == head) {
            if(temp->coefficient < 0)
                printf("-");
        } else {
            if(temp->coefficient < 0)
                printf(" - ");
            else if(temp->coefficient > 0)
                printf(" + ");
        }
        // coefficient handling
        float coeff = fabsf(temp->coefficient);
        if (!(coeff == 1 && temp->exponent != 0)) {
            float rounded = round(coeff * 10) / 10.0; 
            if (fabsf(rounded - (int)rounded) < 1e-3f) 
                printf("%d", (int)rounded);
            else
                printf("%.1f", rounded);
        }
        // exponent handling
        if(temp->exponent > 1)
            printf("x^%d", temp->exponent);
        else if(temp->exponent < 0)
            printf("x^(%d)", temp->exponent);
        else if(temp->exponent == 1)
            printf("x");
        // next term
        next: temp = temp->next;
    }
    if(!printed) printf("0");
    printf("\n");
}

int main() {
    printf("\nEnter the number of terms in the polynomial 1: ");
    int n, i = 1; scanf("%d", &n);

    Term* polynomial1 = NULL;
    while(n--) {
        printf("\tEnter the coefficient and exponent for term %d: ", i++);
        float coefficient; int exponent;
        scanf("%f %d", &coefficient, &exponent);
        insert(&polynomial1, coefficient, exponent);
    }
    printf("\nEnter the number of terms in the polynomial 2: ");
    i = 1; scanf("%d", &n);

    Term* polynomial2 = NULL;
    while(n--) {
        printf("\tEnter the coefficient and exponent for term %d: ", i++);
        float coefficient; int exponent;
        scanf("%f %d", &coefficient, &exponent);
        insert(&polynomial2, coefficient, exponent);
    }
    printf("\nPolynomial 1: ");
    printPolynomial(polynomial1);
    printf("Polynomial 2: ");
    printPolynomial(polynomial2);

    char choice[99];
    printf("\nWould you like to add or multiply these polynomials? \n> ");
    scanf("%s", &choice);

    if(!stricmp(choice, "multiply")) {
        Term* product = NULL;
        product = findProduct(polynomial1, polynomial2);

        printf("Product of the two polynomials: \n");
        printPolynomial(product);
    } else if(!stricmp(choice, "add")) {
        Term* sum = NULL;
        sum = findSum(polynomial1, polynomial2);
        
        printf("Sum of the two polynomials: \n");
        printPolynomial(sum);
    } else 
        printf("Invalid choice\n");
    return 0;
}