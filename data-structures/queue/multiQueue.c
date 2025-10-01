#include <stdio.h>
#include <stdlib.h>

#define MAXK 100
#define MAXN 10000

int main() {
    int k, n;
    scanf("%d %d", &k, &n);

    int arr[MAXN];                  // shared array
    int front[MAXK], rear[MAXK];    // front & rear for each queue
    int start[MAXK], end[MAXK];     // partition boundaries for each queue
    int size[MAXK];                 // capacity of each queue

    // divide array space equally among queues
    int base = n / k;
    int extra = n % k;
    int idx = 0;

    for (int i = 0; i < k; i++) {
        size[i] = base + (i < extra ? 1 : 0);
        start[i] = idx;
        end[i] = idx + size[i] - 1;
        idx = end[i] + 1;
        front[i] = rear[i] = -1;
    }

    while (1) {
        int op;
        if (scanf("%d", &op) != 1) break;

        if (op == 0) break; // exit
        else if (op == 1) {
            int item, q;
            scanf("%d %d", &item, &q);

            if (q < 0 || q >= k || size[q] == 0) {
                // invalid queue
                continue;
            }
            // check overflow
            if ((front[q] == 0 && rear[q] == size[q] - 1) ||
                (rear[q] + 1) % size[q] == front[q]) {
                printf("Queue %d overflow\n", q);
                continue;
            }
            if (front[q] == -1) 
                front[q] = rear[q] = 0;
            else 
                rear[q] = (rear[q] + 1) % size[q];

            arr[start[q] + rear[q]] = item;
        }
        else if (op == 2) {
            int q;
            scanf("%d", &q);

            if (q < 0 || q >= k || size[q] == 0) 
                continue; // invalid queue
            // underflow
            if (front[q] == -1) {
                printf("Queue %d underflow\n", q);
                continue;
            }
            int item = arr[start[q] + front[q]];

            if (front[q] == rear[q]) 
                front[q] = rear[q] = -1; // queue empty
            else 
                front[q] = (front[q] + 1) % size[q];
            printf("Dequeued element from queue %d is %d\n", q, item);
        }
    }
    return 0;
}
