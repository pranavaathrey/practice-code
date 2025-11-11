#include <stdio.h>
#include <stdlib.h>

// struct to store two nodes and an edge weight (respectively)
typedef struct {
    int u, v, w;
} Edge;

// Union–Find: determines if cycles are present
int find(int parent[], int x) {
    while (parent[x] != x)
        x = parent[x];
    return x;
}
void unite(int parent[], int a, int b) {
    int pa = find(parent, a);
    int pb = find(parent, b);
    if (pa != pb)
        parent[pb] = pa;   // attach b's root to a's root
}

// qsort compare function (ascending order of weights)
int cmpEdge(const void *a, const void *b) {
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    return e1->w - e2->w;
}

void kruskal(int n, Edge edges[], int m) {
    // sort edges by weight
    qsort(edges, m, sizeof(Edge), cmpEdge);

    int parent[n];        // initialize
    for (int i = 0; i < n; i++)
        parent[i] = i;    // each vertex is its own set

    printf("Edges in MST:\n");
    int total = 0, count = 0;

    for (int i = 0; i < m && count < n - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        // check if u and v belong to different sets
        if (find(parent, u) != find(parent, v)) {
            unite(parent, u, v);
            printf("%d - %d   weight = %d\n", u, v, w);
            total += w;
            count++;
        }
    }
    printf("Total weight = %d\n", total);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Edge *edges = malloc(sizeof(Edge) * m);

    for (int i = 0; i < m; i++)
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);

    kruskal(n, edges, m);

    free(edges);
    return 0;
}
