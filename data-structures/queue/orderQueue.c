#include <stdio.h>
#include <string.h>

#define SIZE 100
#define MAX_ITEMS 20

typedef struct {
    int orderNo;
    char customer[100];
    int itemCount;
    char items[MAX_ITEMS][100];
} Order;

Order dummy = {-1, "", 0, {""}};

Order queue[SIZE];
int front = -1, rear = -1;

int isEmpty() {
    return front == -1;
}
int isFull() {
    return front == (rear + 1) % SIZE;
}

void enqueue(Order order) {
    if(isFull()) {
        printf("Queue is full\n");
        return;
    }
    if(front == -1) front = 0;
    rear = (rear + 1) % SIZE;
    
    queue[rear] = order;
}
Order dequeue() {
    if(isEmpty()) {
        printf("Queue is empty\n");
        return dummy;
    }
    Order order = queue[front];
    if(front == rear)
        front = rear = -1;
    else
        front = (front + 1) % SIZE;
    return order;
}

void display() {
    if(isEmpty()) {
        printf("Queue is empty\n");
        return;
    }
    int i = front;
    while(1) {
        printf("%d %s ", 
            queue[i].orderNo, queue[i].customer);
        for(int j = 0; j < queue[i].itemCount; j++)
            printf("%s, ", queue[i].items[j]);
        
        if(i == rear) break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

int main() {
    while(1) {
        int choice; scanf("%d", &choice);
        
        Order order;
        switch(choice) {
            case 1:
                scanf("%d %s %d",
                    &order.orderNo,
                     order.customer,
                    &order.itemCount);
                for(int i = 0; i < order.itemCount; i++)
                    scanf("%s", order.items[i]);
                
                enqueue(order);
                printf("Order added to queue\n");
                break;
            case 2:
                order = dequeue();
                if(order.orderNo == -1) break;
                
                printf("Order number: %d\n", order.orderNo);
                printf("Customer name: %s\n", order.customer);
                printf("Food items: \n");
                
                for(int i = 0; i < order.itemCount; i++)
                    printf("%s\n", order.items[i]);
                break;
            case 3:
                display();
                break;
            case 4:
                return 0;
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    }
}





