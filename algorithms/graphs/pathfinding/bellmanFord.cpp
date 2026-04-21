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
    Graph(int v, int e): V(v), E(e) {}

    void addEdge(int u, int v, int w) {
        edges.push_back({u, v, w});
    }

    void bellmanFord(int src) {
        vector<int> distance(V, INT_MAX);
        vector<int> pi(V, -1);
        distance[src] = 0;

        for(int i = 1; i <= V - 1; i++) {
            for(const auto &edge: edges) {
                int u = edge.source;
                int v = edge.destination;
                int weight = edge.weight;

                if(distance[u] != INT_MAX 
                && distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                    pi[v] = u;
                }
            }
        }
        for(const auto &edge: edges) {
            int u = edge.source;
            int v = edge.destination;
            int weight = edge.weight;

            if(distance[u] != INT_MAX 
            && distance[u] + weight < distance[v]) {
                cout << "\nGraph contains negative weight cycle(s)." << endl;
                return;
            }
        }
        printResult(distance, pi, src);
    }

    void printResult(const vector<int>& distance, 
                     const vector<int>& pi, int src) {
        cout << "\nVertex\tDistance from Source" << endl;
        for(int i = 0; i < V; i++) {
            cout << i << "\t"
                 << ((distance[i] == INT_MAX)? 
                    "INF" : to_string(distance[i]))
                 << endl;
        }
        cout << "\nPaths from each vertex to source: " << endl;
        for(int i = 0; i < V; i++) {
            if(i == src) continue;
            cout << "From " << src << " to " << i << ": " << i;

            if(pi[i] == -1) {
                cout << " <- Unreachable..." << endl;
                continue;
            }
            for(int j = i; j != src; j = pi[j]) 
                cout << " <- " << pi[j];
            cout << endl;
        }
    }
};

int main() {
    cout << "Enter number of vertices, edges, and the source vertex: ";
    int V, E, src;
    if(!(cin >> V >> E >> src)) return 0;

    cout << "Enter edge information (u, v, w):" << endl;
    Graph g(V, E);
    for(int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    g.bellmanFord(src);
    return 0;
}



/* REGION Sample output: 
> ./a.exe
Enter number of vertices, edges, and the source vertex: 5 10 0
Enter edge information (u, v, w):
0 1 6
0 3 7
1 3 8
1 4 -4
1 2 5
2 1 -2
3 2 -3
4 3 9
4 0 2
4 2 7

Vertex  Distance from Source
0       0
1       2
2       4
3       7
4       -2

Paths from each vertex to source:
From 0 to 1: 1 <- 2 <- 3 <- 0
From 0 to 2: 2 <- 3 <- 0
From 0 to 3: 3 <- 0
From 0 to 4: 4 <- 1 <- 2 <- 3 <- 0
*/