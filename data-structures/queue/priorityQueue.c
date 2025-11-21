#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int size;
    int capacity;
} PriorityQueue;
// uses max heaps; larger value, greater priority
PriorityQueue *createPQ(int capacity) {
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    pq->arr = malloc(sizeof(int) * capacity);
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

static void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void maxHeapify(PriorityQueue *h, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < h->size && h->arr[left] > h->arr[largest])
        largest = left;

    if (right < h->size && h->arr[right] > h->arr[largest])
        largest = right;

    if (largest != i) {
        swap(&h->arr[i], &h->arr[largest]);
        maxHeapify(h, largest);
    }
}
void buildMaxHeap(PriorityQueue *h) {
    for (int i = h->size / 2 - 1; i >= 0; i--)
        maxHeapify(h, i);
}

void insertMaxHeap(PriorityQueue *h, int x) {
    if (h->size >= h->capacity) {
        printf("Heap full\n");
        return;
    }
    int i = h->size++;
    h->arr[i] = x;

    while (i != 0 && h->arr[(i - 1) / 2] < h->arr[i]) {
        swap(&h->arr[i], &h->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
int extractMax(PriorityQueue *h) {
    if (h->size <= 0)
        return -1;

    int root = h->arr[0];
    h->arr[0] = h->arr[--h->size];
    maxHeapify(h, 0);
    return root;
}

int getMax(PriorityQueue *pq) {
    return pq->size == 0 ? -1 : pq->arr[0];
}
void freePQ(PriorityQueue *pq) {
    free(pq->arr);
    free(pq);
}

int main() {
    PriorityQueue *pq = createPQ(10);

    insertMaxHeap(pq, 40);
    insertMaxHeap(pq, 15);
    insertMaxHeap(pq, 30);
    insertMaxHeap(pq, 50);

    printf("Max: %d\n", getMax(pq));
    printf("Extract: %d\n", extractMax(pq));
    printf("Extract: %d\n", extractMax(pq));

    freePQ(pq);
    return 0;
}
