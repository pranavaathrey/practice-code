#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

using namespace std;

struct Item {
    double value;
    double weight;
    double ratio;

    Item(double v, double w):
        value(v), weight(w), ratio(v/w) {}
};

double fitMaxValue(double remainingCapacity, vector<Item> items) {
    sort(items.begin(), items.end(), [](const Item &a, const Item &b) {
        return a.ratio > b.ratio;
    });
    double maxValue = 0.0;

    for(Item item: items) {
        if(remainingCapacity == 0) break;

        if(item.weight <= remainingCapacity) {
            remainingCapacity -= item.weight;
            maxValue += item.value;
        } else {
            maxValue += remainingCapacity * item.ratio;
            remainingCapacity = 0;
        }
    }
    return maxValue;
}

int main() {
    vector<Item> items = {
        {93.2, 234.3}, {23.43, 32.1},
        {93.2, 234.3}, {23.43, 32.1},
        {93.2, 234.3}, {23.43, 32.1},
    };
    double capacity = 150.00;
    cout << fixed << setprecision(2) << fitMaxValue(capacity, items);
}