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

    char expr[100];
    printf("Enter expression: ");
    fgets(expr, 100, stdin);
    
    expr[strcspn(expr, "\n")] = 0;
    write(sockfd, expr, strlen(expr));

    char res[100];
    int n = read(sockfd, res, sizeof(res) - 1);
    res[n] = 0;
    
    printf("Result: %s\n", res);
    close(sockfd);
}
