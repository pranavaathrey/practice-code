// compile: gcc ipv4Subnetting.c -o ipv4Subnetting

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

unsigned int ipToInt(int a, int b, int c, int d) {
    return ((a << 24) | (b << 16) | (c << 8) | d);
}

void intToIp(unsigned int ip, int *a, int *b, int *c, int *d) {
    *a = (ip >> 24) & 0xFF;
    *b = (ip >> 16) & 0xFF;
    *c = (ip >> 8) & 0xFF;
    *d = ip & 0xFF;
}

int main() {
    int a, b, c, d;
    char type[10];
    int subnetMaskBits = -1, numSubnets;

    printf("\nEnter IPv4 address (dotted-decimal): ");
    scanf("%d.%d.%d.%d", &a, &b, &c, &d);

    printf("\nAddressing type (classful/classless): ");
    scanf("%s", type);

    unsigned int ip = ipToInt(a, b, c, d);
    char classType = 'X';

    if (strcmp(type, "classful") == 0) {
        if (a >= 1 && a <= 126) { classType = 'A'; subnetMaskBits = 8; }
        else if (a >= 128 && a <= 191) { classType = 'B'; subnetMaskBits = 16; }
        else if (a >= 192 && a <= 223) { classType = 'C'; subnetMaskBits = 24; }
        else { printf("Invalid or unsupported class.\n"); return 0; }

        printf("Class: %c\n", classType);
    } 
    else if (strcmp(type, "classless") == 0) {
        printf("\nEnter number of bits allocated to Network ID: /"); // CIDR
        scanf("%d", &subnetMaskBits);
    } 
    else {
        printf("Invalid addressing type.\n");
        return 0;
    }

    printf("\nEnter number of subnets: ");
    scanf("%d", &numSubnets);

    // get subnet mask
    unsigned int mask = (subnetMaskBits == 32) ? 
            0xFFFFFFFF : ~((1 << (32 - subnetMaskBits)) - 1);

    int maskA, maskB, maskC, maskD;
    intToIp(mask, &maskA, &maskB, &maskC, &maskD);
    printf("Subnet Mask: %d.%d.%d.%d\n", 
            maskA, maskB, maskC, maskD);

    // total addresses per subnet
    unsigned int totalAddresses = (1U << (32 - subnetMaskBits));
    printf("Total addresses per subnet: %u\n", totalAddresses);

    // loop for every subnet
    for (int i = 0; i < numSubnets; i++) {
        unsigned int networkID = (ip & mask) + (i * totalAddresses);
        unsigned int broadcastID = networkID + totalAddresses - 1;
        unsigned int firstHost = networkID + 1;
        unsigned int lastHost = broadcastID - 1;

        int na, nb, nc, nd;
        int fa, fb, fc, fd;
        int la, lb, lc, ld;
        int ba, bb, bc, bd;

        intToIp(networkID, &na, &nb, &nc, &nd);
        intToIp(firstHost, &fa, &fb, &fc, &fd);
        intToIp(lastHost, &la, &lb, &lc, &ld);
        intToIp(broadcastID, &ba, &bb, &bc, &bd);

        printf("\n-------------Subnet %d-------------\n", i + 1);
        printf("%-20s %d.%d.%d.%d\n", "Network ID:", na, nb, nc, nd);
        printf("%-20s %d.%d.%d.%d\n", "First Address:", fa, fb, fc, fd);
        printf("%-20s %d.%d.%d.%d\n", "Last Address:", la, lb, lc, ld);
        printf("%-20s %d.%d.%d.%d\n", "Broadcast Address:", ba, bb, bc, bd);
    }
    return 0;
}