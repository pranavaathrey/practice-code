#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BITS 128

// calculate parity bit (VRC)
char calculateParity(char *data, char type) {
    int count = 0;
    for (int i = 0; data[i]; i++) {
        if (data[i] == '1') count++;
    }
    if (type == 'e') 
        return (count % 2 == 0) ? '0' : '1';  // Even parity
    else 
        return (count % 2 == 0) ? '1' : '0';  // Odd parity
}

// Vertical Redundancy Check (VRC)
void vrc(char *mode, char *parityType, char *data) {
    printf("\nOriginal Input: %s\n", data);
    
    printf("Used Parity Generator: %s\n", 
        (parityType[0] == 'e') ? "even" : "odd");
    
    char bit = calculateParity(data, parityType[0]);
    printf("Generated Redundant bit: %c\n", bit);

    if (strcmp(mode, "send") == 0) {
        printf("Bits to be transmitted: %s%c\n", data, bit);
    } else {
        int len = strlen(data);
        char receivedParity = data[len - 1];
        data[len - 1] = '\0';
        char expected = calculateParity(data, parityType[0]);

        if (expected == receivedParity)
            printf("No Error Detected.\n");
        else
            printf("Error Detected in Received Data.\n");
    }
}

// Longitudinal Redundancy Check (LRC)
void lrc(char *mode, char *parityType, char data[][MAX_BITS], int rows, int bitsPerRow) {
    printf("\nUsed Parity Generator: %s\n", 
        (parityType[0] == 'e') ? "even" : "odd");

    char lrcBits[MAX_BITS] = {0};

    for (int i = 0; i < bitsPerRow; i++) {
        int count = 0;
        for (int j = 0; j < rows; j++) {
            if (data[j][i] == '1') count++;
        }
        lrcBits[i] = ((parityType[0] == 'e') ^ (count % 2 != 0)) ? '0' : '1';
    }

    if (strcmp(mode, "send") == 0) {
        printf("Original Data:\n");
        for (int i = 0; i < rows; i++) 
            printf("%s\n", data[i]);
        
        printf("Generated LRC: %s\n", lrcBits);
    } else {
        int error = 0;
        for (int i = 0; i < bitsPerRow; i++) {
            int count = 0;
            for (int j = 0; j < rows; j++) {
                if (data[j][i] == '1') count++;
            }
            if (((parityType[0] == 'e') && (count % 2 != 0)) 
             || ((parityType[0] == 'o') && (count % 2 == 0))) {
                error = 1;
                break;
            }
        }
        if (error)
            printf("Error Detected in Received Data.\n");
        else
            printf("No Error Detected.\n");
    }
}

// Cyclic Redundancy Check (CRC)
void crc(char *mode, char *data, char *divisor) {
    int dataLen = strlen(data);
    int divLen = strlen(divisor);
    char temp[MAX_BITS], remainder[MAX_BITS];

    strcpy(temp, data);
    strcat(temp, "0000000000000000");  // enough padding
    strncpy(remainder, temp, dataLen + divLen - 1);

    remainder[dataLen + divLen - 1] = '\0';

    for (int i = 0; i <= strlen(remainder) - divLen; ) {
        for (int j = 0; j < divLen; j++) {
            remainder[i + j] = (remainder[i + j] == divisor[j]) ? '0' : '1';
        }
        while (remainder[i] == '0' && i < strlen(remainder)) i++;
    }

    char crcBits[MAX_BITS];
    strncpy(crcBits, remainder + strlen(remainder) - divLen + 1, divLen - 1);
    crcBits[divLen - 1] = '\0';

    if (strcmp(mode, "send") == 0) {
        printf("\nCRC bits: %s\n", crcBits);
        printf("Transmitted Frame: %s%s\n", data, crcBits);
    } else {
        int allZero = 1;
        for (int i = 0; i < strlen(remainder); i++) {
            if (remainder[i] != '0') {
                allZero = 0;
                break;
            }
        }
        if (allZero)
            printf("No Error Detected.\n");
        else
            printf("Error Detected in Received Data.\n");
    }
}

void checksum(char *mode, char data[][MAX_BITS], int rows) {
    int sum = 0;
    for (int i = 0; i < rows; i++) 
        sum += (int) strtol(data[i], NULL, 2);

    while (sum >> 8) // wrap around
        sum = (sum & 0xFF) + (sum >> 8);

    int checkSum = ~sum & 0xFF;

    if (strcmp(mode, "send") == 0) 
        printf("\nCalculated Checksum: %08b\n", checkSum);
    else {
        sum += checkSum;
        while (sum >> 8) 
            sum = (sum & 0xFF) + (sum >> 8);
        
        if ((sum & 0xFF) == 0xFF)
            printf("No Error Detected.\n");
        else
            printf("Error Detected in Received Data.\n");
    }
}

int main() {
    int choice;
    char mode[10], parityType[10], data[MAX_BITS];

    printf("\n>> Choose any one of the following:\n1. VRC\n2. LRC\n3. CRC\n4. Checksum\n");
    printf("User Input: ");
    scanf("%d", &choice);

    printf("\n>> Do you want to send or receive the data?\nUser Input: ");
    scanf("%s", mode);

    if (choice == 1 || choice == 2) {
        printf("\n>> Which parity generator do you want to use? odd/even\nUser Input: ");
        scanf("%s", parityType);
    }

    if (choice == 1) {
        printf("\n>> Enter the original data:\nUser Input: ");
        scanf("%s", data);

        vrc(mode, parityType, data);
    } 
    else if (choice == 2) {
        int rows;
        printf("\n>> Enter number of data words: ");
        scanf("%d", &rows);

        char lrcData[rows][MAX_BITS];
        int bits = 0;
        for (int i = 0; i < rows; i++) {
            printf("Word %d: ", i + 1);
            scanf("%s", lrcData[i]);
            if (i == 0) bits = strlen(lrcData[i]);
        }
        lrc(mode, parityType, lrcData, rows, bits);
    } 
    else if (choice == 3) {
        char divisor[MAX_BITS];
        printf("\n>> Enter the data: ");
        scanf("%s", data);

        printf("\n>> Enter the divisor (generator polynomial): ");
        scanf("%s", divisor);

        crc(mode, data, divisor);
    } 
    else if (choice == 4) {
        int rows;
        printf("\n>> Enter number of 8-bit words: ");
        scanf("%d", &rows);

        char checksumData[rows][MAX_BITS];
        for (int i = 0; i < rows; i++) {
            printf("\nWord %d (8 bits): ", i + 1);
            scanf("%s", checksumData[i]);
        }
        checksum(mode, checksumData, rows);
    } 
    else 
        printf("\nInvalid choice.\n");
    
    return 0;
}