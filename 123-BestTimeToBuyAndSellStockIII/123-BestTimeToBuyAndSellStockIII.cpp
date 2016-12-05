#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

//DP,每个节点四种可能
class Solution
{
  public:
    int maxProfit(vector<int> &prices)
    {
		int release2 = 0;
		int hold2 = INT_MIN;
		int release1 = 0;
		int hold1 = INT_MIN;
		for (int i = 0; i < prices.size(); ++i)
		{
			release2 = max(release2, hold2 + prices[i]); //二次卖出，所得利润最高
			hold2 = max(hold2, release1 - prices[i]);    //二次持有，买入价格最低
			release1 = max(release1, hold1 + prices[i]); //首次卖出，所得利润最高
			hold1 = max(hold1, -prices[i]);		 //首次持有，买入价格最低
		}
		return release2;
    }
};

//设状态f(i)表示区间[0,i],状态g(i)表示状态[i+1,n-1]的最大利润，则最终答案为max(f(i)+g(i)),
class Solution1
{
  public:
    int maxProfit(vector<int> &prices)
    {
		if (prices.size() < 2)
			return 0;
		const int n = prices.size();
		vector<int> f(n, 0);
		vector<int> g(n, 0);

		int valley = prices[0];
		for (int i = 1; i < n; ++i)
		{
			valley = min(valley, prices[i]);
			f[i] = max(f[i - 1], prices[i] - valley); //更新利润
		}

		int peak = prices[n - 1];
		for (int j = n - 2; j >= 0; --j)
		{
			peak = max(peak, prices[j]);
			g[j] = max(g[j + 1], peak - prices[j]); //更新利润
		}

		int maxProfit = 0;
		for (int k = 0; k < n; ++k)
			maxProfit = max(maxProfit, f[k] + g[k]);
		return maxProfit;
    }
};

int main()
{
    Solution1 s1;
    vector<int> prices = {2, 5, 4, 8, 9, 3};
    cout << s1.maxProfit(prices) << endl;
    return 0;
}