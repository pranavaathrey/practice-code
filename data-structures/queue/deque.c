#define SIZE 256

int deque[SIZE];
int front = -1, rear = -1;

int isEmpty() {
    return front == -1;
}
int isFull() {
    return front == (rear + 1) % SIZE;
}

void insertFront(int value) {
    if(isFull()) {
        printf("Deque Overflow\n");
        return;
    }
    if(front == -1) front = rear = 0;
    else front = (front - 1 + SIZE) % SIZE;

    deque[front] = value;
    printf("%d inserted at front\n", value);
}
void insertRear(int value) { 
    if(isFull()) {
        printf("Deque Overflow\n");
        return;
    }
    if(front == -1) front = rear = 0;
    else rear = (rear + 1) % SIZE;

    deque[rear] = value;
    printf("%d inserted at rear\n", value);
}

int deleteFront() {
    if(isEmpty()) {
        printf("Deque Underflow\n");
        return -1;
    }
    int value = deque[front];
    if(front == rear) {
        front = -1; rear = -1;
    }else 
        front = (front + 1) % SIZE;

    printf("%d deleted from front\n", value);
    return value;
}
int deleteRear() {
    if(isEmpty()) {
        printf("Deque Underflow\n");
        return -1;
    }
    int value = deque[rear];
    if(front == rear) {
        front = -1; rear = -1;
    }else 
        rear = (rear - 1 + SIZE) % SIZE;

    printf("%d deleted from rear\n", value);
    return value;
}

void display() {
    if(isEmpty()) {
        printf("Deque is empty\n");
        return;
    }
    printf("Deque:");
    int i = front;
    while(1) {
        printf(" %d", deque[i]);

        if(i == rear) break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

// just a data structure, no program here
// AKA Double-ended Queue