/* 
   Selective Repeat ARQ receiver (Windows, Winsock2)
   Compile:
     gcc ARQselective-repeatReceiver.c -o ARQselective-repeatReceiver.exe -lws2_32
   Usage:
     ARQselective-repeatReceiver.exe <listen_port> <loss_percent>
   Example:
     ARQselective-repeatReceiver.exe 5000 10
*/

#define _WIN32_WINNT 0x0600
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#pragma comment(lib, "ws2_32.lib")

#define MAX_PAYLOAD 512
#define SEQ_SPACE 8
#define WINDOW_SIZE 4

typedef struct {
    int seq;
    int len;
    char data[MAX_PAYLOAD];
    unsigned short checksum;
} Packet;

typedef struct {
    int ack_seq;
} AckPacket;

int loss_percent = 0;
SOCKET sockfd;
struct sockaddr_in myaddr;
struct sockaddr_in peeraddr;
int peer_known = 0;

int expected_base = 0; /* receiver window base */
char recvbuf[SEQ_SPACE][MAX_PAYLOAD];
int recvlen[SEQ_SPACE];
int received_flag[SEQ_SPACE];

unsigned short checksum_buf(const char *buf, int len) {
    unsigned int sum = 0;
    for (int i = 0; i < len; ++i) sum += (unsigned char)buf[i];
    while (sum >> 16) sum = (sum & 0xFFFF) + (sum >> 16);
    return (unsigned short)~sum;
}

int rand_percent() { return rand() % 100; }

int between(int a, int b, int c) {
    if (a <= c) return (a <= b && b < c);
    return (a <= b || b < c);
}

void send_ack(int seq) {
    int ack = htonl(seq);
    if (rand_percent() < loss_percent) {
        printf("[Receiver] Simulating LOSS of ACK %d\n", seq);
        return;
    }
    sendto(sockfd, (char*)&ack, sizeof(ack), 0, (struct sockaddr*)&peeraddr, sizeof(peeraddr));
    printf("[Receiver] Sent ACK %d\n", seq);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: %s <listen_port> <loss_percent>\n", argv[0]);
        return 1;
    }
    int port = atoi(argv[1]);
    loss_percent = atoi(argv[2]);

    srand((unsigned)time(NULL));

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup failed\n"); return 1;
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == INVALID_SOCKET) { printf("socket failed\n"); return 1; }

    ZeroMemory(&myaddr, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myaddr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr*)&myaddr, sizeof(myaddr)) == SOCKET_ERROR) {
        printf("bind failed: %d\n", WSAGetLastError());
        return 1;
    }

    ZeroMemory(received_flag, sizeof(received_flag));
    ZeroMemory(recvlen, sizeof(recvlen));

    printf("[Receiver] Listening on port %d\n", port);

    while (1) {
        Packet pkt;
        struct sockaddr_in from;
        int fromlen = sizeof(from);
        int n = recvfrom(sockfd, (char*)&pkt, sizeof(pkt), 0, (struct sockaddr*)&from, &fromlen);
        if (n == SOCKET_ERROR) {
            int err = WSAGetLastError();
            if (err == WSAEWOULDBLOCK || err == WSAEINTR) { Sleep(20); continue; }
            printf("[Receiver] recvfrom error: %d\n", err);
            break;
        }
        /* remember sender address to reply with ACKs */
        if (!peer_known) { peeraddr = from; peer_known = 1; }

        /* simulate data-loss */
        if (rand_percent() < loss_percent) {
            printf("[Receiver] Simulating LOSS of data packet (ignored)\n");
            continue;
        }

        /* validate checksum */
        unsigned short chksum = checksum_buf(pkt.data, pkt.len);
        if (chksum != pkt.checksum) {
            printf("[Receiver] Dropped packet %d due to checksum mismatch\n", pkt.seq);
            continue;
        }

        printf("[Receiver] Got packet seq=%d len=%d\n", pkt.seq, pkt.len);

        /* if packet seq is within receive window, buffer and ack */
        int recv_window_end = (expected_base + WINDOW_SIZE) % SEQ_SPACE;
        int within;
        if (expected_base < recv_window_end) within = (pkt.seq >= expected_base && pkt.seq < recv_window_end);
        else within = (pkt.seq >= expected_base || pkt.seq < recv_window_end);

        if (within) {
            if (!received_flag[pkt.seq]) {
                /* buffer it */
                received_flag[pkt.seq] = 1;
                recvlen[pkt.seq] = pkt.len;
                memcpy(recvbuf[pkt.seq], pkt.data, pkt.len);
                recvbuf[pkt.seq][pkt.len] = '\0';
                printf("[Receiver] Buffered seq=%d\n", pkt.seq);
            } else {
                printf("[Receiver] Duplicate packet %d (already buffered)\n", pkt.seq);
            }
            /* send ACK */
            send_ack(pkt.seq);

            /* deliver in-order as much as possible */
            while (received_flag[expected_base]) {
                printf("[Receiver] Delivered (in-order) seq=%d : \"%s\"\n", expected_base, recvbuf[expected_base]);
                received_flag[expected_base] = 0; /* consumed */
                expected_base = (expected_base + 1) % SEQ_SPACE;
            }
        } else {
            /* outside window: send ACK for last received if appropriate (or send ACK to indicate) */
            printf("[Receiver] Packet %d outside window (base=%d). Sending ACK if previously received.\n", pkt.seq, expected_base);
            /* send ACK anyway to indicate maybe previously received */
            send_ack(pkt.seq);
        }
    }

    closesocket(sockfd);
    WSACleanup();
    return 0;
}
