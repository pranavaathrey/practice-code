#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class MaxFlow {
    int n;
    vector<vector<int>> capacity;
    vector<vector<int>> adj;

public:
    MaxFlow(int n) : n(n), capacity(n, vector<int>(n, 0)), adj(n) {}

    void addEdge(int u, int v, int c) {
        if (u < 0 || v < 0 || u >= n || v >= n) return;
        adj[u].push_back(v);
        adj[v].push_back(u);
        capacity[u][v] += c;
    }

    int bfs(int s, int t, vector<int> &parent) {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
        queue<pair<int, int>> q;
        q.push({s, INT_MAX});

        while (!q.empty()) {
            int u = q.front().first;
            int flow = q.front().second;
            q.pop();

            for (int v : adj[u]) {
                if (parent[v] == -1 && capacity[u][v] > 0) {
                    parent[v] = u;
                    int newFlow = min(flow, capacity[u][v]);
                    if (v == t) return newFlow;
                    q.push({v, newFlow});
                }
            }
        }
        return 0;
    }

    int fordFulkerson(int s, int t) {
        int flow = 0;
        vector<int> parent(n);
        int pushed;

        while ((pushed = bfs(s, t, parent)) > 0) {
            flow += pushed;
            int cur = t;
            while (cur != s) {
                int prev = parent[cur];
                capacity[prev][cur] -= pushed;
                capacity[cur][prev] += pushed;
                cur = prev;
            }
        }
        return flow;
    }
};

int main() {
    int V, E, s, t;
    if (!(cin >> V >> E >> s >> t) || V <= 0 || E < 0) return 0;

    MaxFlow mf(V);
    for (int i = 0; i < E; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        mf.addEdge(u, v, c);
    }

    cout << mf.fordFulkerson(s, t) << "\n";
    return 0;
}