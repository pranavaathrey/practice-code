#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct SubArr {
    int maxSum;
    int lowerLimit;
    int higherLimit;

    bool operator<(const SubArr &other) const {
        return (maxSum < other.maxSum);
    }
};

SubArr findMaxCrossSum(vector<int> &array, int low, int mid, int high) {
    int leftSum = INT_MIN, leftMax = mid;
    int sum = 0;

    for(int i = mid; i >= low; i--) {
        sum += array[i];

        if(sum > leftSum) {
            leftSum = sum;
            leftMax = i;
        }
    }
    int rightSum = INT_MIN, rightMax = mid + 1;
    sum = 0;

    for(int i = mid + 1; i <= high; i++) {
        sum += array[i];

        if(sum > rightSum) {
            rightSum = sum;
            rightMax = i;
        }
    }
    return (SubArr){leftSum + rightSum, leftMax, rightMax};
}

SubArr findMaxSubSum(vector<int> &array, int low, int high) {
    if(low == high) 
        return (SubArr){array[low], low, high};
    
    int mid = low + (high - low) / 2;
    SubArr leftSum = findMaxSubSum(array, low, mid);
    SubArr rightSum = findMaxSubSum(array, mid + 1, high);
    SubArr crossSum = findMaxCrossSum(array, low, mid, high);

    return max({leftSum, rightSum, crossSum});
}

int main() {
    vector<int> array = {-2, -5, 6, -2, -3, 1, 5, -6};
    SubArr maxSubArr = findMaxSubSum(array, 0, array.size() - 1);
    cout << maxSubArr.maxSum << endl
         << maxSubArr.lowerLimit << endl
         << maxSubArr.higherLimit << endl;
}