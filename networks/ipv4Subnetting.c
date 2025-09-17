/*
 * ipv4Subnetting.c
 *
 * - Task 7.1: Accept IPv4 in binary, dotted-decimal, or hex and convert to requested format.
 * - Task 7.2: Subnet calculations for classful/classless addressing.
 *
 * Compile: gcc -std=c99 -O2 -Wall -o ipv4Subnetting ipv4Subnetting.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#define LINEBUFSZ 256

/* -- Utility helpers -- */

static void trim(char *s) {
    char *p = s;
    while (*p && isspace((unsigned char)*p)) p++;
    if (p != s) memmove(s, p, strlen(p) + 1);
    /* trim end */
    int len = (int)strlen(s);
    while (len > 0 && isspace((unsigned char)s[len-1])) { s[len-1] = '\0'; len--; }
}

static int is_hex_char(char c) {
    return (c>='0' && c<='9') || (c>='a' && c<='f') || (c>='A' && c<='F');
}

static int all_chars_are(const char *s, const char *allowed) {
    for (; *s; ++s) {
        if (!strchr(allowed, *s)) return 0;
    }
    return 1;
}

/* Convert uint32 IP to dotted decimal string */
static void u32_to_dotted(uint32_t ip, char *buf, int bufsz) {
    snprintf(buf, bufsz, "%u.%u.%u.%u",
             (unsigned)((ip >> 24) & 0xFF),
             (unsigned)((ip >> 16) & 0xFF),
             (unsigned)((ip >>  8) & 0xFF),
             (unsigned)((ip      ) & 0xFF));
}

/* Convert uint32 IP to grouped binary like 11000000.10101000.00000001.00000001 */
static void u32_to_binary(uint32_t ip, char *buf, int bufsz) {
    int pos = 0;
    for (int oct = 3; oct >= 0; --oct) {
        for (int b = 7; b >= 0; --b) {
            if (pos < bufsz-1) buf[pos++] = ((ip >> (oct*8 + b)) & 1) ? '1' : '0';
        }
        if (oct > 0 && pos < bufsz-1) buf[pos++] = '.';
    }
    buf[pos] = '\0';
}

/* Convert uint32 IP to hex string like 0xC0A80001 */
static void u32_to_hex(uint32_t ip, char *buf, int bufsz) {
    snprintf(buf, bufsz, "0x%08X", (unsigned)ip);
}

/* Parse dotted decimal "a.b.c.d" */
static int parse_dotted(const char *s, uint32_t *out) {
    unsigned a,b,c,d;
    char after = 0;
    if (sscanf(s, " %u . %u . %u . %u %c", &a, &b, &c, &d, &after) == 4) {
        if (a<=255 && b<=255 && c<=255 && d<=255) {
            *out = ((uint32_t)a<<24) | ((uint32_t)b<<16) | ((uint32_t)c<<8) | (uint32_t)d;
            return 1;
        }
    }
    return 0;
}

/* Parse binary string either dotted or continuous */
static int parse_binary(const char *s, uint32_t *out) {
    char tmp[64]; int idx = 0;
    for (const char *p = s; *p && idx < (int)sizeof(tmp)-1; ++p) {
        if (*p == '0' || *p == '1') tmp[idx++] = *p;
        else if (*p == '.' || isspace((unsigned char)*p)) continue;
        else return 0;
    }
    tmp[idx] = '\0';
    if (idx != 32) return 0;
    uint32_t val = 0;
    for (int i = 0; i < 32; ++i) {
        val = (val << 1) | (tmp[i] - '0');
    }
    *out = val;
    return 1;
}

/* Parse hex string like 0xC0A80001 or C0A80001 (length up to 8 hex digits). */
static int parse_hex(const char *s, uint32_t *out) {
    const char *p = s;
    while (*p && isspace((unsigned char)*p)) ++p;
    if (p[0]=='0' && (p[1]=='x' || p[1]=='X')) p += 2;
    char tmp[16]; int idx = 0;
    for (; *p && idx < 15; ++p) {
        if (is_hex_char(*p)) tmp[idx++] = *p;
        else if (isspace((unsigned char)*p)) continue;
        else return 0;
    }
    if (idx == 0 || idx > 8) return 0;
    tmp[idx] = '\0';
    /* parse */
    uint32_t val = 0;
    for (int i = 0; tmp[i]; ++i) {
        char c = tmp[i];
        int v = (c>='0' && c<='9') ? (c-'0') : (toupper(c)-'A'+10);
        val = (val << 4) | (uint32_t)v;
    }
    /* if fewer than 8 hex digits, this is left-padded implicitly */
    *out = val;
    return 1;
}

/* Try to detect and parse input string into uint32 IP */
static int parse_address_to_u32(const char *in, uint32_t *out, char *detected_fmt, int fmt_sz) {
    char tmp[LINEBUFSZ];
    strncpy(tmp, in, sizeof(tmp)-1); tmp[sizeof(tmp)-1] = '\0';
    trim(tmp);
    if (strlen(tmp) == 0) return 0;

    /* If there's a dot, check if it's a dotted binary first (only 0/1 and dots),
       else dotted decimal */
    if (strchr(tmp, '.')) {
        int only01dot = 1;
        for (const char *p = tmp; *p; ++p) {
            if (!(*p == '0' || *p == '1' || *p == '.' || isspace((unsigned char)*p))) { only01dot = 0; break; }
        }
        if (only01dot && parse_binary(tmp, out)) {
            strncpy(detected_fmt, "binary", fmt_sz);
            return 1;
        }
        if (parse_dotted(tmp, out)) {
            strncpy(detected_fmt, "dotted-decimal", fmt_sz);
            return 1;
        }
        /* not dotted-decimal; try hex with dots removed? Not supported here */
        return 0;
    } else {
        /* no dots: could be continuous binary (32 bits), hex (0x...), or plain hex digits */
        int all01 = 1; int allhex = 1; int alldigits = 1;
        int len = 0;
        for (const char *p = tmp; *p; ++p) {
            if (!(*p == '0' || *p == '1')) all01 = 0;
            if (!is_hex_char(*p)) allhex = 0;
            if (!isdigit((unsigned char)*p)) alldigits = 0;
            ++len;
        }
        if (all01 && len == 32) {
            if (parse_binary(tmp, out)) { strncpy(detected_fmt, "binary", fmt_sz); return 1; }
        }
        if ((tmp[0]=='0' && (tmp[1]=='x' || tmp[1]=='X')) || allhex) {
            if (parse_hex(tmp, out)) { strncpy(detected_fmt, "hex", fmt_sz); return 1; }
        }
        /* plain decimal 32-bit number? treat as raw uint32 */
        if (alldigits) {
            unsigned long long v = strtoull(tmp, NULL, 10);
            if (v <= 0xFFFFFFFFULL) { *out = (uint32_t)v; strncpy(detected_fmt, "uint32", fmt_sz); return 1; }
        }

        return 0;
    }
}

/* Convert mask prefix to mask value */
static uint32_t prefix_to_mask(int prefix) {
    if (prefix <= 0) return 0u;
    if (prefix >= 32) return 0xFFFFFFFFu;
    uint64_t tmp = 0xFFFFFFFFULL;
    tmp <<= (32 - prefix);
    return (uint32_t)(tmp & 0xFFFFFFFFULL);
}

/* Convert dotted mask string to prefix length, return -1 if invalid */
static int dotted_mask_to_prefix(const char *s) {
    uint32_t mask;
    if (!parse_dotted(s, &mask)) return -1;
    /* count consecutive ones from MSB */
    int cnt = 0;
    int state = 0; /* 0: counting ones, 1: counting zeroes */
    for (int i = 31; i >= 0; --i) {
        int bit = (mask >> i) & 1;
        if (state == 0) {
            if (bit) cnt++;
            else state = 1;
        } else {
            if (bit) return -1; /* non-contiguous ones (invalid mask) */
        }
    }
    return cnt;
}

/* Parse mask input: could be "/24", "24", "255.255.255.0", or "none" */
static int parse_mask_input(const char *s) {
    char tmp[LINEBUFSZ];
    strncpy(tmp, s, sizeof(tmp)-1); tmp[sizeof(tmp)-1] = '\0';
    trim(tmp);
    if (strlen(tmp) == 0) return -2; /* not provided */
    if (strcasecmp(tmp, "none") == 0) return -2;
    if (tmp[0] == '/') {
        int v = atoi(tmp+1);
        if (v >= 0 && v <= 32) return v;
        return -1;
    }
    /* numeric only (24) */
    int allnum = 1;
    for (const char *p = tmp; *p; ++p) if (!isdigit((unsigned char)*p)) { allnum = 0; break; }
    if (allnum) {
        int v = atoi(tmp);
        if (v >= 0 && v <= 32) return v;
        return -1;
    }
    /* dotted decimal mask */
    int pfx = dotted_mask_to_prefix(tmp);
    return pfx; /* -1 if invalid */
}

/* ceil(log2(x)) for integer x>=1 */
static int ceil_log2_uint32(unsigned int x) {
    if (x <= 1) return 0;
    int e = 0;
    unsigned int v = 1;
    while (v < x) { v <<= 1; e++; }
    return e;
}

/* Identify IPv4 class from first octet */
static char ip_class(uint32_t ip) {
    unsigned int first = (unsigned int)((ip >> 24) & 0xFF);
    if (first <= 126) return 'A'; /* 127 is loopback */
    if (first >= 128 && first <= 191) return 'B';
    if (first >= 192 && first <= 223) return 'C';
    if (first >= 224 && first <= 239) return 'D';
    return 'E';
}

/* Print a 32-bit value as dotted+binary+hex for explanation */
static void print_intermediate(uint32_t ip) {
    char buf[64];
    u32_to_dotted(ip, buf, sizeof(buf));
    printf("  dotted: %s\n", buf);
    u32_to_binary(ip, buf, sizeof(buf));
    printf("  binary : %s\n", buf);
    u32_to_hex(ip, buf, sizeof(buf));
    printf("  hex    : %s\n", buf);
}

/* -- Menu handlers -- */

static void handle_conversion() {
    char line[LINEBUFSZ];
    printf("\n[Conversion] Enter IPv4 address (binary, dotted-decimal, or hex):\n> ");
    if (!fgets(line, sizeof(line), stdin)) return;
    trim(line);
    uint32_t ip;
    char detected[32];
    if (!parse_address_to_u32(line, &ip, detected, sizeof(detected))) {
        printf("  Error: could not parse input address. Accepted examples:\n"
               "    - binary dotted: 11000000.10101000.00000001.00000001\n"
               "    - binary continuous: 11000000101010000000000100000001\n"
               "    - dotted-decimal: 192.168.1.1\n"
               "    - hex: 0xC0A80101 or C0A80101\n");
        return;
    }
    printf("  Detected format: %s\n", detected);
    printf("  Integer form (32-bit): %u (0x%08X)\n", (unsigned)ip, (unsigned)ip);
    printf("  Intermediate representations:\n");
    print_intermediate(ip);

    printf("\nChoose output format (binary / dotted / hex):\n> ");
    if (!fgets(line, sizeof(line), stdin)) return;
    trim(line);
    for (char *p=line; *p; ++p) *p = tolower((unsigned char)*p);

    char outbuf[64];
    if (strcmp(line, "binary")==0) {
        u32_to_binary(ip, outbuf, sizeof(outbuf));
        printf("Converted (binary): %s\n", outbuf);
    } else if (strcmp(line, "dotted")==0 || strcmp(line, "dotted-decimal")==0) {
        u32_to_dotted(ip, outbuf, sizeof(outbuf));
        printf("Converted (dotted-decimal): %s\n", outbuf);
    } else if (strcmp(line, "hex")==0) {
        u32_to_hex(ip, outbuf, sizeof(outbuf));
        printf("Converted (hex): %s\n", outbuf);
    } else {
        printf("Unknown output format. Accepted: binary, dotted, hex.\n");
    }
}

static void handle_subnet_calc() {
    char line[LINEBUFSZ];
    printf("\n[Subnet calculator] Enter IPv4 address (binary, dotted-decimal, or hex):\n> ");
    if (!fgets(line, sizeof(line), stdin)) return;
    trim(line);
    uint32_t ip;
    char detected[32];
    if (!parse_address_to_u32(line, &ip, detected, sizeof(detected))) {
        printf("  Error: could not parse input address.\n");
        return;
    }
    printf("  Parsed IP: ");
    print_intermediate(ip);

    /* addressing type */
    printf("\nEnter addressing type: classless OR classful\n> ");
    if (!fgets(line, sizeof(line), stdin)) return;
    trim(line);
    for (char *p=line; *p; ++p) *p = tolower((unsigned char)*p);
    int classless = (strcmp(line, "classless") == 0);

    /* subnet mask (optional) */
    printf("Enter subnet mask (optional). Accepts /24, 24, 255.255.255.0 or 'none' to skip:\n> ");
    if (!fgets(line, sizeof(line), stdin)) return;
    trim(line);
    int mask_prefix = parse_mask_input(line); /* -2 means none, -1 invalid */
    if (mask_prefix == -1) {
        printf("  Invalid mask format. Aborting.\n");
        return;
    }

    int initial_network_bits = -1;
    if (classless) {
        /* classless requires user-specified network ID bits (unless mask provided) */
        printf("Enter number of bits allocated to the network ID (0-32). If you entered mask earlier, you may enter 0 to use that mask:\n> ");
        if (!fgets(line, sizeof(line), stdin)) return;
        trim(line);
        int nb = atoi(line);
        if (nb < 0 || nb > 32) { printf("  Invalid network ID bits.\n"); return; }
        if (nb == 0 && mask_prefix >= 0) initial_network_bits = mask_prefix;
        else initial_network_bits = nb;
        if (initial_network_bits < 0) {
            printf("  No valid network-id bits provided.\n");
            return;
        }
    } else {
        /* classful: default based on class, unless mask provided */
        char cls = ip_class(ip);
        if (mask_prefix >= 0) {
            initial_network_bits = mask_prefix;
            printf("  Using provided mask -> /%d\n", initial_network_bits);
        } else {
            if (cls == 'A') initial_network_bits = 8;
            else if (cls == 'B') initial_network_bits = 16;
            else if (cls == 'C') initial_network_bits = 24;
            else initial_network_bits = 24; /* for D/E not typical */
            printf("  Detected class %c -> default network bits = %d\n", cls, initial_network_bits);
        }
    }

    /* number of subnets */
    printf("Enter number of subnets required (integer >=1):\n> ");
    if (!fgets(line, sizeof(line), stdin)) return;
    trim(line);
    unsigned int num_subnets = (unsigned int)atoi(line);
    if (num_subnets < 1) { printf("  Number of subnets must be >= 1\n"); return; }

    /* Determine how many bits needed to create that many subnets */
    int sbits = ceil_log2_uint32(num_subnets);
    int new_prefix = initial_network_bits + sbits;
    if (new_prefix > 32) {
        printf("  ERROR: need %d bits for subnets but only %d host bits available -> new prefix %d > 32\n",
               sbits, 32 - initial_network_bits, new_prefix);
        return;
    }

    uint32_t initial_mask = prefix_to_mask(initial_network_bits);
    uint32_t new_mask = prefix_to_mask(new_prefix);
    uint64_t subnet_size = 1ULL << (32 - new_prefix); /* total addresses per subnet */
    uint64_t available_subnets = 1ULL << (new_prefix - initial_network_bits);
    if (num_subnets > available_subnets) {
        printf("  ERROR: requested %u subnets but only %llu equal subnets possible (with %d initial bits -> new prefix %d).\n",
               num_subnets, (unsigned long long)available_subnets, initial_network_bits, new_prefix);
        return;
    }

    /* Base network (network ID for the original network) */
    uint32_t base_network = ip & initial_mask;

    printf("\nSubnetting result (initial prefix /%d, new prefix /%d):\n", initial_network_bits, new_prefix);
    printf("  Initial network mask: ");
    print_intermediate(initial_mask);
    printf("  New subnet mask: /%d ", new_prefix); { char tmp[64]; u32_to_dotted(new_mask, tmp, sizeof(tmp)); printf("(%s)\n", tmp); }
    printf("  Subnet size (total addresses per subnet): %llu\n", (unsigned long long)subnet_size);
    if (new_prefix <= 30) printf("  Usable hosts per subnet: %llu (exclude network & broadcast)\n", (unsigned long long)(subnet_size - 2));
    else if (new_prefix == 31) printf("  Usable hosts per subnet: 2 (RFC3021 point-to-point semantics; no broadcast).\n");
    else printf("  Usable hosts per subnet: 1 (single host /32)\n");

    printf("\nListing subnets (0 .. %u-1):\n", num_subnets);

    for (unsigned int i = 0; i < num_subnets; ++i) {
        uint64_t offset = (uint64_t)i * subnet_size;
        uint32_t subnet_network = (uint32_t)((uint64_t)base_network + offset);
        uint32_t broadcast = (uint32_t)((uint64_t)subnet_network + subnet_size - 1);
        char s_net[64], s_brd[64];
        u32_to_dotted(subnet_network, s_net, sizeof(s_net));
        u32_to_dotted(broadcast, s_brd, sizeof(s_brd));

        printf("\nSubnet %u:\n", i+1);
        printf("  Network ID: %s  (/ %d)\n", s_net, new_prefix);
        printf("  Subnet mask: ");
        { char tmp[64]; u32_to_dotted(new_mask, tmp, sizeof(tmp)); printf("%s\n", tmp); }
        printf("  Total addresses: %llu\n", (unsigned long long)subnet_size);
        if (new_prefix <= 30) {
            char first_addr[64], last_addr[64];
            u32_to_dotted(subnet_network + 1, first_addr, sizeof(first_addr));
            u32_to_dotted(broadcast - 1, last_addr, sizeof(last_addr));
            printf("  First usable address: %s\n", first_addr);
            printf("  Last usable address:  %s\n", last_addr);
        } else if (new_prefix == 31) {
            char f[64], l[64];
            u32_to_dotted(subnet_network, f, sizeof(f));
            u32_to_dotted(broadcast, l, sizeof(l));
            printf("  Usable addresses (RFC3021): %s — %s\n", f, l);
        } else { /* /32 */
            char f[64];
            u32_to_dotted(subnet_network, f, sizeof(f));
            printf("  Only address in this subnet: %s\n", f);
        }
        printf("  Broadcast address: %s\n", s_brd);

        /* Host ID range and (if input IP is in this subnet) host ID of the input IP */
        uint32_t host_mask = ~new_mask;
        printf("  Host-ID bits mask (as binary): ");
        { char tmp[128]; u32_to_binary(host_mask, tmp, sizeof(tmp)); printf("%s\n", tmp); }

        /* range of host IDs: 0 .. subnet_size-1 */
        printf("  Host ID range (numeric): 0 - %llu\n", (unsigned long long)(subnet_size - 1));

        if (ip >= subnet_network && ip <= broadcast) {
            uint32_t host_id = ip - subnet_network;
            char tmp[64]; u32_to_binary(host_id, tmp, sizeof(tmp));
            printf("  (Given IP is inside this subnet) Host ID of input IP: %u  (binary: %s)\n", (unsigned)host_id, tmp);
        } else {
            printf("  (Given IP not in this subnet)\n");
        }
    }

    if (!classless) {
        char cls = ip_class(ip);
        printf("\nClassful note: IP belongs to Class %c.\n", cls);
        if (cls == 'A') printf("  Class A default mask: /8\n");
        else if (cls == 'B') printf("  Class B default mask: /16\n");
        else if (cls == 'C') printf("  Class C default mask: /24\n");
        else printf("  (Class D/E: multicast/reserved)\n");
    }

    printf("\n[End of subnet listing]\n");
}

int main(void) {
    char line[LINEBUFSZ];
    printf("IP Tools - conversion and subnet calculator\n");
    printf("Type 1 to run format conversion (7.1), 2 to run subnet calc (7.2), q to quit.\n");
    while (1) {
        printf("\nSelect option (1/2/q):\n> ");
        if (!fgets(line, sizeof(line), stdin)) break;
        trim(line);
        if (strlen(line) == 0) continue;
        if (line[0] == 'q' || line[0] == 'Q') break;
        if (line[0] == '1') handle_conversion();
        else if (line[0] == '2') handle_subnet_calc();
        else printf("Unknown option. Choose 1, 2, or q.\n");
    }
    printf("Exiting.\n");
    return 0;
}
