#define SIZE 256

int queue[SIZE];
int front = 0, rear = -1;

int isEmpty() {
    return front > rear;
}
int isFull() {
    return rear == SIZE - 1;
}

void enqueue(int value) {
    if(isFull()) {
        printf("Queue Overflow\n");
        return;
    }
    queue[++rear] = value;
    printf("%d enqueued\n", value);
}
int dequeue() {
    if(isEmpty()) {
        printf("Queue Underflow\n");
        return -1;
    }
    int value = queue[front++];
    printf("%d dequeued\n", value);

    // reset queue
    if(front > rear) {front = 0; rear = -1;}
    return value;
}

void display() {
    if(isEmpty()) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue:");
    for(int i = front; i <= rear; i++) 
        printf(" %d", queue[i]);
    printf("\n");
}

// just a data structure, no program here