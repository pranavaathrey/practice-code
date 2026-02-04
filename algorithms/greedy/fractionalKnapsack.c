#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double weight;
    double value;
    double ratio;
} Item;

// sort items by value-weight ration, in descending
int compareByItemRatioDesc(const void *a, const void *b) {
    const Item *item1 = (const Item *)a;
    const Item *item2 = (const Item *)b;

    if(item1->ratio > item2->ratio)
        return -1;
    else if(item1->ratio < item2->ratio)
        return 1;
    else 
        return 0;
}

double fractionalKnapsack(Item items[], int n, double capacity) {
    for(int i = 0; i < n; i++) {
        items[i].ratio = items[i].value / items[i].weight;
    }
    qsort(items, n, sizeof(Item), compareByItemRatioDesc);
    
    double currWeight = 0.0, totalValue = 0.0;
    for(int i = 0; i < n; i++) {
        if(currWeight == capacity)
            break;
        else if(currWeight + items[i].weight <= capacity) {
            currWeight += items[i].weight;
            totalValue += items[i].value;
        } else {
            totalValue += items[i].ratio * (capacity - currWeight);
            break;
        }
    }
    return totalValue;
}

int main() {
    // weight-value pairs, 3 items
    Item items[] = {{10.5, 60.0}, {20.0, 100.0}, {30.0, 120.0}};
    int n = sizeof(items) / sizeof(Item);

    double maxValue = fractionalKnapsack(items, n, 48.5);
    printf("Max value fit into the knapsack (including part items): %.2f", maxValue);
    return 0;
}