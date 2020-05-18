#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;

// nums[i] > 0时，如果nums[i]存在和dp_max_i重叠的部分dp_tmp数组使得dp_tmp * nums[i] > dp_max_i * nums[i]，那么dp_max_i必然不是最优解。
// 子数组和同理且不分正负
class Solution
{
  public:
    int maxProduct(vector<int> &nums) { // dp_max_i的含义是以i个元素结尾的子数组
        int i = 0, dp_max_i = nums[0], dp_min_i = nums[0], result = nums[0];
        int dp_max_pre_i = 0, dp_min_pre_i = 0;
        for (i = 1; i < nums.size(); i++) {
            dp_max_pre_i = dp_max_i; dp_min_pre_i = dp_min_i;
            dp_max_i = max(dp_max_pre_i * nums[i], max(dp_min_pre_i * nums[i], nums[i])); // 如果dp_max_pre_i < 0，pre_x必然是第一个出现的负数。否则如果dp_max_pre_i至少为pre_x且大于0。
            dp_min_i = min(dp_min_pre_i * nums[i], min(dp_max_pre_i * nums[i], nums[i])); // x小于0
            result = max(dp_max_i, result);
        }
        return result;
    }
};

int main()
{
    // vector<int> nums = {-2, 3, 4};
    vector<int> nums = {-4, -3, -2};
    // vector<int> nums = {-2};
    Solution s1;
    cout << s1.maxProduct(nums) << endl;
    return 0;
}