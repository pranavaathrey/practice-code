#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Node {
    int level;
    int pathCost;
    int bound;
    vector<int> assignment;
    vector<int> used;

    bool operator>(const Node &other) const {
        return bound > other.bound;
    }
};

int lowerBound(const vector<vector<int>> &cost, const Node &node) {
    int n = (int)cost.size();
    int lb = node.pathCost;

    for (int worker = node.level; worker < n; worker++) {
        int best = INT_MAX;
        for (int job = 0; job < n; job++) {
            if (!node.used[job] && cost[worker][job] < best) best = cost[worker][job];
        }
        if (best == INT_MAX) return INT_MAX;
        lb += best;
    }
    return lb;
}

pair<int, vector<int>> jobSelectionBnB(const vector<vector<int>> &cost) {
    int n = (int)cost.size();
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    Node root;
    root.level = 0;
    root.pathCost = 0;
    root.assignment.assign(n, -1);
    root.used.assign(n, 0);
    root.bound = lowerBound(cost, root);
    pq.push(root);

    int bestCost = INT_MAX;
    vector<int> bestAssign(n, -1);

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        if (cur.bound >= bestCost) continue;

        if (cur.level == n) {
            if (cur.pathCost < bestCost) {
                bestCost = cur.pathCost;
                bestAssign = cur.assignment;
            }
            continue;
        }

        int worker = cur.level;
        for (int job = 0; job < n; job++) {
            if (cur.used[job]) continue;

            Node child = cur;
            child.level = worker + 1;
            child.assignment[worker] = job;
            child.used[job] = 1;
            child.pathCost = cur.pathCost + cost[worker][job];
            child.bound = lowerBound(cost, child);

            if (child.bound < bestCost) pq.push(child);
        }
    }

    return {bestCost, bestAssign};
}

int main() {
    int n;
    if (!(cin >> n) || n <= 0) return 0;

    vector<vector<int>> cost(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> cost[i][j];
    }

    auto result = jobSelectionBnB(cost);
    cout << result.first << "\n";
    for (int i = 0; i < n; i++) {
        cout << i << " " << result.second[i] << "\n";
    }

    return 0;
}
