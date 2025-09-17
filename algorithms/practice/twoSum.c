#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int i, j;
    for(i = 0; i < numsSize; i++) 
        for(j = i + 1; j < numsSize; j++) 
            if(nums[i] + nums[j] == target) {
                int* twoSum = (int*)malloc(2 * sizeof(int));
                twoSum[0] = i;
                twoSum[1] = j;
                return twoSum;
            }
    return NULL;
}

int main() {
    int nums[] = {3, 2, 4}, returnSize;
    int numsSize = 3, target = 6;

    int* two_Sum = twoSum(nums, numsSize, 
            target, &returnSize);
    printf("[%d, %d]", two_Sum[0], two_Sum[1]);
    free(two_Sum);
}