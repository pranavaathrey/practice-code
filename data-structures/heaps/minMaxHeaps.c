#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int arr[MAX];
    int size;
} Heap;

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// ----HEAPIFY---- //

void minHeapify(Heap *h, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < h->size && h->arr[left] < h->arr[smallest])
        smallest = left;

    if (right < h->size && h->arr[right] < h->arr[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&h->arr[i], &h->arr[smallest]);
        minHeapify(h, smallest);
    }
}
void maxHeapify(Heap *h, int i) {
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

// ----BUILD HEAP---- //

void buildMinHeap(Heap *h) {
    for (int i = h->size / 2 - 1; i >= 0; i--)
        minHeapify(h, i);
}
void buildMaxHeap(Heap *h) {
    for (int i = h->size / 2 - 1; i >= 0; i--)
        maxHeapify(h, i);
}

// ----INSERTION---- //

void insertMinHeap(Heap *h, int x) {
    if (h->size >= MAX) {
        printf("Heap full\n");
        return;
    }
    int i = h->size++;
    h->arr[i] = x;

    while (i != 0 && h->arr[(i - 1) / 2] > h->arr[i]) {
        swap(&h->arr[i], &h->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
void insertMaxHeap(Heap *h, int x) {
    if (h->size >= MAX) {
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

// ----GET MIN/MAX---- //

int extractMin(Heap *h) {
    if (h->size <= 0)
        return -1;

    int root = h->arr[0];
    h->arr[0] = h->arr[--h->size];
    minHeapify(h, 0);
    return root;
}
int extractMax(Heap *h) {
    if (h->size <= 0)
        return -1;

    int root = h->arr[0];
    h->arr[0] = h->arr[--h->size];
    maxHeapify(h, 0);
    return root;
}

// print the heap
void printHeap(Heap *h) {
    for (int i = 0; i < h->size; i++)
        printf("%d ", h->arr[i]);
    printf("\n");
}

int main() {
    Heap h;
    h.size = 0;

    printf("Inserting into Min Heap:\n");
    insertMinHeap(&h, 10);
    insertMinHeap(&h, 5);
    insertMinHeap(&h, 20);
    insertMinHeap(&h, 2);
    printHeap(&h);

    printf("Extract Min: %d\n", extractMin(&h));
    printHeap(&h);

    h.size = 0;
    printf("\nInserting into Max Heap:\n");
    insertMaxHeap(&h, 10);
    insertMaxHeap(&h, 5);
    insertMaxHeap(&h, 20);
    insertMaxHeap(&h, 2);
    printHeap(&h);

    printf("Extract Max: %d\n", extractMax(&h));
    printHeap(&h);

    return 0;
}
