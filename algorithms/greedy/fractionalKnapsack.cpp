#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    double weight;
    double value;
    double ratio;
};

double fractionalKnapsack(vector<Item> items, double capacity) {
    for(Item &item: items) 
        item.ratio = item.value / item.weight;
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.ratio > b.ratio; // sort in descending
    });
    
    double currWeight = 0.0, totalValue = 0.0;
    for(Item item: items) {
        if(currWeight == capacity)
            break;
        else if(currWeight + item.weight <= capacity) {
            currWeight += item.weight;
            totalValue += item.value;
        } else {
            totalValue += item.ratio * (capacity - currWeight);
            break;
        }
    }
    return totalValue;
}

int main() {
    // weight-value pairs, 3 items
    vector<Item> items = {{10.5, 60.0}, {20.0, 100.0}, {30.0, 120.0}};
    int n = sizeof(items) / sizeof(Item);

    double maxValue = fractionalKnapsack(items, 48.5);
    cout << "Max value fit into the knapsack (including part items): " << maxValue;
    return 0;
}