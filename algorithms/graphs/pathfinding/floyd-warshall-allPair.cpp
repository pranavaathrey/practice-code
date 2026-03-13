#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// We use a safely large number instead of INT_MAX to prevent 
// integer overflow when adding two "infinite" distances together.
const int INF = 1e9; 

class Graph {
    int V, E;
    vector<vector<int>> dist;

    public:
    Graph(int v, int e) : V(v), E(e) {
        // Initialize the adjacency matrix. 
        // Distance to self is 0, all other distances are initially INF.
        dist.assign(V, vector<int>(V, INF));
        for (int i = 0; i < V; ++i) 
            dist[i][i] = 0;
    }
    void addEdge(int u, int v, int w) {
        // For a directed graph, we only set dist[u][v].
        dist[u][v] = w;
    }

    void floydWarshall() {
        // Core Floyd-Warshall logic: Dynamic Programming
        // k is the intermediate vertex
        for (int k = 0; k < V; ++k) 
            // i is the source vertex
            for (int i = 0; i < V; ++i) 
                // j is the destination vertex
                for (int j = 0; j < V; ++j) 
                    // Relax the path if going through vertex k is shorter
                    if (dist[i][k] != INF && dist[k][j] != INF 
                        && dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
        // Negative weight cycle detection
        // If the distance from any vertex to itself becomes negative, 
        // a negative cycle exists.
        for (int i = 0; i < V; ++i) 
            if (dist[i][i] < 0) {
                cout << "Graph contains a negative weight cycle." << endl;
                return;
            }
        printResult();
    }

    void printResult() {
        cout << "All-Pairs Shortest Path Matrix:" << endl;
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][j] == INF)
                    cout << "INF\t";
                else
                    cout << dist[i][j] << "\t";
            }
            cout << endl;
        }
    }
};

int main() {
    int V, E;
    Graph g(V, E);
    
    // Read edges and populate the adjacency matrix
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    cout << "Vertices: " << V << "\n";
    cout << "Edges: " << E << "\n";
    cout << "--- Results ---\n";

    // Invoke the all-pairs shortest path algorithm
    g.floydWarshall();
    return 0;
}