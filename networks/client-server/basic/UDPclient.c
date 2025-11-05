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
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    sendto(sock, "Hello", 5, 0, (struct sockaddr*)&addr, sizeof(addr));

    char buf[100];
    int n = recvfrom(sock, buf, sizeof(buf) - 1, 0, NULL, NULL);
    buf[n] = '\0';
    printf("Got: %s\n", buf);

    close(sock);
    return 0;
}
