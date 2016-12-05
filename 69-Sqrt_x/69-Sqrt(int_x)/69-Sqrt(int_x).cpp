#include <climits>
#include <iostream>
using namespace std;

//牛顿迭代法优于二分查找法
//9					2 ：2
//100				4 ：5
//1000				7 ：9
//36548963			15：26
//2147395600		19：30
//INT_MAX			19: 31
//这是因为牛顿迭代法只从右侧逼近，而二分查找从右侧左侧同时逼近。

static int lable = 0;

//二分
class Solution
{
  public:
    int mySqrt(int x)
    {
		if (x < 2)
			return x;
		return biSearch(1, x / 2, x);
    }

  private:
    int biSearch(int low, int high, int x)
    {
		lable++;
		int mid = low + (high - low) / 2;
		if (low <= high)
		{
			if (x / mid < mid)
				return biSearch(low, mid - 1, x); //注意防止溢出
			if (x / mid > mid)
				return biSearch(mid + 1, high, x); //一定不从这里收敛
			return mid;
		}
		return mid - 1; //注意递归出口，某个所求的mid一定满足x/mid>=mid,如果等于，在19行直接返回mid，
    }			//如果mid即为所求，且x/mid>mid(如12-15),递归时一定会二分查找(mid+1,high),收敛在mid+1
};

//牛顿迭代法
class Solution1
{
  public:
    int mySqrt(int x)
	{
		if (x < 2)
			return x;
		int xk = 1;
		do //使用do while保证xk=1进入循环
		{
			lable++;
			xk = (double)xk / 2 + (double)x / xk / 2; //不能是xk = (xk+n/xk)/2防止越界；
		} while (x / xk < xk);			      //但是这么操作需要强制转化为double防止损耗，
			return xk;				      //例如对2147395600，最后一步是xk=46341的迭代，如果不强制类型转化会迭代为46339
    }
};

int main()
{
    Solution s1;
    int x = INT_MAX;
    cout << s1.mySqrt(x) << endl;
    cout << lable << endl;
    return 0;
}