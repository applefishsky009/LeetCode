#include <vector>
#include <iostream>
using namespace std;

// DP 
// sum(P) - sum(N) = target -> 2 * sum(P) = target + sum(P+N) -> sum(P) = (target + sum(PN)) / 2
// 填满容量为i的背包,有dp[i]种方法. 即找到和为(target + sum(PN)) / 2的非负整数集合个数
// 初始状态: dp[0] = 1, 表明填满容量为0的背包有且只有一种方法
// 转移方程: dp[i] = dp[i] + dp[i - num]
// time: O(n * target)
// space: O(target)
class Solution {
  public:
    int findTargetSumWays(vector<int> &nums, int S) {
        int sum = 0;
        for (auto &x : nums) sum += x;
        if ((S + sum) & 1 || S > sum) return 0;
        int target = (S + sum) / 2;
        vector<int> idp(target + 1, 0);
        idp[0] = 1;
        for (auto &num : nums)  // 依次填num
            for (int i = target; i >= num; --i) // i >= num 表示背包容量不能为负, 从大到小--是因为num不会相互影响，++会覆盖内存导致二次计数
                idp[i] += idp[i - num];     // 放入num更新背包容量对应的方法数
        return idp[target];
    }
};

int main() {
    Solution s;
    vector<int> nums = {1, 1, 1, 1, 1};
    cout << s.findTargetSumWays(nums, 3) << endl;
    return 0;
}