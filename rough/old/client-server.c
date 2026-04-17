
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

void server() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8080);
    serv.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&serv, sizeof(serv));
    listen(sockfd, 1);

    int client = accept(sockfd, NULL, NULL);

    char recvbuf[100];
    int n = read(client, recvbuf, sizeof(recvbuf) - 1);
    recvbuf[n] = 0;

    float a, b, res; char op;
    sscanf(recvbuf, "%f %c %f", &a, &op, &b);

    switch(op) {
        case '+': res = a + b; break;
        case '-': res = a - b; break;
        case '*': res = a * b; break;
        case '/': res = (b != 0)? a / b : 0; break;
    }
    char sendbuf[100];
    sprintf(sendbuf, "%f", res);
    write(client, sendbuf, strlen(sendbuf));
    
    close(client);
    close(sockfd);
}

void client() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr);

    connect(sockfd, (struct sockaddr *)&serv, sizeof(serv));

    char sendbuf[100];
    printf("Enter expression: ");
    fgets(sendbuf, 100, stdin);

    sendbuf[strcspn(sendbuf, "\n")] = 0;
    write(sockfd, sendbuf, strlen(sendbuf));

    char recvbuf[100];
    int n = read(sockfd, recvbuf, sizeof(recvbuf) - 1);
    recvbuf[n] = 0;
    
    printf("%s", recvbuf);
    close(sockfd);
}