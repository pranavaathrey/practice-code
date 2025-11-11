#include <stdio.h>
#include <stdlib.h>

// adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;
typedef struct {
    Node* head;
} List;

// graph
typedef struct {
    int numVertices;
    List* adjLists;
    int* visited;
} Graph;
Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(List));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i].head = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}
Node* createNode(int v) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}
void addEdge(Graph* graph, int src, int dest) {
    // add edge from src to dest
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src].head;
    graph->adjLists[src].head = newNode;

    // for undirected graph, add reverse edge
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest].head;
    graph->adjLists[dest].head = newNode;
}

#define MAX_VERTICES 100
// queue
typedef struct {
    int items[MAX_VERTICES];
    int front, rear;
} Queue;
Queue* createQueue() {
    Queue* q = malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}
int isEmpty(Queue* q) {
    return q->rear == -1;
}
void enqueue(Queue* q, int value) {
    if (q->rear == MAX_VERTICES - 1)
        return;    
    if (q->front == -1)
        q->front = 0;
    
    q->rear++;
    q->items[q->rear] = value;
}
int dequeue(Queue* q) {
    int item;
    if (isEmpty(q))
        return -1;

    item = q->items[q->front];
    q->front++;

    if (q->front > q->rear) 
        q->front = q->rear = -1;
    return item;
}

void BFS(Graph* graph, int startVertex) {
    Queue* q = createQueue();

    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);

    printf("Breadth First Search starting from vertex %d:\n", 
        startVertex);

    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        printf("%d ", currentVertex);

        Node* temp = graph->adjLists[currentVertex].head;
        while (temp) {
            int adjVertex = temp->vertex;
            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

int main() {
    Graph* graph = createGraph(6);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);

    BFS(graph, 0);

    return 0;
}
