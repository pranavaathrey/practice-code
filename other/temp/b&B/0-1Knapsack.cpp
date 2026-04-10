#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Item {
    int id;
    double profit;
    double weight;

    Item(int id = 0, double profit = 0.0, double weight = 0.0) : id(id), profit(profit), weight(weight) {}
};

bool compareItems(const Item &a, const Item &b) {
    return (a.profit / a.weight) > (b.profit / b.weight);
}

struct Node {
    int level;
    double profit;
    double weight;
    double bound;

    bool operator>(const Node &other) const {
        return bound > other.bound;
    }
};

double calculateBound(const Node &u, int n, double capacity, const vector<Item> &items) {
    if (u.weight >= capacity) return 0;

    double boundProfit = u.profit;
    int j = u.level;
    double totalWeight = u.weight;

    while (j < n && totalWeight + items[j].weight <= capacity) {
        totalWeight += items[j].weight;
        boundProfit += items[j].profit;
        j++;
    }
    if (j < n) {
        boundProfit += (capacity - totalWeight) * (items[j].profit / items[j].weight);
    }

    return -boundProfit;
}

double O1Knapsack(vector<Item> items, double capacity) {
    int n = (int)items.size();
    sort(items.begin(), items.end(), compareItems);

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    Node root{0, 0, 0, 0};
    root.bound = calculateBound(root, n, capacity, items);
    pq.push(root);

    double maxProfit = 0;

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        if (cur.bound >= -maxProfit || cur.level >= n) continue;

        Node left;
        left.level = cur.level + 1;
        left.profit = cur.profit + items[cur.level].profit;
        left.weight = cur.weight + items[cur.level].weight;

        if (left.weight <= capacity) {
            if (left.profit > maxProfit) maxProfit = left.profit;
            left.bound = calculateBound(left, n, capacity, items);
            if (left.bound < -maxProfit) pq.push(left);
        }

        Node right;
        right.level = cur.level + 1;
        right.profit = cur.profit;
        right.weight = cur.weight;
        right.bound = calculateBound(right, n, capacity, items);
        if (right.bound < -maxProfit) pq.push(right);
    }

    return maxProfit;
}

int main() {
    int n;
    double capacity;
    if (!(cin >> n >> capacity) || n < 0) return 0;

    vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        cin >> items[i].weight >> items[i].profit;
        items[i].id = i;
    }

    cout << O1Knapsack(items, capacity) << "\n";
    return 0;
}
