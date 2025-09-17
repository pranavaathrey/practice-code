// stop-and-Wait ARQ sender (Windows, UDP)
// compile: gcc ARQstop-waitSender.c -o ARQstop-waitSender -lws2_32

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "127.0.0.1"   // change as needed
#define SERVER_PORT 5005
#define MAX_PAYLOAD 512
#define MAX_FRAME_SIZE (1 + 1 + 2 + MAX_PAYLOAD + 1) // type + seq + len + data + checksum
#define TIMEOUT_SEC 2
#define TIMEOUT_USEC 0

// frame types
#define TYPE_DATA 0
#define TYPE_ACK  1

uint8_t checksum(const uint8_t *buf, int len) {
    uint32_t s = 0;
    for (int i = 0; i < len; ++i) s += buf[i];
    return (uint8_t)(s & 0xFF);
}

int main(void) {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in si_other;
    int slen = sizeof(si_other);
    uint8_t frame[MAX_FRAME_SIZE];
    uint8_t rbuf[64];

    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET) {
        printf("socket() failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    ZeroMemory(&si_other, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &si_other.sin_addr);

    printf("Enter the message to be sent (end with Ctrl+Z & Enter):\n");

    // read all stdin into buffer (simple)
    char *buffer = NULL;
    size_t bufcap = 0, buflen = 0;
    const size_t chunk = 1024;
    while (!feof(stdin)) {
        if (buflen + chunk + 1 > bufcap) {
            bufcap = bufcap + chunk + 1;
            buffer = (char*)realloc(buffer, bufcap);
        }
        size_t r = fread(buffer + buflen, 1, chunk, stdin);
        buflen += r;
        if (r < chunk) break;
    }

    if (buflen == 0) {
        printf("Nothing to send. Exiting.\n");
        closesocket(sock);
        WSACleanup();
        return 0;
    }

    uint8_t seq = 0;
    size_t offset = 0;

    printf("Starting Stop-and-Wait send to %s:%d\n", SERVER_IP, SERVER_PORT);

    while (offset < buflen) {
        size_t to_send = buflen - offset;
        if (to_send > MAX_PAYLOAD) to_send = MAX_PAYLOAD;

        // build frame
        frame[0] = TYPE_DATA;
        frame[1] = seq;
        uint16_t len_net = htons((uint16_t)to_send);
        memcpy(&frame[2], &len_net, 2);
        memcpy(&frame[4], buffer + offset, to_send);
        uint8_t c = checksum(frame, 1 + 1 + 2 + (int)to_send);
        frame[4 + to_send] = c;
        int frame_len = (int)(1 + 1 + 2 + to_send + 1);

        int attempts = 0;
        const int max_attempts = 10;
        int acked = 0;
        while (!acked && attempts < max_attempts) {
            ++attempts;
            if (sendto(sock, (char*)frame, frame_len, 0, (struct sockaddr*)&si_other, slen) == SOCKET_ERROR) {
                printf("sendto() failed: %d\n", WSAGetLastError());
                free(buffer);
                closesocket(sock);
                WSACleanup();
                return 1;
            }
            printf("[SEND] Sent seq=%d, len=%zu (attempt %d)\n", seq, to_send, attempts);

            // wait for ACK with timeout
            fd_set readfds;
            FD_ZERO(&readfds);
            FD_SET(sock, &readfds);
            struct timeval tv;
            tv.tv_sec = TIMEOUT_SEC;
            tv.tv_usec = TIMEOUT_USEC;

            int rv = select(0, &readfds, NULL, NULL, &tv);
            if (rv == SOCKET_ERROR) {
                printf("select() failed: %d\n", WSAGetLastError());
                free(buffer);
                closesocket(sock);
                WSACleanup();
                return 1;
            } else if (rv == 0) {
                // timeout
                printf("[TIMEOUT] No ACK, will retransmit.\n");
                continue;
            } else {
                // data available
                int rlen = recvfrom(sock, (char*)rbuf, sizeof(rbuf), 0, NULL, NULL);
                if (rlen == SOCKET_ERROR) {
                    printf("recvfrom() failed: %d\n", WSAGetLastError());
                    free(buffer);
                    closesocket(sock);
                    WSACleanup();
                    return 1;
                }
                if (rlen >= 3 && (uint8_t)rbuf[0] == TYPE_ACK) {
                    uint8_t ack_seq = (uint8_t)rbuf[1];
                    uint8_t recv_ck = (uint8_t)rbuf[2];
                    uint8_t calc_ck = checksum((uint8_t*)rbuf, 2);
                    if (recv_ck != calc_ck) {
                        printf("[ACK] Received corrupted ACK (checksum mismatch). Ignoring.\n");
                        continue;
                    }
                    if (ack_seq == seq) {
                        printf("[ACK] Received ACK for seq=%d\n", ack_seq);
                        acked = 1;
                        seq = 1 - seq; // flip sequence
                        offset += to_send; // consume data
                        break;
                    } else {
                        printf("[ACK] Received ACK for seq=%d but expected %d. Ignoring.\n", ack_seq, seq);
                        // continue waiting or retransmit on next loop
                    }
                } else {
                    printf("[RECV] Ignored non-ACK or short packet\n");
                }
            }
        } // end attempts
        if (!acked) {
            printf("Failed to send frame after %d attempts. Giving up.\n", max_attempts);
            break;
        }
    }

    printf("Send complete or stopped.\n");
    free(buffer);
    closesocket(sock);
    WSACleanup();
    return 0;
}
