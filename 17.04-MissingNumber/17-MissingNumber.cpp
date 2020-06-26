#include <vector>
#include <iostream>
using namespace std;

// 高斯求和
class Solution0 {
  public:
    int missingNumber(vector<int>& nums) {
        int len = nums.size();
        int sum = ((len * (len + 1)) >> 1);
        for (auto &x: nums)
            sum -= x;
        return sum;
    }
};

// 异或
class Solution {
  public:
    int missingNumber(vector<int>& nums) {
        int ans = 0, i = 0;
        for (i = 0; i < nums.size(); i++)
            ans ^= ((i + 1) ^ nums[i]);
        return ans;
    }
};

int main() {
    Solution s;
    vector<int> nums0 = {3, 0, 1};
    vector<int> nums1 = {9, 6, 4, 2, 3, 5, 7, 0, 1};
    cout << s.missingNumber(nums0) << endl;
    cout << s.missingNumber(nums1) << endl;
    return 1;
}