#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} PriorityQueue;
// uses min heaps
PriorityQueue *createPQ(int capacity) {
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    pq->data = malloc(sizeof(int) * capacity);
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

static void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

static void heapifyDown(PriorityQueue *pq, int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < pq->size && pq->data[left] > pq->data[largest])
        largest = left;

    if (right < pq->size && pq->data[right] > pq->data[largest])
        largest = right;

    if (largest != i) {
        swap(&pq->data[i], &pq->data[largest]);
        heapifyDown(pq, largest);
    }
}
static void heapifyUp(PriorityQueue *pq, int i) {
    int parent = (i - 1) / 2;

    while (i > 0 && pq->data[i] > pq->data[parent]) {
        swap(&pq->data[i], &pq->data[parent]);
        i = parent;
        parent = (i - 1) / 2;
    }
}

void insert(PriorityQueue *pq, int value) {
    if (pq->size == pq->capacity) {
        pq->capacity *= 2;
        pq->data = realloc(pq->data, pq->capacity * sizeof(int));
    }
    pq->data[pq->size] = value;
    heapifyUp(pq, pq->size);
    pq->size++;
}

int getMax(PriorityQueue *pq) {
    return pq->size == 0 ? -1 : pq->data[0];
}
int extractMax(PriorityQueue *pq) {
    if (pq->size == 0) return -1;

    int maxVal = pq->data[0];
    pq->data[0] = pq->data[pq->size - 1];
    pq->size--;
    heapifyDown(pq, 0);

    return maxVal;
}

void freePQ(PriorityQueue *pq) {
    free(pq->data);
    free(pq);
}

int main() {
    PriorityQueue *pq = createPQ(10);

    insert(pq, 40);
    insert(pq, 15);
    insert(pq, 30);
    insert(pq, 50);

    printf("Max: %d\n", getMax(pq));
    printf("Extract: %d\n", extractMax(pq));
    printf("Extract: %d\n", extractMax(pq));

    freePQ(pq);
    return 0;
}
