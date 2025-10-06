#include <stdio.h>
#include <stdlib.h>

typedef struct GraphMatrix {
    int V;
    int** adj;
} GraphMatrix;

GraphMatrix* createGraph(int V) {
    GraphMatrix* graph = (GraphMatrix*)malloc(sizeof(GraphMatrix));
    graph->V = V;

    graph->adj = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) 
        graph->adj[i] = (int*)calloc(V, sizeof(int));
    return graph;
}
void addEdge(GraphMatrix* graph, int u, int v) {
    graph->adj[u][v] = 1;
    graph->adj[v][u] = 1; // undirected
}

/* ------------------------- BFS ------------------------- */
void BFS(GraphMatrix* graph, int start) {
    int* visited = (int*)calloc(graph->V, sizeof(int));
    int* queue = (int*)malloc(graph->V * sizeof(int));
    int front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    printf("\nBFS starting from vertex %d: ", start);

    while (front != rear) {
        int current = queue[front++];
        printf("%d ", current);

        for (int i = 0; i < graph->V; i++) {
            if (graph->adj[current][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }

    printf("\n");
    free(queue);
    free(visited);
}

/* ------------------------- DFS ------------------------- */
void DFSUtil(GraphMatrix* graph, int v, int* visited) {
    visited[v] = 1;
    printf("%d ", v);

    for (int i = 0; i < graph->V; i++) {
        if (graph->adj[v][i] && !visited[i])
            DFSUtil(graph, i, visited);
    }
}
void DFS(GraphMatrix* graph, int start) {
    int* visited = (int*)calloc(graph->V, sizeof(int));
    printf("\nDFS starting from vertex %d: ", start);
    DFSUtil(graph, start, visited);
    printf("\n");
    free(visited);
}

/* ------------------- Other Utilities ------------------- */
void printGraph(GraphMatrix* graph) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graph->V; i++) {
        for (int j = 0; j < graph->V; j++)
            printf("%d ", graph->adj[i][j]);
        printf("\n");
    }
}
void freeGraphMatrix(GraphMatrix* graph) {
    for (int i = 0; i < graph->V; i++)
        free(graph->adj[i]);
    free(graph->adj);
    free(graph);
}

int main() {
    int V = 5;
    GraphMatrix* graph = createGraph(V);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 4);

    printGraph(graph);

    BFS(graph, 0);
    DFS(graph, 0);

    // cleanup
    for (int i = 0; i < V; i++)
        free(graph->adj[i]);
    free(graph->adj);
    free(graph);

    return 0;
}