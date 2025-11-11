#include <stdio.h>
#include <limits.h>

#define INF INT_MAX

// pick the vertex with the minimum key value that is not yet in MST
int minKey(int key[], int visited[], int n) {
    int min = INF, min_index = -1;
    for (int v = 0; v < n; v++) 
        if (!visited[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    return min_index;
}

void prim(int n, int graph[n][n]) {
    int parent[n];     // stores previous node (parent -> i)
    int key[n];        // minimum cost to add this vertex
    int visited[n];      // true if vertex is already included

    // initialize. set everything to unvisited & distance to INF
    for (int i = 0; i < n; i++) {
        key[i] = INF;
        visited[i] = 0;
    }
    key[0] = 0;        // start from vertex 0
    parent[0] = -1;    // first node has no parent

    for (int count = 0; count < n - 1; count++) {
        // find smallest distance node not in MST, and mark visited
        int u = minKey(key, visited, n);
        visited[u] = 1;

        // update key for neighbors of u (if we've found cheaper routes)
        for (int v = 0; v < n; v++) {
            // graph[u][v] != 0 means there is an edge
            if (graph[u][v] && !visited[v] 
                && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
    // print MST
    int total = 0;
    printf("Edges in MST:\n");
    for (int v = 1; v < n; v++) {
        printf("%d -> %d   weight = %d\n", 
            parent[v], v, graph[v][parent[v]]);
        total += graph[v][parent[v]];
    }
    printf("Total weight = %d\n", total);
}

int main() {
    int n;
    scanf("%d", &n);

    int graph[n][n];

    // input adjacency matrix
    // 0 means no edge except diagonal is 0
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);
    
    prim(n, graph);

    return 0;
}
