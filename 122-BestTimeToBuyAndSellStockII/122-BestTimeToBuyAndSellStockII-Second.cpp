#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// dp - 只可买卖一次
// dp[i][0]表示第i天结束手里没有股票 dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i])	// 卖
// dp[i][1]表示第i天结束手里有一支股票 dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i])	// 买
// time: O(n)
// space: O(1)
class Solution {
  public:
    int maxProfit(vector<int> &prices) {
        if (prices.empty()) return 0;
        int f0 = 0, f1 = -prices[0];
        for (int i = 0; i < prices.size(); i++)
            tie(f0, f1) = make_tuple(max(f0, f1 + prices[i]), max(f1, f0 - prices[i]));
        return f0;
    }
};

int main()
{
    Solution s1;
    // vector<int> prices = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    cout << s1.maxProfit(prices) << endl;
    return 0;
}