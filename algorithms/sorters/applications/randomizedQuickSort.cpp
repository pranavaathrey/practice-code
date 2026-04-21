#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int randomizedPartition(vector<int> &array, int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(array[randomIndex], array[high]);

    int pivot = array[high];
    int i = low - 1;
    for(int j = low; j < high; j++) 
        if(array[j] <= pivot) {
            i++;
            swap(array[i], array[j]);
        }
    swap(array[i + 1], array[high]);
    return i + 1;
}
void randomizedQuickSort(vector<int> &array, int low, int high) {
    if(low >= high) 
        return;
    int pivotIndex = randomizedPartition(array, low, high);
    randomizedQuickSort(array, low, pivotIndex - 1);
    randomizedQuickSort(array, pivotIndex + 1, high);
}

int main() {
    cout << "Enter the size of the array: " << endl;
    int size; cin >> size;

    cout << "Enter array elements: " << endl;
    vector<int> array(size);
    for(int i = 0; i < size; i++) 
        cin >> array[i];

    srand((unsigned)time(nullptr));
    if(size > 0) randomizedQuickSort(array, 0, size - 1);

    cout << endl << "Sorted array: " << endl;
    for(int i = 0; i < size; i++) 
        cout << array[i] << ' ';
    return 0;
}
