#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isDecimal(const char *str) {
    for (int i = 0; str[i]; i++) {
        if (!isdigit((unsigned char)str[i])) return 0;
    }
    return 1;
}

void decimalToHex(const char *decimal, char *hex_out) {
    int value = atoi(decimal);
    sprintf(hex_out, "%02X", value); 
}

// look up table for keywords
typedef struct {
    const char *word;
    const char *code;
} Mapping;

Mapping table[] = {
    //------------> OPCODES <------------//

    // memory management
    {"copy", "40"},         // 0100 0000
    {"copy_i", "C0"},       // 1100 0000
    
    {"ram_load", "3F"},     // 0011 1111
    {"ram_save", "3E"},     // 0011 1110

    {"push", "3B"},         // 0011 1011
    {"pop", "3C"},          // 0011 1100

    // arithmetic
    {"add", "00"},          // 0000 0000
    {"add_ii", "C0"},       // 1100 0000
    {"add_ir", "80"},       // 1000 0000
    {"add_ri", "40"},       // 0100 0000
    
    {"sub", "01"},          // 0000 0001
    {"sub_ii", "C1"},       // 1100 0001
    {"sub_ir", "81"},       // 1000 0001
    {"sub_ri", "41"},       // 0100 0001

    {"mult", "0E"},         // 0000 1110
    {"mult_ii", "CE"},      // 1100 1110
    {"mult_ir", "8E"},      // 1000 1110
    {"mult_ri", "4E"},      // 0100 1110

    {"mult_hi_byte", "0F"}, // 0000 1111

    {"div", "10"},          // 0001 0000
    {"div_ii", "D0"},       // 1101 0000
    {"div_ir", "90"},       // 1001 0000
    {"div_ri", "50"},       // 0101 0000

    {"mod", "11"},          // 0001 0001
    {"mod_ii", "D1"},       // 1101 0001
    {"mod_ir", "91"},       // 1001 0001
    {"mod_ri", "51"},       // 0101 0001

    // logical
    {"AND", "02"},          // 0000 0010
    {"AND_ii", "C2"},       // 1100 0010
    {"AND_ir", "82"},       // 1000 0010
    {"AND_ri", "42"},       // 0100 0010
    
    {"OR", "03"},           // 0000 0011
    {"OR_ii", "C3"},        // 1100 0011
    {"OR_ir", "83"},        // 1000 0011
    {"OR_ri", "43"},        // 0100 0011

    {"NOT", "04"},          // 0000 0100
    {"NOT_ii", "C4"},       // 1100 0100
    {"NOT_ir", "84"},       // 1000 0100
    {"NOT_ri", "44"},       // 0100 0100

    {"XOR", "05"},          // 0000 0101
    {"XOR_ii", "C5"},       // 1100 0101
    {"XOR_ir", "85"},       // 1000 0101
    {"XOR_ri", "45"},       // 0100 0101

    // conditional


    // other
    {"end", "3A"},          // 0011 1010
    

    //------------> FILLER <------------//

    {"from", "00"},         // 0000 0000
    {"to", "00"},           // 0000 0000
    {"upon", "00"},         // 0000 0000

    {"loc", "00"},          // 0000 0000
    {"location", "00"},     // 0000 0000

    {"function", "00"},     // 0000 0000    
    {"stack", "00"},        // 0000 0000


    //------------> ADDRESSES <------------//

    {"ram_address", "00"},  // 0000 0000
    {"counter", "06"},      // 0000 0110

    {"input", "07"},        // 0000 0111
    {"output", "07"},       // 0000 0111

    {"reg_0", "00"},        // 0000 0000 -- UNUSED
    {"reg_1", "01"},        // 0000 0001
    {"reg_2", "02"},        // 0000 0010
    {"reg_3", "03"},        // 0000 0011
    {"reg_4", "04"},        // 0000 0100
    {"reg_5", "05"},        // 0000 0101

    // end of the mapping
    {NULL, NULL}
};

const char* lookup(const char *word) {
    for (int i = 0; table[i].word != NULL; i++) {
        if (strcmp(word, table[i].word) == 0) 
            return table[i].code;
    }
    return NULL;
}

int main() {
    FILE *in = fopen("instructions.txt", "r");
    FILE *out = fopen("binary.bin", "wb");

    if (!in || !out) {
        perror("File error");
        return 1;
    }

    char line[512];
    while (fgets(line, sizeof(line), in)) {
        if (strncmp(line, "//", 2) == 0 || strncmp(line, "#", 1) == 0)
            continue;

        char *token = strtok(line, " \t\r\n");
        while (token) {
            const char *mapped = lookup(token);
            char hexCode[16];

            if (mapped) 
                strcpy(hexCode, mapped);
            else if (isDecimal(token)) 
                decimalToHex(token, hexCode);
            else {
                // if unknown word
                printf("Unknown instruction: %s\n", token);
                strcpy(hexCode, "??");
            }

            unsigned int byte;
            if (sscanf(hexCode, "%x", &byte) == 1) {
                unsigned char b = (unsigned char)byte;
                fwrite(&b, 1, 1, out);
            }
            token = strtok(NULL, " \t\r\n");
        }
    }
    fclose(in);
    fclose(out);

    printf("Conversion complete. Output saved to binary.bin\n");
    return 0;
}
