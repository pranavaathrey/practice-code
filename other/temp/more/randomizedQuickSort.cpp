#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int partitionArray(vector<int> &a, int l, int r) {
    int pivot = a[r];
    int i = l - 1;
    for (int j = l; j < r; j++) {
        if (a[j] <= pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[r]);
    return i + 1;
}

int randomizedPartition(vector<int> &a, int l, int r) {
    int p = l + rand() % (r - l + 1);
    swap(a[p], a[r]);
    return partitionArray(a, l, r);
}

void randomizedQuickSort(vector<int> &a, int l, int r) {
    if (l >= r) return;
    int p = randomizedPartition(a, l, r);
    randomizedQuickSort(a, l, p - 1);
    randomizedQuickSort(a, p + 1, r);
}

int main() {
    int n;
    if (!(cin >> n) || n < 0) return 0;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    srand((unsigned)time(nullptr));
    if (n > 0) randomizedQuickSort(a, 0, n - 1);

    for (int i = 0; i < n; i++) {
        cout << a[i] << (i + 1 == n ? '\n' : ' ');
    }
    if (n == 0) cout << "\n";
    return 0;
}
