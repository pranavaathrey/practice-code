#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size(), x = 0;
        for(int i = 1; i < n; i++) 
            x ^= i;

        for(int i = 0; i < n; i++) 
            x ^= nums[i];
        return x;
    }
    int findMulDuplicate(vector<int>& nums) {
        int slow = nums[0];
        int fast = nums[nums[0]];

        while(slow != fast) {
            slow = nums[slow]; 
            fast = nums[nums[fast]];
        }
        slow = 0;
        while(slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};

int main() {
    vector<int> nums = {1, 2, 3, 4, 4, 5, 6};
    Solution s;
    cout << s.findMulDuplicate(nums);
    return 0;
}