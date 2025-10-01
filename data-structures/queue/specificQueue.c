#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int queue[MAX];
int front = -1, rear = -1, size = 0, capacity;

int isFull() {
    return size == capacity;
}
int isEmpty() {
    return size == 0;
}

// even only enqueue
void enqueue(int value) {
    if (value % 2 != 0) {
        printf("Only even numbers can be enqueued!\n");
        return;
    }
    if (isFull()) {
        printf("Queue Overflow\n");
        return;
    }
    if(front == -1) front = 0;
    rear = (rear + 1) % capacity;
    
    queue[rear] = value;
    size++;
}

// dequeue maximum element
void dequeueMax() {
    if (isEmpty()) {
        printf("Queue Underflow\n");
        return;
    }
    // find max element and its index
    int maxVal = queue[front];
    int maxIdx = front;
    int idx = front;
    for (int i = 0; i < size; i++) {
        if (queue[idx] > maxVal) {
            maxVal = queue[idx];
            maxIdx = idx;
        }
        idx = (idx + 1) % capacity;
    }
    // remove max element by shifting others
    int next = (maxIdx + 1) % capacity;
    while (next != (rear + 1) % capacity) {
        queue[maxIdx] = queue[next];
        maxIdx = next;
        next = (next + 1) % capacity;
    }
    rear = (rear - 1 + capacity) % capacity;
    size--;

    if (size == 0) 
        front = rear = -1;
    printf("Element dequeued: %d\n", maxVal);
}

// Display queue
void display() {
    if (isEmpty()) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue elements: ");
    int idx = front;
    for (int i = 0; i < size; i++) {
        printf("%d ", queue[idx]);
        idx = (idx + 1) % capacity;
    }
    printf("\n");
}

int main() {
    int choice, value;

    scanf("%d", &capacity);
    if (capacity > MAX) capacity = MAX; 

    while (1) {
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                scanf("%d", &value);
                enqueue(value);
                break;
            case 2:
                dequeueMax();
                break;
            case 3:
                display();
                break;
            case 4:
                printf("Exit\n");
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
}
