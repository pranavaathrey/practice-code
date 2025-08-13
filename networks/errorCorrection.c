#include <stdio.h>
#include <stdlib.h>

// function for sender side (encoding)
void sender() {
    int d[4];           // data bits
    int p1, p2, p4;     // parity bits

    printf("Enter 4 data bits (space separated): ");
    scanf("%d %d %d %d", &d[0], &d[1], &d[2], &d[3]);

    // calculate parity bits using Hamming(7,4)
    p1 = d[0] ^ d[1] ^ d[3];
    p2 = d[0] ^ d[2] ^ d[3];
    p4 = d[1] ^ d[2] ^ d[3];

    // final 7-bit code (positions: p1 p2 d1 p4 d2 d3 d4)
    printf("Encoded 7-bit data: %d %d %d %d %d %d %d\n",
           p1, p2, d[0], p4, d[1], d[2], d[3]);
}

// function for receiver side (decoding & error correction)
void receiver() {
    int r[7];
    int p1, p2, p4, error_pos;

    printf("Enter the received 7 bits (space separated): ");
    for (int i = 0; i < 7; i++)
        scanf("%d", &r[i]);

    // recalculate parity checks
    p1 = r[0] ^ r[2] ^ r[4] ^ r[6];
    p2 = r[1] ^ r[2] ^ r[5] ^ r[6];
    p4 = r[3] ^ r[4] ^ r[5] ^ r[6];

    // covert error position from binary to decimal
    error_pos = p4 * 4 + p2 * 2 + p1 * 1;

    if (error_pos == 0) 
        printf("No error detected.\n");
    else {
        printf("Error detected at bit position: %d\n", error_pos);
        // correct the error (bit positions are 1-indexed)
        r[error_pos - 1] ^= 1;
        printf("Corrected data: ");
        for (int i = 0; i < 7; i++)
            printf("%d ", r[i]);
        printf("\n");
    }
}

int main() {
    int choice;
    printf("Error Correction Mechanism using Hamming Codes \nOptions: \n");
    printf("1. Sender\n");
    printf("2. Receiver\n");
    printf(">> Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
        sender();
    else if (choice == 2)
        receiver();
    else
        printf("Invalid choice.\n");

    return 0;
}