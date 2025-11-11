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

    char msg[100];
    int n = read(client, msg, sizeof(msg) - 1);
    msg[n] = 0;

    double a, b; char op;
    sscanf(msg, "%lf %c %lf", &a, &op, &b);
    
    double result = 0;
    if (op == '+')
        result = a + b;
    else if (op == '-')
        result = a - b;
    else if (op == '*')
        result = a * b;
    else if (op == '/')
        result = (b != 0)? a / b : 0;
    
    char out[100];
    sprintf(out, "%f", result);
    write(client, out, strlen(out));
    
    close(client);
    close(sockfd);
}
