#include <iostream>
#include <vector>

using namespace std;

const int INF = 1000000000;

class Graph {
    int V, E;
    vector<vector<int>> dist;

public:
    Graph(int v, int e) : V(v), E(e) {
        dist.assign(V, vector<int>(V, INF));
        for (int i = 0; i < V; ++i)
            dist[i][i] = 0;
    }

    void addEdge(int u, int v, int w) {
        dist[u][v] = w;
    }

    void floydWarshall() {
        for (int k = 0; k < V; ++k)
            for (int i = 0; i < V; ++i)
                for (int j = 0; j < V; ++j)
                    if (dist[i][k] != INF && dist[k][j] != INF
                        && dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
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
    if (!(cin >> V >> E)) return 0;
    Graph g(V, E);

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    g.floydWarshall();
    return 0;
}