#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// represents an edge
typedef struct {
    int src, dest, weight;
} Edge;

void BellmanFord(Edge edges[], int V, int E, int src) {
    int distance[V];

    // Step 1: Initialize distances
    for (int i = 0; i < V; i++)
        distance[i] = INT_MAX;
    distance[src] = 0;

    // Step 2: Relax edges |V| - 1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;
            if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
            }
        }
    }
    // Step 3: Check for negative-weight cycles
    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;
        if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
            printf("Graph contains a negative weight cycle.\n");
            return;
        }
    }
    // Print result
    printf("Vertex\tDistance from Source (%d)\n", src);
    for (int i = 0; i < V; i++) {
        if (distance[i] == INT_MAX)
            printf("%d\tINF\n", i);
        else
            printf("%d\t%d\n", i, distance[i]);
    }
}

int main() {
    int V, E, src;

    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);

    Edge *edges = (Edge *)malloc(E * sizeof(Edge));

    printf("Enter edges (src dest weight):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
    }

    printf("Enter source vertex: ");
    scanf("%d", &src);

    BellmanFord(edges, V, E, src);

    free(edges);
    return 0;
}
