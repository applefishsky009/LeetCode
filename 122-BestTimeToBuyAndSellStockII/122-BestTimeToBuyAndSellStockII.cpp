#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//累计正的相邻的diff差，思路类似于最大m子段和
//局部利润一定是整体利润的唯一部分(因为只能持有一份股票)，因此分割为最小利润单元
class Solution
{
  public:
    int maxProfit(vector<int> &prices)
    {
		int sumProfit = 0;
		for (int i = 1; i < prices.size(); ++i)
		{
			int diff = prices[i] - prices[i - 1];
			if (diff > 0)
				sumProfit += diff; //有利润则累积
		}
		return sumProfit;
    }
};

int main()
{
    Solution s1;
    vector<int> prices = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << s1.maxProfit(prices) << endl;
    return 0;
}