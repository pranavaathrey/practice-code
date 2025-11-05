// LINUX only

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv = {AF_INET, htons(8080)};
    inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr);

    connect(sockfd, (struct sockaddr*)&serv, sizeof(serv));
    write(sockfd, "Hello Server", 12);

    char msg[100];
    read(sockfd, msg, sizeof(msg));
    printf("Server: %s\n", msg);

    close(sockfd);
}
