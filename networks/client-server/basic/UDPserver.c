// LINUX only

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(sock, (struct sockaddr*)&addr, sizeof(addr));

    char buf[100];
    struct sockaddr_in src;
    socklen_t len = sizeof(src);
    recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&src, &len);
    printf("Got: %s\n", buf);

    sendto(sock, "ey ma man", 9, 0, (struct sockaddr*)&src, len);
    close(sock);
    return 0;
}
