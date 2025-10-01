#include <stdio.h>
#define SIZE 256

int queue[SIZE];
int front = -1, rear = -1;

int isEmpty() {
    return front == -1;
}
int isFull() {
    return front == (rear + 1) % SIZE;
}

void enqueue(int value) {
    if(isFull()) {
        printf("Queue Overflow\n");
        return;
    }
    if(front == -1) 
        front = rear = 0;
    else 
        rear = (rear + 1) % SIZE;

    queue[rear] = value;
    printf("%d enqueued\n", value);
}
int dequeue() {
    if(isEmpty()) {
        printf("Queue Underflow\n");
        return -1;
    }
    int value = queue[front];
    if(front == rear) 
        front = rear = -1;
    else 
        front = (front + 1) % SIZE;

    printf("%d dequeued\n", value);
    return value;
}

void display() {
    if(isEmpty()) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue:");
    int i = front;
    while(1) {
        printf(" %d", queue[i]);

        if(i == rear) break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

// just a data structure, no program here