#include <stdio.h>

int main() {
    char operator;
    double num1, num2, result;

    printf("Choose an operation (+, -, *, /): ");
    scanf(" %c", &operator);  

    printf("Enter the first number: ");
    scanf("%lf", &num1);
    printf("Enter the second number: ");
    scanf("%lf", &num2);

    switch (operator) {
        case '+':
            result = num1 + num2;
            printf("Sum: %.2lf + %.2lf = %.2lf\n", num1, num2, result);
            break;

        case '-':
            result = num1 - num2;
            printf("Difference: %.2lf - %.2lf = %.2lf\n", num1, num2, result);
            break;

        case '*':
            result = num1 * num2;
            printf("Product: %.2lf * %.2lf = %.2lf\n", num1, num2, result);
            break;

        case '/':
            if (num2 != 0) {  // Check for division by zero
                result = num1 / num2;
                printf("Quotient: %.2lf / %.2lf = %.2lf\n", num1, num2, result);
            } else {
                printf("You can't divide by zero.\n");
            }
            break;

        default:
            printf("Invalid operator. Please use one of (+, -, *, /).\n");
    }

    return 0;
}
