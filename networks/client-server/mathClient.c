#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
// on mingw, compile with the -lws2_32 flag

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    // initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }

    // create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("Socket creation error. Code: %d\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // convert IPv4 address from text to binary
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address/Address not supported\n");
        closesocket(sock);
        WSACleanup();
        return -1;
    }

    // connect to server
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection Failed. Code: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return -1;
    }

    printf("Connected to server. Enter 'quit' to exit. \n\n");
    printf("Enter expressions in the following format: \n"); 
    printf("<num1> <op> <num2> (e.g., 5 + 3) \n\n");

    while (1) {
        char input[BUFFER_SIZE];
        printf("> ");
        fgets(input, BUFFER_SIZE, stdin);

        // exit on "quit"
        if (strncmp(input, "quit", 4) == 0) 
            break;

        send(sock, input, strlen(input), 0);

        memset(buffer, 0, BUFFER_SIZE);
        int valread = recv(sock, buffer, BUFFER_SIZE, 0);
        if (valread > 0) 
            printf("%s\n", buffer);
    }
    closesocket(sock);
    WSACleanup();
    return 0;
}
