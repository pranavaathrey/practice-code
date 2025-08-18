#include <stdio.h>

int add(int a, int b) {
    return a + b;
}
int subtract(int a, int b) {
    return a - b;
}

int doOperation(int a, int b, int (*operation)(int, int)) {
    return operation(a, b);
}

int main() {
    int x, y;
    printf("Enter two integers: ");
    scanf("%d %d", &x, &y);

    printf("Sum: %d\n", doOperation(x, y, add));
    printf("Difference: %d\n", doOperation(x, y, subtract));

    return 0;
}   