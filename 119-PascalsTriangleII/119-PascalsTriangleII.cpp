#include <cmath>
#include <vector>
#include <iterator>
#include <E:\RylModule\vector.h>
using namespace std;

//计算二项式系数Cn0 -> Cnn，为了防止越界，后半部分需要拷贝O(n)?
//注意push_back()会使迭代器失效
//long long 长度不够，double精度可能缺失
class Solution
{
  public:
    vector<int> getRow(int rowIndex)
    {
		vector<int> result;
		result.push_back(1);
		double up = rowIndex; //分子
		double down = 1;      //分母
		for (int i = 1, temp = up; i <= rowIndex / 2; ++i, --temp)
		{
			result.push_back(round(up / down)); //double精度缺失,不能int()取整
			up = up * (temp - 1);
			down = down * (rowIndex + 1 - temp + 1);
		}
		if (rowIndex & 0x1)
		{				       //奇数，对称复制
			result.reserve(result.size() * 2); //防止迭代器失效
			auto p = result.end();
			for (; p != result.begin();)
			{
				--p;
				result.push_back(*p);
			}
		}
		else
		{ //偶数，非对称复制
			result.reserve(result.size() * 2 + 1);
			auto p = result.end();
			--p;
			for (; p != result.begin();)
			{
				--p;
				result.push_back(*p);
			}
		}
		return result;
    }
};

//滚动数组O(n^2)
class Solution1
{
  public:
    vector<int> getRow(int rowIndex)
    {
		vector<int> array;
		for (int i = 0; i <= rowIndex; i++)
		{
			for (int j = i - 1; j > 0; j--)
				array[j] = array[j - 1] + array[j];
			array.push_back(1);
		}
		return array;
    }
};

int main()
{
    Solution s1;
    int rowIndex = 6;
    vector<int> result = s1.getRow(rowIndex);
	show1DVector(result);
    return 0;
}