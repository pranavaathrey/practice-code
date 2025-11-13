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