// LINUX only

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    char buf[100];
    struct sockaddr_in src;
    socklen_t len = sizeof(src);
    
    int n = recvfrom(sock, buf, sizeof(buf) - 1, 0, (struct sockaddr *)&src, &len);
    buf[n] = 0;
    double a, b;
    char op;
    sscanf(buf, "%lf %c %lf", &a, &op, &b);

    double r = 0;
    if (op == '+')
        r = a + b;
    else if (op == '-')
        r = a - b;
    else if (op == '*')
        r = a * b;
    else if (op == '/')
        r = b != 0 ? a / b : 0;
    
    char out[100];
    sprintf(out, "%f", r);
    sendto(sock, out, strlen(out), 0, (struct sockaddr *)&src, len);
    
    close(sock);
    return 0;
}
