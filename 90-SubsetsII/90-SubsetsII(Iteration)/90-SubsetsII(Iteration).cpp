#include <set>
#include <vector>
#include <iterator> //use back_inserter
#include <algorithm>
#include <E:\RylModule\vector.h>
using namespace std;

//增量构造法，和动态规划思想类似
class Solution
{
  public:
    vector<vector<int>> subsetsWithDup(vector<int> &S)
    {
		sort(S.begin(), S.end()); //排序
		vector<vector<int>> result(1);
		size_t previous_size = 0;
		for (size_t i = 0; i < S.size(); ++i)
		{				       //每来一个新元素
			const size_t size = result.size(); //存当前结果长度
			for (size_t j = 0; j < size; ++j)
			{
				//第一个 || 新元素(从0到size-1全都入一遍) ||
				//旧元素(上一个元素(旧或新)肯定入过size-1，也就是现在的presize-1,现在入presize到size-1(上次元素的简单重复))
				if (i == 0 || S[i] != S[i - 1] || j >= previous_size)
				{
					result.push_back(result[j]);
					result.back().push_back(S[i]);
				}
			}
			previous_size = size; //上一个元素插入完毕时容器长度
		}
		return result;
    }
};

//二进制法，用set存储，set转vector
class Solution1
{
  public:
    vector<vector<int>> subsetsWithDup(vector<int> &nums)
    {
		sort(nums.begin(), nums.end());
		set<vector<int>> result; //unique key
		const int size_N = nums.size();

		vector<int> temp;
		for (int i = 0; i < 1 << size_N; ++i)
		{				     //二进制对应的向量
			for (int j = 0; j < size_N; ++j) //取j位置
				if (i & 1 << j)
					temp.push_back(nums[j]);
			result.insert(temp);
			temp.clear();
		}

		vector<vector<int>> real_result;
		copy(result.begin(), result.end(), back_inserter(real_result)); //copy
		//vector<vector<int>> real_result(result.begin(), result.end());   //神奇的构造函数
		return real_result;
    }
};

int main()
{
    vector<int> nums = {1, 2, 2};
    Solution s1;
    vector<vector<int>> result = s1.subsetsWithDup(nums);
	show2DVector(result);
    return 0;
}