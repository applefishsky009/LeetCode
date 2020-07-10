#include <cmath>
#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// dp[i] 表示第i天 结束后 的累计最大收益, 三种不同状态:
// 持有一只股票, 累计最大收益为dp[i][0], 状态转移方程为 dp[i][0] = max(dp[i - 1][0], dp[i - 1][2] - prices[i]) // i - 1天就持有||i天买入(i - 1天不持有且不处于冷冻期)
// 不持有任何一只股票且处于冷冻期, 累计最大收益为dp[i][1] dp[i][1] = dp[i - 1][0] + prices[i]   // i当天卖出, i - 1天持有
// 不持有任何一只股票且不处于冷冻期, 累计最大收益为dp[i][2] dp[i][2] = max(dp[i - 1][1], dp[i - 1][2])     // i - 1天不持有任何股票, 冷冻期 || 非冷冻期
// 三种情况总的来说, 第n天结束后(下标n - 1), maxProfit = max(dp[n - 1][0], dp[n - 1][1], dp[n - 1][2]) = max(dp[n - 1][1], dp[n - 1][2])
// 边界条件 dp[0][0] = -prices[0], dp[0][1] = 0, dp[0][2] = 0;
// time: O(n)
// space: O(n)
class Solution1 {
  public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
        int len = prices.size();
        vector<vector<int>> dp(len, vector<int>(3, 0));
        dp[0][0] = -prices[0];
        for (int i = 1; i < len; i++) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][2] - prices[i]); // 持有一只股票
            dp[i][1] = dp[i - 1][0] + prices[i]; // 不持有任何一只股票且处于冷冻期
            dp[i][2] = max(dp[i - 1][1], dp[i - 1][2]); // 不持有任何一只股票且不处于冷冻期
        }
        return max(dp[len - 1][1], dp[len - 1][2]);
    }
};

// dp[i] 表示第i天 结束后 的累计最大收益, 三种不同状态:
// 持有一只股票, 累计最大收益为dp[i][0], 状态转移方程为 dp[i][0] = max(dp[i - 1][0], dp[i - 1][2] - prices[i]) // i - 1天就持有||i天买入(i - 1天不持有且不处于冷冻期)
// 不持有任何一只股票且处于冷冻期, 累计最大收益为dp[i][1] dp[i][1] = dp[i - 1][0] + prices[i]   // i当天卖出, i - 1天持有
// 不持有任何一只股票且不处于冷冻期, 累计最大收益为dp[i][2] dp[i][2] = max(dp[i - 1][1], dp[i - 1][2])     // i - 1天不持有任何股票, 冷冻期 || 非冷冻期
// 三种情况总的来说, 第n天结束后(下标n - 1), maxProfit = max(dp[n - 1][0], dp[n - 1][1], dp[n - 1][2]) = max(dp[n - 1][1], dp[n - 1][2])
// 边界条件 dp[0][0] = -prices[0], dp[0][1] = 0, dp[0][2] = 0;
// time: O(n)
// space: O(1)
class Solution2 {
  public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
        int len = prices.size(), f0 = -prices[0], f1 = 0, f2 = 0;
        for (int i = 1; i < len; i++) {
            int newf0 = max(f0, f2 - prices[i]);
            int newf1 = f0 + prices[i];
            int newf2 = max(f2, f1);
            f0 = newf0;
            f1 = newf1;
            f2 = newf2;
        }
        return max(f1, f2);
    }
};

// dp[i] 表示第i天 结束后 的累计最大收益, 三种不同状态:
// 持有一只股票, 累计最大收益为dp[i][0], 状态转移方程为 dp[i][0] = max(dp[i - 1][0], dp[i - 1][2] - prices[i]) // i - 1天就持有||i天买入(i - 1天不持有且不处于冷冻期)
// 不持有任何一只股票且处于冷冻期, 累计最大收益为dp[i][1] dp[i][1] = dp[i - 1][0] + prices[i]   // i当天卖出, i - 1天持有
// 不持有任何一只股票且不处于冷冻期, 累计最大收益为dp[i][2] dp[i][2] = max(dp[i - 1][1], dp[i - 1][2])     // i - 1天不持有任何股票, 冷冻期 || 非冷冻期
// 三种情况总的来说, 第n天结束后(下标n - 1), maxProfit = max(dp[n - 1][0], dp[n - 1][1], dp[n - 1][2]) = max(dp[n - 1][1], dp[n - 1][2])
// 边界条件 dp[0][0] = -prices[0], dp[0][1] = 0, dp[0][2] = 0;
// time: O(n)
// space: O(1)
class Solution {
  public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
        int len = prices.size(), f0 = -prices[0], f1 = 0, f2 = 0;
        for (int i = 1; i < len; i++)
            tie(f0, f1, f2) = make_tuple(max(f0, f2 - prices[i]), f0 + prices[i], max(f2, f1)); // 买, 卖, 状态更新
        return max(f1, f2);
    }
};

int main() {
    Solution s;
    // vector<int> prices = {1, 2, 3, 0, 2};
    vector<int> prices = {1, 2, 4, 0, 3};
    cout << s.maxProfit(prices) << endl;
    return 0;
}