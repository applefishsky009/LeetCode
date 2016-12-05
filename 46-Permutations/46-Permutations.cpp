#include <vector>
#include <iterator>
#include <algorithm>
#include <E:\RylModule\vector.h>
using namespace std;

//按位置dfs，出口，入口，回溯
class Solution
{
  public:
    vector<vector<int>> permute(vector<int> &nums)
    {
		vector<vector<int>> result;
		vector<int> path;
		dfs(nums, result, path, nums.size());
		return result;
    }

  private:
    void dfs(vector<int> nums, vector<vector<int>> &result, vector<int> path, const int n)
    {
		if (path.size() == n)
		{ //出口
			result.push_back(path);
			return;
		}
		for (int i = 0; i < nums.size(); ++i)
		{
			vector<int> temp = nums;
			vector<int>::iterator cur = temp.begin() + i;
			path.push_back(*cur);
			temp.erase(cur);		//往前走一步
			dfs(temp, result, path, n); //入口
			path.pop_back();		//回溯
		}
    }
};

//使用find函数避免了复制与迭代器，更快
class Solution1
{
  public:
    vector<vector<int>> permute(vector<int> &num)
    {
		sort(num.begin(), num.end());
		vector<vector<int>> result;
		vector<int> path; //中间结果
		dfs(num, path, result);
		return result;
    }

  private:
    void dfs(const vector<int> &num, vector<int> &path,
	     vector<vector<int>> &result)
    {
		if (path.size() == num.size())
		{ //收敛条件
			result.push_back(path);
			return;
		}
		//扩展状态
		for (auto i : num)
		{
			//查找是否在path中出现过
			auto pos = find(path.begin(), path.end(), i); //使用find函数
			if (pos == path.end())
			{
				path.push_back(i);
				dfs(num, path, result);
				path.pop_back();
			}
		}
    }
};

int main()
{
    Solution s1;
    vector<vector<int>> result;
    vector<int> nums = {1, 2, 3};
    result = s1.permute(nums);
	show2DVector(result);
    return 0;
}