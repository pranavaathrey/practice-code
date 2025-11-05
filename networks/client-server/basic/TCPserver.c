// LINUX only

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv = {AF_INET, htons(8080), INADDR_ANY};
    
    bind(sockfd, (struct sockaddr*)&serv, sizeof(serv));
    listen(sockfd, 1);

    int client = accept(sockfd, NULL, NULL);
    char msg[100];
    read(client, msg, sizeof(msg));
    printf("Client: %s\n", msg);
    write(client, "Hello Client", 12);

    close(client);
    close(sockfd);
}
