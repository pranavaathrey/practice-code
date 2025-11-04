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

void DFS(Graph* graph, int vertex) {
    Node* adjList = graph->adjLists[vertex].head;
    Node* temp = adjList;

    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL) {
        int connectedVertex = temp->vertex;

        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
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

    printf("Depth First Search starting from vertex 0:\n");
    DFS(graph, 0);

    printf("\n");
    return 0;
}
