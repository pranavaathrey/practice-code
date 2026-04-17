#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

struct Item {
    int id;
    double profit;
    double weight;

    Item(int id = 0, double p = 0, double w = 0): 
             id(id), profit(p), weight(w) {}
};
bool Compare(const Item &a, const Item &b) {
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

double calculateBound(Node &node, vector<Item> &items, int n, double capacity) {
    if(node.weight > capacity)
        return 0;

    double boundProfit = node.profit;
    double currWeight = node.weight;
    int j = node.level;

    while(j < n && currWeight + items[j].weight <= capacity) {
        currWeight += items[j].weight;
        boundProfit += items[j].profit;
        j++;
    }
    if(j < n)
        boundProfit += (capacity - currWeight)
                     * (items[j].profit / items[j].weight);
    return -boundProfit;
}

double knapsack(vector<Item> items, double capacity) {
    int n = items.size();
    sort(items.begin(), items.end(), Compare);

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    Node root{0, 0, 0, 0};
    root.bound = calculateBound(root, items, n, capacity);
    pq.push(root);

    double maxProfit = 0;

    while(!pq.empty()) {
        Node curr = pq.top(); pq.pop();

        if(curr.bound >= -maxProfit || curr.level >= n) continue;

        Node left;
        left.level = curr.level + 1;
        left.profit = curr.profit + items[curr.level].profit;
        left.weight = curr.weight + items[curr.level].weight;

        if(left.weight <= capacity) {
            if(left.profit > maxProfit) maxProfit = left.profit;
            left.bound = calculateBound(left, items, n, capacity);
            if(left.bound < -maxProfit) pq.push(left);
        }

        Node right;
        right.level = curr.level + 1;
        right.profit = curr.profit;
        right.weight = curr.weight;

        right.bound = calculateBound(right, items, n, capacity);
        if(right.bound < -maxProfit) pq.push(right);
    }
    return maxProfit;
}

int main() {
    int n; double capacity;
    if (!(cin >> n >> capacity) || n < 0) return 0;

    vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        cin >> items[i].weight >> items[i].profit;
        items[i].id = i;
    }
    cout << knapsack(items, capacity) << "\n";
    return 0;
}
