#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// dotted-decimal
void printDecimal(uint32_t ip) {
    unsigned char bytes[4];
    bytes[0] = (ip >> 24) & 0xFF;
    bytes[1] = (ip >> 16) & 0xFF;
    bytes[2] = (ip >> 8) & 0xFF;
    bytes[3] = ip & 0xFF;
    printf("%u.%u.%u.%u\n", 
        bytes[0], bytes[1], bytes[2], bytes[3]);
}

// binary
void printBinary(uint32_t ip) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (ip >> i) & 1);
        if (i % 8 == 0 && i != 0) printf(".");
    }
    printf("\n");
}

// hexadecimal
void printHex(uint32_t ip) {
    printf("0x%08X\n", ip);
}

int main() {
    char input[100], format[20], output[20];
    uint32_t ip = 0;

    printf("Enter input format (binary/decimal/hex): ");
    scanf("%s", format);

    printf("Enter IPv4 address: ");
    scanf("%s", input);

    if (strcmp(format, "decimal") == 0) {
        unsigned int b1, b2, b3, b4;
        sscanf(input, "%u.%u.%u.%u", &b1, &b2, &b3, &b4);
        ip = (b1 << 24) | (b2 << 16) | (b3 << 8) | b4; // 32-bit IP
    } 
    else if (strcmp(format, "binary") == 0) {
        // remove dots and parse binary
        char binStr[40] = "";
        for (int i = 0; i < strlen(input); i++) 
            if (input[i] != '.') strncat(binStr, &input[i], 1);
        ip = (uint32_t) strtoul(binStr, NULL, 2);
    } 
    else if (strcmp(format, "hex") == 0) 
        ip = (uint32_t) strtoul(input, NULL, 16);
    else {
        printf("Invalid input format.\n");
        return 1;
    }

    printf("Enter output format (binary/decimal/hex): ");
    scanf("%s", output);

    if (strcmp(output, "decimal") == 0) 
        printDecimal(ip);
    else if (strcmp(output, "binary") == 0) 
        printBinary(ip);
    else if (strcmp(output, "hex") == 0) 
        printHex(ip);
    else {
        printf("Invalid output format.\n");
        return 1;
    }
    return 0;
}
