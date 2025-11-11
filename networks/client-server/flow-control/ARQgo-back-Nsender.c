// Go-Back-N sender (UDP) for Windows
// to compile: gcc ARQgo-back-Nsender.c -o ARQgo-back-Nsender.exe -lws2_32  (MinGW)

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT 8888
#define SERVER_IP "127.0.0.1"
#define MAX_PKT_SIZE 1024
#define PAYLOAD_SIZE 900
#define TIMEOUT_MS 500
#define WINDOW_SIZE 4

typedef struct {
    uint32_t seq;
    uint16_t len;
    char data[PAYLOAD_SIZE];
} __attribute__((packed)) packet_t;

uint64_t now_ms() {
    return GetTickCount64();
}

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in serverAddr;
    int serverAddrLen = sizeof(serverAddr);

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
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    char input[8192];
    printf("Enter message to send (or blank to use sample text):\n> ");
    fflush(stdout);
    if (!fgets(input, sizeof(input), stdin)) input[0]=0;
    if (input[0] == '\n' || input[0]==0) {
        strncpy(input, "The quick brown fox jumps over the lazy dog. This is a test message for Go-Back-N ARQ implementation over UDP. Repeat to make it longer. ", sizeof(input)-1);
        strcat(input, input); strcat(input, input); // make longer
    }

    size_t input_len = strlen(input);
    // split into packets
    int total_pkts = (input_len + PAYLOAD_SIZE - 1) / PAYLOAD_SIZE;
    packet_t **pkts = malloc(sizeof(packet_t*) * total_pkts);
    for (int i = 0; i < total_pkts; ++i) {
        size_t off = i * PAYLOAD_SIZE;
        size_t chunk = (input_len - off) < PAYLOAD_SIZE ? (input_len - off) : PAYLOAD_SIZE;
        pkts[i] = malloc(sizeof(packet_t));
        memset(pkts[i], 0, sizeof(packet_t));
        pkts[i]->seq = htonl((uint32_t)i);
        pkts[i]->len = htons((uint16_t)chunk);
        memcpy(pkts[i]->data, input + off, chunk);
    }

    printf("Prepared %d packets. Server %s:%d Window=%d Timeout=%dms\n",
           total_pkts, SERVER_IP, SERVER_PORT, WINDOW_SIZE, TIMEOUT_MS);

    int base = 0;
    int nextseq = 0;
    uint64_t timer_start = 0;
    int timer_running = 0;

    // set socket non-blocking for recv
    u_long mode = 1;
    ioctlsocket(sock, FIONBIO, &mode);

    while (base < total_pkts) {
        // send packets within window
        while (nextseq < total_pkts && nextseq < base + WINDOW_SIZE) {
            // send packet[nextseq]
            // reconstruct packet on the wire: seq(4) + len(2) + data
            uint32_t seq_net; uint16_t len_net;
            memcpy(&seq_net, &(pkts[nextseq]->seq), sizeof(uint32_t));
            memcpy(&len_net, &(pkts[nextseq]->len), sizeof(uint16_t));
            char sendbuf[MAX_PKT_SIZE];
            int sendlen = 0;
            memcpy(sendbuf + sendlen, &seq_net, sizeof(uint32_t)); sendlen += sizeof(uint32_t);
            memcpy(sendbuf + sendlen, &len_net, sizeof(uint16_t)); sendlen += sizeof(uint16_t);
            uint16_t plen = ntohs(len_net);
            memcpy(sendbuf + sendlen, pkts[nextseq]->data, plen); sendlen += plen;

            int sent = sendto(sock, sendbuf, sendlen, 0, (struct sockaddr*)&serverAddr, serverAddrLen);
            if (sent == SOCKET_ERROR) {
                printf("sendto error %d\n", WSAGetLastError());
            } else {
                printf("Sent pkt seq=%d len=%d\n", nextseq, plen);
            }

            if (!timer_running) {
                timer_running = 1;
                timer_start = now_ms();
            }
            nextseq++;
        }

        // check for ACKs
        char ackbuf[8];
        struct sockaddr_in from; int fromlen = sizeof(from);
        int r = recvfrom(sock, ackbuf, sizeof(ackbuf), 0, (struct sockaddr*)&from, &fromlen);
        if (r > 0) {
            if (r >= (int)sizeof(uint32_t)) {
                uint32_t ack_net;
                memcpy(&ack_net, ackbuf, sizeof(uint32_t));
                uint32_t ack = ntohl(ack_net);
                if (ack == 0xFFFFFFFFu) {
                    printf("Received ACK = NONE\n");
                } else {
                    printf("Received ACK = %u\n", ack);
                    if ((int)ack >= base) {
                        base = (int)ack + 1;
                        if (base == nextseq) 
                            timer_running = 0;
                        else {
                            // restart timer for new base
                            timer_start = now_ms(); 
                            timer_running = 1;
                        }
                    } else 
                        printf(" (duplicate/old ACK)\n");
                }
            }
        } else {
            int err = WSAGetLastError();
            if (err != WSAEWOULDBLOCK && err != WSAEINTR) {
                // real error
                //printf("recvfrom error %d\n", err);
            }
        }

        // check timeout
        if (timer_running) {
            uint64_t elapsed = now_ms() - timer_start;
            if (elapsed >= TIMEOUT_MS) {
                // timeout: retransmit all packets in window [base, nextseq-1]
                printf("Timeout! Retransmitting window from %d to %d\n", base, nextseq - 1);
                for (int i = base; i < nextseq; ++i) {
                    uint32_t seq_net; uint16_t len_net;
                    memcpy(&seq_net, &(pkts[i]->seq), sizeof(uint32_t));
                    memcpy(&len_net, &(pkts[i]->len), sizeof(uint16_t));
                    char sendbuf[MAX_PKT_SIZE];
                    int sendlen = 0;
                    memcpy(sendbuf + sendlen, &seq_net, sizeof(uint32_t)); sendlen += sizeof(uint32_t);
                    memcpy(sendbuf + sendlen, &len_net, sizeof(uint16_t)); sendlen += sizeof(uint16_t);
                    uint16_t plen = ntohs(len_net);
                    memcpy(sendbuf + sendlen, pkts[i]->data, plen); sendlen += plen;
                    int sent = sendto(sock, sendbuf, sendlen, 0, (struct sockaddr*)&serverAddr, serverAddrLen);
                    if (sent == SOCKET_ERROR) 
                        printf("sendto error %d\n", WSAGetLastError());
                    else
                        printf(" Retransmitted pkt seq=%d\n", i);
                }
                timer_start = now_ms(); // restart timer
            }
        }
        Sleep(10); // small sleep to avoid busy loop
    }
    printf("All packets sent and acknowledged. Cleaning up.\n");

    // free memory
    for (int i = 0; i < total_pkts; ++i) free(pkts[i]);
    free(pkts);

    closesocket(sock);
    WSACleanup();
    return 0;
}
