#include <stdio.h>
#include <limits.h>

#define MAX 100  

// finds vertex with minimum distance
int minDistance(int dist[], int visited[], int V) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Dijkstra’s Algorithm
void dijkstra(int graph[MAX][MAX], int V, int src) {
    int dist[MAX];     // dist[i] will hold shortest distance from src to i
    int visited[MAX];  // visited[i] is 1 if vertex i is finalized

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited, V);
        if (u == -1) break; // No more reachable vertices
        visited[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("\nVertex\tDistance from Source (%d)\n", src);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX)
            printf("%d\tINF\n", i);
        else
            printf("%d\t%d\n", i, dist[i]);
    }
}

int main() {
    int V, E;
    int graph[MAX][MAX] = {0};

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    printf("Enter edges in the format: src dest weight\n");
    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;   // directed graph
        // if undirected, also add: graph[v][u] = w;
    }

    int src;
    printf("Enter the source vertex: ");
    scanf("%d", &src);

    dijkstra(graph, V, src);

    return 0;
}
