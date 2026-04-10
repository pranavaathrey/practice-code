#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge {
    int source;
    int destination;
    int weight;
};

class Graph {
    int V, E;
    vector<Edge> edges;

public:
    Graph(int v, int e) : V(v), E(e) {}

    void addEdge(int u, int v, int w) {
        edges.push_back({u, v, w});
    }

    void bellmanFord(int src) {
        vector<int> distance(V, INT_MAX);
        distance[src] = 0;

        for (int i = 1; i <= V - 1; ++i) {
            for (const auto &edge : edges) {
                int u = edge.source;
                int v = edge.destination;
                int weight = edge.weight;

                if (distance[u] != INT_MAX && distance[u] + weight < distance[v])
                    distance[v] = distance[u] + weight;
            }
        }
        for (const auto &edge : edges) {
            int u = edge.source;
            int v = edge.destination;
            int weight = edge.weight;

            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                cout << "Graph contains a negative weight cycle." << endl;
                return;
            }
        }
        printResult(distance);
    }

    void printResult(const vector<int>& distance) {
        cout << "Vertex\tDistance from Source" << endl;
        for (int i = 0; i < V; ++i) {
            cout << i << "\t"
                 << (distance[i] == INT_MAX ? "INF" : to_string(distance[i]))
                 << endl;
        }
    }
};

int main() {
    int V, E, src;
    if (!(cin >> V >> E >> src)) return 0;

    Graph g(V, E);
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    g.bellmanFord(src);
    return 0;
}