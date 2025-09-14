// Go-Back-N receiver (UDP) for Windows
// Compile: gcc ARQgo-back-Nclient.c -o ARQgo-back-Nclient.exe -lws2_32   (MinGW)

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT 8888
#define MAX_PKT_SIZE 1024
#define DROP_PROBABILITY 0.2  // 20% chance to drop incoming packet (simulate loss)

typedef struct {
    uint32_t seq;
    uint16_t len;
    char data[1]; // variable-length payload
} __attribute__((packed)) pkt_hdr;

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in serverAddr, clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    char buffer[MAX_PKT_SIZE];
    srand((unsigned)time(NULL));

    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        printf("socket() failed\n");
        WSACleanup();
        return 1;
    }

    ZeroMemory(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(SERVER_PORT);

    if (bind(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("bind() failed\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    printf("GBN Receiver listening on port %d\n", SERVER_PORT);
    uint32_t expected_seq = 0;
    while (1) {
        int recvLen = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (recvLen == SOCKET_ERROR) {
            printf("recvfrom error %d\n", WSAGetLastError());
            continue;
        }

        // simulate random drop
        double r = (double)rand() / RAND_MAX;
        if (r < DROP_PROBABILITY) {
            printf("[SIM DROP] Dropped a packet from client (simulated).\n");
            // optionally we could not send ACK - that's the drop
            continue;
        }

        if (recvLen < (int)sizeof(uint32_t) + (int)sizeof(uint16_t)) {
            printf("Received too small packet\n");
            continue;
        }

        // parse header
        uint32_t seq;
        uint16_t len;
        memcpy(&seq, buffer, sizeof(uint32_t));
        memcpy(&len, buffer + sizeof(uint32_t), sizeof(uint16_t));
        seq = ntohl(seq);
        len = ntohs(len);

        printf("Received packet seq=%u len=%u\n", seq, len);

        if (seq == expected_seq) {
            // deliver (for demo, print payload)
            if (len > 0 && (int)len <= recvLen - ((int)sizeof(uint32_t)+ (int)sizeof(uint16_t))) {
                printf(" DATA: %.*s\n", len, buffer + sizeof(uint32_t) + sizeof(uint16_t));
            } else {
                printf(" (no data or truncated)\n");
            }
            expected_seq++;
        } else {
            printf(" Out of order (expected %u). Discarding.\n", expected_seq);
        }

        // send ACK for last in-order packet (expected_seq - 1). If expected_seq==0, ack -1 not allowed; send ack 0xFFFFFFFF to signal none.
        uint32_t ack_seq = (expected_seq == 0) ? 0xFFFFFFFFu : (expected_seq - 1);
        uint32_t ack_net = htonl(ack_seq);
        int sent = sendto(sock, (char*)&ack_net, sizeof(ack_net), 0, (struct sockaddr*)&clientAddr, clientAddrLen);
        if (sent == SOCKET_ERROR) {
            printf("sendto ACK failed %d\n", WSAGetLastError());
        } else {
            if (ack_seq == 0xFFFFFFFFu)
                printf(" Sent ACK = NONE (no packets in order yet)\n");
            else
                printf(" Sent ACK = %u\n", ack_seq);
        }
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
