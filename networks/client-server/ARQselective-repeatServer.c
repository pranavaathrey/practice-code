/* 
   Selective Repeat ARQ sender (Windows, Winsock2)
   Compile:
     gcc ARQselective-repeatServer.c -o ARQselective-repeatServer.exe -lws2_32
   Usage:
     ARQselective-repeatServer.exe <receiver_ip> <receiver_port> <window_size> <timeout_ms> <loss_percent>
   Example:
     ARQselective-repeatServer.exe 127.0.0.1 5000 4 1000 10
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
#define SEQ_SPACE 8   /* sequence number space: 0..SEQ_SPACE-1 */
#define MAX_PENDING 128

typedef struct {
    int seq;
    int len;
    char data[MAX_PAYLOAD];
    unsigned short checksum;
} Packet;

typedef struct {
    int ack_seq; /* sequence being ACKed */
} AckPacket;

int window_size = 4;
int timeout_ms = 1000;
int loss_percent = 0; /* simulate loss */

SOCKET sockfd;
struct sockaddr_in servaddr;
CRITICAL_SECTION lock;

Packet sendbuf[SEQ_SPACE];        /* buffer for sent-but-not-acked */
int sent_flag[SEQ_SPACE];         /* 0-not used/acked, 1-sent and waiting */
DWORD send_time[SEQ_SPACE];       /* last send timestamp (GetTickCount) */
int payload_len[SEQ_SPACE];
int base = 0;                     /* lowest unacked sequence */
int nextseq = 0;                  /* next seq to use (mod SEQ_SPACE) */
int eof_reached = 0;

int running = 1;

/* simple checksum */
unsigned short checksum_buf(const char *buf, int len) {
    unsigned int sum = 0;
    for (int i = 0; i < len; ++i) sum += (unsigned char)buf[i];
    while (sum >> 16) sum = (sum & 0xFFFF) + (sum >> 16);
    return (unsigned short)~sum;
}

int between(int a, int b, int c) {
    /* return (a <= b < c) on circular seq space */
    /* Using modulo arithmetic for circular windows */
    if (a <= c) return (a <= b && b < c);
    return (a <= b || b < c);
}

int rand_percent() {
    return rand() % 100;
}

/* receiver thread: receives ACKs */
DWORD WINAPI ack_receiver_thread(LPVOID param) {
    (void)param;
    char buf[64];
    struct sockaddr_in from;
    int fromlen = sizeof(from);
    while (running) {
        int n = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&from, &fromlen);
        if (n == SOCKET_ERROR) {
            int err = WSAGetLastError();
            if (err == WSAEWOULDBLOCK) { Sleep(50); continue; }
            /* other errors -> break */
            break;
        }
        if (n >= sizeof(int)) {
            int ack_seq;
            memcpy(&ack_seq, buf, sizeof(int));
            ack_seq = ntohl(ack_seq);

            EnterCriticalSection(&lock);
            /* Mark acked if within window and pending */
            if (sent_flag[ack_seq]) {
                sent_flag[ack_seq] = 0; /* acknowledged */
                /* advance base */
                while (!sent_flag[base] && base != nextseq) 
                    base = (base + 1) % SEQ_SPACE;
            }
            LeaveCriticalSection(&lock);
            printf("[Sender] Received ACK %d\n", ack_seq);
        }
    }
    return 0;
}

/* send a packet (simulate loss) */
void do_send_packet(int seq) {
    Packet *p = &sendbuf[seq];
    char out[sizeof(Packet)];
    memcpy(out, p, sizeof(Packet));
    if (rand_percent() < loss_percent) {
        /* simulate loss: pretend we sent but don't actually send */
        printf("[Sender] Simulating LOSS of packet %d\n", seq);
        return;
    }
    int sent = sendto(
        sockfd, out, sizeof(Packet), 0, 
        (struct sockaddr*)&servaddr, sizeof(servaddr)
    );
    if (sent == SOCKET_ERROR) 
        printf("[Sender] sendto error: %d\n", WSAGetLastError());
    else 
        printf("[Sender] Sent packet seq=%d len=%d\n", seq, p->len);
}

/* main sender */
int main(int argc, char **argv) {
    if (argc < 6) {
        printf("Usage: %s <receiver_ip> <receiver_port> <window_size> <timeout_ms> <loss_percent>\n", argv[0]);
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);
    window_size = atoi(argv[3]);
    timeout_ms = atoi(argv[4]);
    loss_percent = atoi(argv[5]);
    if (window_size <= 0 || window_size >= SEQ_SPACE) {
        printf("window_size must be in 1..%d\n", SEQ_SPACE - 1);
        return 1;
    }

    srand((unsigned)time(NULL));

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup failed\n"); return 1;
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == INVALID_SOCKET) { printf("socket failed\n"); return 1; }

    /* make non-blocking so recvfrom won't block */
    u_long mode = 1;
    ioctlsocket(sockfd, FIONBIO, &mode);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &servaddr.sin_addr);
    servaddr.sin_port = htons(port);

    InitializeCriticalSection(&lock);

    /* start ACK receiver thread */
    HANDLE th = CreateThread(NULL, 0, ack_receiver_thread, NULL, 0, NULL);

    printf("Enter lines to send (Ctrl+Z then Enter to finish):\n");

    char line[MAX_PAYLOAD];
    while (fgets(line, sizeof(line), stdin) != NULL) {
        int linelen = (int)strlen(line);
        if (linelen > 0 && line[linelen-1] == '\n') { 
            line[linelen-1] = '\0'; linelen--; 
        }

        /* wait until window has space */
        while (1) {
            EnterCriticalSection(&lock);
            /* count unacked in window */
            int unacked = 0;
            for (int i = 0; i < SEQ_SPACE; ++i) if (sent_flag[i]) unacked++;
            int avail = window_size - unacked;
            if (avail > 0) {
                /* send packet with seq = nextseq */
                int seq = nextseq;
                Packet *p = &sendbuf[seq];
                p->seq = seq;
                p->len = linelen;
                memcpy(p->data, line, linelen);
                p->data[linelen] = '\0';
                p->checksum = checksum_buf(p->data, p->len);

                sent_flag[seq] = 1;
                payload_len[seq] = p->len;
                send_time[seq] = GetTickCount();
                do_send_packet(seq);

                /* advance nextseq mod space, but not beyond SEQ_SPACE range */
                nextseq = (nextseq + 1) % SEQ_SPACE;
                LeaveCriticalSection(&lock);
                break;
            }
            LeaveCriticalSection(&lock);
            Sleep(50);
        }

        /* background: check for timeouts and retransmit */
        /* We'll handle in below loop too */
    }

    /* after EOF: wait for all outstanding acks */
    eof_reached = 1;
    printf("[Sender] EOF reached. Waiting for outstanding packets to be ACKed.\n");

    /* main loop: check timers and finish when all sent_flag are 0 */
    while (1) {
        EnterCriticalSection(&lock);
        int outstanding = 0;
        DWORD now = GetTickCount();
        for (int i = 0; i < SEQ_SPACE; ++i) {
            if (sent_flag[i]) {
                outstanding++;
                if ((int)(now - send_time[i]) >= timeout_ms) {
                    /* timeout: retransmit */
                    send_time[i] = now;
                    printf("[Sender] Timeout: retransmitting seq=%d\n", i);
                    do_send_packet(i);
                }
            }
        }
        LeaveCriticalSection(&lock);

        if (eof_reached && outstanding == 0) break;
        Sleep(50);
    }

    /* clean up */
    running = 0;
    Sleep(100); /* give ack thread a chance to exit */
    closesocket(sockfd);
    DeleteCriticalSection(&lock);
    WSACleanup();
    printf("[Sender] All packets ACKed. Exiting.\n");
    return 0;
}
