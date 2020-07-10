#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// dp - 只可买卖一次
// dp[i][0]表示第i天结束手里没有股票 dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i])	// 卖
// dp[i][1]表示第i天结束手里有一支股票 dp[i][1] = max(dp[i - 1][1], -prices[i])	// 买
// dp[i][1]表示第i天结束手里有一支股票 dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i])	// 买
// time: O(n)
// space: O(n)
class Solution1 {
  public:
    int maxProfit(vector<int> &prices) {
		if (prices.empty()) return 0;
		int len = prices.size();
		vector<vector<int>> dp(len, vector<int>(2, 0));
		dp[0][0] = 0; dp[0][1] = -prices[0];
		for (int i = 1; i < len; ++i) {
			dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
			dp[i][1] = max(dp[i - 1][1], -prices[i]);
			// dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
		}
		return dp[len - 1][0];
    }
};

// dp - 只可买卖一次
// dp[i][0]表示第i天结束手里没有股票 dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i])	// 卖
// dp[i][1]表示第i天结束手里有一支股票 dp[i][1] = max(dp[i - 1][1], -prices[i])	// 买
// dp[i][1]表示第i天结束手里有一支股票 dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i])	// 买
// time: O(n)
// space: O(1)
class Solution {
  public:
    int maxProfit(vector<int> &prices) {
		if (prices.empty()) return 0;
		int len = prices.size(), f0 = 0, f1 = -prices[0];
		for (int i = 1; i < len; ++i) 
			tie(f0, f1) = make_tuple(max(f0, f1 + prices[i]), max(f1, -prices[i]));	// (维持, 卖) (维持, 买)
		return f0;
    }
};

int main() {
    Solution s1;
    // vector<int> prices = {5, 8, 1, 6, 4, 3, 45, 9};
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    cout << s1.maxProfit(prices) << endl;
    return 0;
}