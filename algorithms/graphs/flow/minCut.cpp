#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class MinCut {
    int n;
    vector<vector<int>> cap;
    vector<vector<int>> original;
    vector<vector<int>> adj;

    public:
    MinCut(int n) : n(n), cap(n, vector<int>(n, 0)), original(n, vector<int>(n, 0)), adj(n) {}

    void addEdge(int u, int v, int c) {
        if (u < 0 || v < 0 || u >= n || v >= n) return;
        adj[u].push_back(v);
        adj[v].push_back(u);
        cap[u][v] += c;
        original[u][v] += c;
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
                if (parent[v] == -1 && cap[u][v] > 0) {
                    parent[v] = u;
                    int newFlow = min(flow, cap[u][v]);
                    if (v == t) 
                        return newFlow;
                    q.push({v, newFlow});
                }
            }
        }
        return 0;
    }

    int maxFlow(int s, int t) { // Edmonds-Karp
        int flow = 0;
        vector<int> parent(n);
        int pushed;

        while ((pushed = bfs(s, t, parent)) > 0) {
            flow += pushed;
            int cur = t;
            while (cur != s) {
                int prev = parent[cur];
                cap[prev][cur] -= pushed;
                cap[cur][prev] += pushed;
                cur = prev;
            }
        }
        return flow;
    }

    vector<int> reachableFromSource(int s) {
        vector<int> vis(n, 0);
        queue<int> q;
        q.push(s);
        vis[s] = 1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (!vis[v] && cap[u][v] > 0) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
        return vis;
    }

    void printMinCut(int s) {
        vector<int> vis = reachableFromSource(s);
        for (int u = 0; u < n; u++) {
            if (!vis[u]) continue;
            for (int v = 0; v < n; v++) {
                if (vis[v]) continue;
                if (original[u][v] > 0) {
                    cout << u << " " << v << "\n";
                }
            }
        }
    }
};

int main() {
    int V, E, s, t;
    if (!(cin >> V >> E >> s >> t) 
    || V <= 0 || E < 0) 
        return 0;

    MinCut mc(V);
    for (int i = 0; i < E; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        mc.addEdge(u, v, c);
    }
    cout << mc.maxFlow(s, t) << "\n";
    mc.printMinCut(s);
    return 0;
}
