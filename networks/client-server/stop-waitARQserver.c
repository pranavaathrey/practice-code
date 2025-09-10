// stop-and-Wait ARQ receiver (Windows, UDP)

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 5005
#define MAX_PAYLOAD 512
#define MAX_FRAME_SIZE (1 + 1 + 2 + MAX_PAYLOAD + 1) // type + seq + len + data + checksum

// frame types
#define TYPE_DATA 0
#define TYPE_ACK  1

// set packet loss probability for simulation (0.0 - 1.0)
#define LOSS_PROBABILITY 0.1

uint8_t checksum(const uint8_t *buf, int len) {
    uint32_t s = 0;
    for (int i = 0; i < len; ++i) s += buf[i];
    return (uint8_t)(s & 0xFF);
}

int maybe_drop_packet() {
    double r = (double)rand() / RAND_MAX;
    return r < LOSS_PROBABILITY;
}

int main(void) {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in si_me, si_other;
    int slen = sizeof(si_other);
    uint8_t buf[MAX_FRAME_SIZE];

    srand((unsigned)time(NULL));

    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET) {
        printf("socket() failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    ZeroMemory(&si_me, sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sock, (struct sockaddr*)&si_me, sizeof(si_me)) == SOCKET_ERROR) {
        printf("bind() failed: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    printf("Receiver listening on port %d\n", PORT);

    uint8_t expected_seq = 0;
    while (1) {
        int recvlen = recvfrom(sock, (char*)buf, MAX_FRAME_SIZE, 0, (struct sockaddr*)&si_other, &slen);
        if (recvlen == SOCKET_ERROR) {
            printf("recvfrom() failed: %d\n", WSAGetLastError());
            break;
        }
        if (recvlen < 1 + 1 + 2 + 1) continue; // too small

        // simulate packet loss
        if (maybe_drop_packet()) {
            printf("[SIM] Dropped a packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
            continue;
        }

        uint8_t type = buf[0];
        uint8_t seq  = buf[1];
        uint16_t len_net;
        memcpy(&len_net, &buf[2], 2);
        uint16_t dlen = ntohs(len_net);
        if (dlen > MAX_PAYLOAD) dlen = MAX_PAYLOAD;

        uint8_t received_checksum = buf[1 + 1 + 2 + dlen]; // after payload
        uint8_t calc = checksum(buf, 1 + 1 + 2 + dlen); // type + seq + len + payload

        if (type != TYPE_DATA) {
            // ignore non-data
            continue;
        }

        if (calc != received_checksum) {
            printf("Checksum mismatch (got 0x%02x, calc 0x%02x). Sending ACK for last good seq %d\n", received_checksum, calc, (uint8_t)(1 - expected_seq));
            // send ACK for last correctly received seq (i.e., 1 - expected_seq)
            uint8_t ackbuf[1 + 1 + 1]; // type, seq, checksum
            ackbuf[0] = TYPE_ACK;
            ackbuf[1] = (uint8_t)(1 - expected_seq);
            ackbuf[2] = checksum(ackbuf, 2);
            sendto(sock, (char*)ackbuf, 3, 0, (struct sockaddr*)&si_other, slen);
            continue;
        }

        if (seq == expected_seq) {
            // accept and deliver
            if (dlen > 0) {
                // print payload to stdout (safe)
                fwrite(&buf[4], 1, dlen, stdout);
                fflush(stdout);
            }
            // send ACK
            uint8_t ackbuf[1 + 1 + 1];
            ackbuf[0] = TYPE_ACK;
            ackbuf[1] = seq;
            ackbuf[2] = checksum(ackbuf, 2);
            if (sendto(sock, (char*)ackbuf, 3, 0, (struct sockaddr*)&si_other, slen) == SOCKET_ERROR) {
                printf("sendto() failed: %d\n", WSAGetLastError());
                break;
            } else {
                printf("\n[RECV] Accepted seq=%d, len=%d, sent ACK\n", seq, dlen);
            }
            expected_seq = 1 - expected_seq; // flip
        } else {
            // duplicate, re-send ACK for last good seq (which is 1 - expected_seq)
            uint8_t ackbuf[1 + 1 + 1];
            ackbuf[0] = TYPE_ACK;
            ackbuf[1] = (uint8_t)(1 - expected_seq);
            ackbuf[2] = checksum(ackbuf, 2);
            sendto(sock, (char*)ackbuf, 3, 0, (struct sockaddr*)&si_other, slen);
            printf("[RECV] Duplicate seq=%d (expected %d). Re-sent ACK for %d\n", seq, expected_seq, 1 - expected_seq);
        }
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
