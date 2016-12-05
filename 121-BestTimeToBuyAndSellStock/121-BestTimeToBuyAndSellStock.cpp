#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//注意prices[0]是第一天价钱
//第一种n*log(n)，两层循环，每次得到一天能取得的最大利润
//下边O(n),
class Solution
{
  public:
    int maxProfit(vector<int> &prices)
    {
		if (prices.size() < 2)
			return 0;
		int cur_min = prices[0]; //记录每一步之前的最小值
		int profit = 0;		 //记录这一步与前面最小值最大差价，也就是利润
		for (int i = 1; i < prices.size(); ++i)
		{
			profit = max(profit, prices[i] - cur_min); //利润，cur_min暂未更新，保证卖出在买入之后
			cur_min = min(cur_min, prices[i]);
		}
		return profit;
    }
};

int main()
{
    Solution s1;
    vector<int> prices = {5, 8, 1, 6, 4, 3, 45, 9};
    cout << s1.maxProfit(prices) << endl;
    return 0;
}