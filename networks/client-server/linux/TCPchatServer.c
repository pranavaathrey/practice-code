// LINUX only

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8080);
    serv.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));
    listen(sockfd, 1);

    int client = accept(sockfd, NULL, NULL);

    char recvbuf[100], sendbuf[100];

    while (1) {
        int n = read(client, recvbuf, sizeof(recvbuf) - 1);
        if (n <= 0)
            break;

        recvbuf[n] = 0;
        printf("Client: %s\n", recvbuf);

        if (strcmp(recvbuf, "exit") == 0)
            break;

        printf("You: ");
        fgets(sendbuf, sizeof(sendbuf), stdin);
        sendbuf[strcspn(sendbuf, "\n")] = 0;

        write(client, sendbuf, strlen(sendbuf));

        if (strcmp(sendbuf, "exit") == 0)
            break;
    }
    close(client);
    close(sockfd);
    return 0;
}
