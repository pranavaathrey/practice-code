#include <iostream>
#include <climits>

using namespace std;

struct SumInfo {
    int maxSum;
    int lowerLimit;
    int higherLimit;
};

SumInfo findMaxSubSum(int array[], int low, int high) {
    if(low == high)
        return (SumInfo){array[low], low, high};
    
    int mid = low + (high - low) / 2;
    SumInfo leftSumInfo  = findMaxSubSum(array, low, mid);
    SumInfo rightSumInfo = findMaxSubSum(array, mid + 1, high);
    SumInfo crossSumInfo = findMaxCrossSum(array, low, mid, high);

    if(crossSumInfo.maxSum > leftSumInfo.maxSum 
    && crossSumInfo.maxSum > rightSumInfo.maxSum)
        return crossSumInfo;
    else if(leftSumInfo.maxSum > rightSumInfo.maxSum)
        return leftSumInfo;
    else    
        return rightSumInfo;
}

SumInfo findMaxCrossSum(int array[], int low, int mid, int high) {
    int leftSum = INT_MIN, maxLower = mid;
    int sum = 0;

    for(int i = mid; i >= low; i--) {
        sum += array[i];

        if(sum > leftSum) {
            leftSum = sum;
            maxLower = i;
        }
    }
    int rightSum = INT_MIN, maxHigher = mid + 1;
    sum = 0;

    for(int i = mid + 1; i <= high; i++) {
        sum += array[i];

        if(sum > rightSum) {
            rightSum = sum;
            maxHigher = i;
        }
    }
    return (SumInfo){leftSum + rightSum, maxLower, maxHigher};
}

int main() {
    int array[] = {-2, -5, 6, -2, -3, 1, 5, -6};
    int n = sizeof(array) / sizeof(int);

    SumInfo maxSumInfo = findMaxSubSum(array, 0, n - 1);
    cout << "The array: ";
    for(int i = 0; i < n; i++)
        cout << array[i] << " ";

    cout << "\n\nThe maximum subarray sum is: " << maxSumInfo.maxSum;
    cout << "\nwith the elements: ";
    for(int i =  maxSumInfo.lowerLimit; 
            i <= maxSumInfo.higherLimit; i++) {
        cout << array[i] << " ";
    }
    return 0;
}