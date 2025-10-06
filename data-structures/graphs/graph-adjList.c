#include <stdio.h>
#include <stdlib.h>

// represents a node in adjacency list
typedef struct Node {
    int dest;
    struct Node* next;
} Node;
// represents an adjacency list
typedef struct AdjList {
    Node* head;
} AdjList;
// represents the whole graph
typedef struct Graph {
    int V;                // vertice count
    AdjList* list;        // array of adjacency lists
} Graph;

// create a new adjacency list node
Node* createNode(int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// create a graph with V vertices
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;

    graph->list = (AdjList*)malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; i++)
        graph->list[i].head = NULL;

    return graph;
}

// add edge (u, v) to an undirected graph
void addEdge(Graph* graph, int u, int v) {
    // add v to u’s list
    Node* newNode = createNode(v);
    newNode->next = graph->list[u].head;
    graph->list[u].head = newNode;

    // add u to v’s list (since the graph is undirected)
    newNode = createNode(u);
    newNode->next = graph->list[v].head;
    graph->list[v].head = newNode;
}

/* ------------------------- BFS ------------------------- */
void BFS(Graph* graph, int startVertex) {
    int* visited = (int*)calloc(graph->V, sizeof(int));
    int* queue = (int*)malloc(graph->V * sizeof(int));
    int front = 0, rear = 0;

    visited[startVertex] = 1;
    queue[rear++] = startVertex;

    printf("\nBFS starting from vertex %d: ", startVertex);

    while (front != rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        Node* temp = graph->list[currentVertex].head;
        while (temp) {
            int adjVertex = temp->dest;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }
    printf("\n");
    free(queue);
    free(visited);
}

/* ------------------------- DFS ------------------------- */
void DFSUtil(Graph* graph, int vertex, int* visited) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    Node* temp = graph->list[vertex].head;
    while (temp) {
        int adjVertex = temp->dest;
        if (!visited[adjVertex])
            DFSUtil(graph, adjVertex, visited);
        temp = temp->next;
    }
}
void DFS(Graph* graph, int startVertex) {
    int* visited = (int*)calloc(graph->V, sizeof(int));
    printf("\nDFS starting from vertex %d: ", startVertex);
    DFSUtil(graph, startVertex, visited);
    printf("\n");
    free(visited);
}

// print adjacency list representation of graph
void printGraph(Graph* graph) {
    for (int v = 0; v < graph->V; ++v) {
        Node* temp = graph->list[v].head;
        printf("Adjacency list of vertex %d\n head", v);
        while (temp) {
            printf(" -> %d", temp->dest);
            temp = temp->next;
        }
        printf("\n");
    }
}
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        Node* temp = graph->list[i].head;
        while (temp) {
            Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph->list);
    free(graph);
}

int main() {
    int V = 6;
    struct Graph* graph = createGraph(V);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);

    printGraph(graph);

    BFS(graph, 0);
    DFS(graph, 0);

    freeGraph(graph);
    return 0;
}