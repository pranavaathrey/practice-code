// LINUX only

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr);

    connect(sockfd, (struct sockaddr *)&serv, sizeof(serv));

    char sendbuf[100], recvbuf[100];

    while (1) {
        printf("You: ");
        fgets(sendbuf, sizeof(sendbuf), stdin);
        sendbuf[strcspn(sendbuf, "\n")] = 0;

        write(sockfd, sendbuf, strlen(sendbuf));

        if (strcmp(sendbuf, "exit") == 0)
            break;

        int n = read(sockfd, recvbuf, sizeof(recvbuf) - 1);
        if (n <= 0)
            break;

        recvbuf[n] = 0;
        printf("Server: %s\n", recvbuf);

        if (strcmp(recvbuf, "exit") == 0)
            break;
    }
    close(sockfd);
    return 0;
}
