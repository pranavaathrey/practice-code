#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
// on mingw, compile with the -lws2_32 flag

#define PORT 8080
#define BUFFER_SIZE 1024

// function to perform calculation
double calculate(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b != 0) ? a / b : 0;
        default: return 0;
    }
}

int main() {
    WSADATA wsaData;
    SOCKET server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }

    // create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == INVALID_SOCKET) {
        printf("Socket creation failed. Error code: %d\n", 
                                        WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // setup server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // bind socket
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) 
                        == SOCKET_ERROR) {
        printf("Bind failed. Error code: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // listen for connections
    if (listen(server_fd, 3) == SOCKET_ERROR) {
        printf("Listen failed. Error code: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    printf("Server listening on port %d...\n", PORT);

    // accept a client
    new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
    if (new_socket == INVALID_SOCKET) {
        printf("Accept failed. Error code: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }
    printf("Client connected!\n");

    // communication loop
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);

        int valread = recv(new_socket, buffer, BUFFER_SIZE, 0);
        if (valread <= 0) {
            printf("Client disconnected.\n");
            break;
        }

        double num1, num2;
        char op;
        sscanf(buffer, "%lf %c %lf", &num1, &op, &num2);

        double result = calculate(num1, num2, op);

        char result_str[BUFFER_SIZE];
        snprintf(result_str, sizeof(result_str), 
                            "  Result: %.2lf\n ", result);

        send(new_socket, result_str, strlen(result_str), 0);
    }
    closesocket(new_socket);
    closesocket(server_fd);
    WSACleanup();

    return 0;
}
