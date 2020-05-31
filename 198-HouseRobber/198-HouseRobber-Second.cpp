#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

// DP[i] = max(DP[i - 1], DP[i - 2] + nums[i])
class Solution1 {
  public:
    int rob(vector<int>& nums) {
        int i = 0, len = nums.size();
        vector<int> dp(len + 2, 0);
        for (i = 0; i < len; i++)
            dp[i + 2] = max(dp[i + 1], dp[i] + nums[i]);
        return dp[len + 1];
    }
};

// DP[i] = max(DP[i - 1], DP[i - 2] + nums[i])
class Solution {
  public:
    int rob(vector<int>& nums) {
        int i = 0, pre_2 = 0, pre = 0;
        for (i = 0; i < nums.size(); i++) {
            pre_2 = max(pre, pre_2 + nums[i]);
            swap(pre, pre_2);
        }
        return pre;
    }
};

int main() {
    Solution s;
    // vector<int> nums = {1, 2, 3, 1};
    // vector<int> nums = {1, 2, 3, 10};
    // vector<int> nums = {};
    // vector<int> nums = {2, 7, 9, 3, 1};
    vector<int> nums = {3, 2, 3, 10};
    cout << s.rob(nums) << endl;
    return 1;
}