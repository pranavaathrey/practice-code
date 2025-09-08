#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")
// on mingw, compile with the -lws2_32 flag

#define PORT 8080
#define BUFFER_SIZE 1024

// thread function to receive messages from client
DWORD WINAPI recvThread(LPVOID lpParam) {
    SOCKET clientSocket = *(SOCKET*)lpParam;
    char buffer[BUFFER_SIZE];

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int valread = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (valread <= 0) {
            printf("Client disconnected.\n");
            break;
        }
        printf("\nClient: %s", buffer);
    }
    closesocket(clientSocket);
    return 0;
}

int main() {
    WSADATA wsa;
    SOCKET server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];

    // initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    // create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation failed. Error Code: %d\n", WSAGetLastError());
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
        printf("Bind failed. Error Code: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // listen for connections
    if (listen(server_fd, 3) == SOCKET_ERROR) {
        printf("Listen failed. Error Code: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }
    printf("Server listening on port %d...\n", PORT);

    // accept connection
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) 
                    == INVALID_SOCKET) {
        printf("Accept failed. Error Code: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }
    printf("Client connected!\n");

    // create a thread for receiving messages
    HANDLE hThread = CreateThread(NULL, 0, recvThread, &new_socket, 0, NULL);
    if (hThread == NULL) {
        printf("Failed to create thread. Error Code: %d\n", GetLastError());
        closesocket(new_socket);
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // main thread: send messages to client
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        printf("> ");
        fgets(buffer, BUFFER_SIZE, stdin);
        send(new_socket, buffer, strlen(buffer), 0);
    }
    // cleanup
    closesocket(new_socket);
    closesocket(server_fd);
    WSACleanup();
    return 0;
}
