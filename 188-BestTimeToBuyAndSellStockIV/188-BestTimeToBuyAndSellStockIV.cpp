#include <queue>
#include <stack>
#include <vector>
#include <iostream>
using namespace std;

//待转换：考虑(1,5)->(2,4),利润不仅由下一次决定，还可能与下下次相关，->(3,6)就需要两次利润转换，因此加入转换队列；若->(0,6)就在待转化栈中计算了两次利润；
//需要转换:考虑(1,5)->(2,6),利润转换5+3=4+4,小利润3，大利润5对应(1,6)还要看下一步
//利润:考虑(1,5)->(0,3),利润是4,(0,3)由下次决定
//利润:考虑(1,5)->(0,6),利润是4,(0,6)由下次决定

class Solution
{
  public:
    int maxProfit(int k, vector<int> &prices)
    {
		int n = (int)prices.size(), ret = 0, v, p = 0;
		priority_queue<int> profits;    //优先级队列存放利润
		stack<pair<int, int>> vp_pairs; //存放(v,p)对，每一个时刻只有一个(v,p)对，因此两个while只能执行一个
		while (p < n)
		{
			// find next valley/peak pair
			for (v = p; v < n - 1 && prices[v] >= prices[v + 1]; v++)
				; //找局部最小值v
			for (p = v + 1; p < n && prices[p] >= prices[p - 1]; p++)
				; //找局部最大值p-1
			//下面根据前一次的(v,p)对更新(v,p)对，是否需要利润转换。本次的vp对利润更新在下一次
			// save profit of 1 transaction at last v/p pair, if current v is lower than last v
			while (!vp_pairs.empty() && prices[v] < prices[vp_pairs.top().first])
			{											//当前局部最小值小于上一个局部最小值,不转换
				profits.push(prices[vp_pairs.top().second - 1] - prices[vp_pairs.top().first]); //上一个(v,p)对的利润
				vp_pairs.pop();
			}
			// save profit difference between 1 transaction (last v and current p) and 2 transactions (last v/p + current v/p),
			// if current v is higher than last v and current p is higher than last p
			while (!vp_pairs.empty() && prices[p - 1] >= prices[vp_pairs.top().second - 1])
			{								     //当前局部最大值不小于上一个局部最大值，利润转换
				profits.push(prices[vp_pairs.top().second - 1] - prices[v]); //转换后的小利润
				v = vp_pairs.top().first;				     //更新(v,p)对
				vp_pairs.pop();
			}
			vp_pairs.push(pair<int, int>(v, p)); //新的(v,p)对
		}
		// save profits of the rest v/p pairs
		while (!vp_pairs.empty())
		{ //处理剩下的(v,p)对
			profits.push(prices[vp_pairs.top().second - 1] - prices[vp_pairs.top().first]);
			vp_pairs.pop();
		}
		// sum up first k highest profits
		for (int i = 0; i < k && !profits.empty(); i++)
		{ //根据优先级队列特性计算前k个利润
			ret += profits.top();
			profits.pop();
		}
		return ret;
    }
};

int main()
{
    vector<int> prices = {1, 3, 2, 5, 2, 3};
    int k = 2;
    Solution s1;
    cout << s1.maxProfit(k, prices) << endl;
    return 0;
}