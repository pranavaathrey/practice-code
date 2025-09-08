#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
// on mingw, compile with the -lws2_32 flag

#define PORT 8080
#define BUFFER_SIZE 1024

// thread function to receive messages from server
DWORD WINAPI recvThread(LPVOID lpParam) {
    SOCKET sock = *(SOCKET*)lpParam;
    char buffer[BUFFER_SIZE];

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int valread = recv(sock, buffer, BUFFER_SIZE, 0);
        if (valread <= 0) {
            printf("Server disconnected.\n");
            break;
        }
        printf("\nServer: %s", buffer);
    }
    closesocket(sock);
    return 0;
}

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];

    // initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    // create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation failed. Error Code: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // convert IPv4 address
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address.\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // connect to server
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) 
                    == SOCKET_ERROR) {
        printf("Connection failed. Error Code: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    printf("Connected to server. Start chatting!\n");

    // create a thread to receive messages
    HANDLE hThread = CreateThread(NULL, 0, recvThread, &sock, 0, NULL);
    if (hThread == NULL) {
        printf("Failed to create thread. Error Code: %d\n", GetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // main thread: send messages
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        printf("> ");
        fgets(buffer, BUFFER_SIZE, stdin);
        send(sock, buffer, strlen(buffer), 0);
    }
    // cleanup
    closesocket(sock);
    WSACleanup();
    return 0;
}
