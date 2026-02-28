#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Item {
    int id;
    int profit;
    int weight;

    Item(int id = 0, int profit = 0, int weight = 0):
        id(id), profit(profit), weight(weight) {}
};
// to sort items by profit/weight ratio in descending 
bool compareItems(const Item& a, const Item& b) {
    double r1 = static_cast<double>(a.profit) / a.weight;
    double r2 = static_cast<double>(b.profit) / b.weight;
    return r1 > r2;
}

// node in the state space tree
struct Node {
    int level;
    int profit, weight;
    double bound;
    vector<int> path; 

    // min-heap comparator
    bool operator>(const Node& other) const {
        return bound > other.bound;
    }
};
// calculates the (fractional knapsack) upper bound for a given node.
double calculateBound(const Node& u, int n, int capacity, const vector<Item>& items) {
    // if the weight already exceeds capacity, its an invalid path
    if (u.weight >= capacity) return 0; 
    
    double bound_profit = u.profit;
    int j = u.level;
    int total_weight = u.weight;

    // greedily take whole items as long as they fit
    while (j < n && total_weight + items[j].weight <= capacity) {
        total_weight += items[j].weight;
        bound_profit += items[j].profit;
        j++;
    }
    // take a fractional part of the next item
    if (j < n) {
        bound_profit += (capacity - total_weight) 
                      * (static_cast<double>(items[j].profit) / items[j].weight);
    }
    // negate the bound for the min-heap
    return -bound_profit;
}

struct Info {
    int maxProfit;
    vector<int> bestPath; 
};
// Least Cost Branch and Bound Algorithm
Info O1Knapsack(vector<Item> items, int capacity) {
    int n = items.size();
    // sort items based on P[i]/W[i] in descending 
    sort(items.begin(), items.end(), compareItems);

    // PQ is a min-heap based on the negated bound
    priority_queue<Node, vector<Node>, greater<Node>> PQ;

    Node root;
    root.level = 0; // starts at 0 to evaluate the first item at index 0
    root.profit = 0;
    root.weight = 0;
    root.bound = calculateBound(root, n, capacity, items);

    PQ.push(root);
    int maxProfit = 0;
    vector<int> bestPath(n, 0); 

    while (!PQ.empty()) {
        Node current = PQ.top(); PQ.pop();

        // if the current node is promising
        if (current.bound < -maxProfit && current.level < n) {
            // -------- Branch Left: include the current item -------- //
            Node leftNode;
            leftNode.level = current.level + 1;
            leftNode.profit = current.profit + items[current.level].profit;
            leftNode.weight = current.weight + items[current.level].weight;
            leftNode.path = current.path; leftNode.path.push_back(1);

            if (leftNode.weight <= capacity) {
                if (leftNode.profit > maxProfit) {
                    maxProfit = leftNode.profit;                    
                    // construct the best path array in the original item order
                    bestPath.assign(n, 0); 
                    for(size_t i = 0; i < leftNode.path.size(); ++i) 
                        bestPath[items[i].id] = leftNode.path[i];
                }
                leftNode.bound = calculateBound(leftNode, n, capacity, items);
                // push left child if it remains promising
                if (leftNode.bound < -maxProfit) 
                    PQ.push(leftNode);
            }

            // -------- Branch Right: exclude the current item -------- //
            Node rightNode;
            rightNode.level = current.level + 1;
            rightNode.profit = current.profit;
            rightNode.weight = current.weight;
            rightNode.path = current.path; rightNode.path.push_back(0);

            rightNode.bound = calculateBound(rightNode, n, capacity, items);
            // push right child if it remains promising
            if (rightNode.bound < -maxProfit) 
                PQ.push(rightNode);
        }
    }
    return { maxProfit, bestPath };
}

int main() {
    int n; cout << "Enter the number of items: "; cin >> n;
    vector<Item> items(n);

    cout << "Enter the price and weight of each item:\n";
    for(int i = 0; i < n; i++) {
        items[i].id = i;
        cin >> items[i].profit >> items[i].weight;
    }
    int M; cout << "Enter maximum capacity of knapsack: "; cin >> M;

    Info solution = O1Knapsack(items, M);

    cout << "\nPrice      |\t";
    for(int i = 0; i < n; i++) cout << items[i].profit << "\t";
    cout << "\nWeight     |\t";
    for(int i = 0; i < n; i++) cout << items[i].weight << "\t";
    cout << "\nInclusion  |\t";
    for(int x : solution.bestPath) cout << (x? "Yes" : "No") << "\t";
    cout << "\n\n";
    cout << "Maximum Profit: " << solution.maxProfit << endl;

    return 0;
}