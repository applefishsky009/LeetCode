#include <vector>
#include <algorithm>
#include <E:\RylModule\vector.h>
using namespace std;

class Solution
{
  public:
    vector<vector<int>> combinationSum(vector<int> &candidates, const int target)
    {
		sort(candidates.begin(), candidates.end()); //这要看输入是否有序
		vector<vector<int>> result;
		vector<int> path;
		dfs(candidates, target, result, path, 0, 0); //第一个0是当前path和，第二个0是当前path遍历到candidates的哪一步，防止223,232,322，类似的结果
		return result;
    }

  private:
    void dfs(vector<int> &candidates, const int target, vector<vector<int>> &result, vector<int> path, int sum, int step)
    {
		//if (sum > target) return;
		if (sum == target)
		{
			result.push_back(path);
			return;
		}
		int temp = sum; //保存当前和
		for (int i = step; i < candidates.size(); ++i)
		{
			sum = temp;
			if (target - sum < candidates[i])
				return; //从下边方法提炼而来，极大提升性能，替换17行
			path.push_back(candidates[i]);
			sum += candidates[i];
			dfs(candidates, target, result, path, sum, i);
			path.pop_back();
		}
    }
};

//少传一个参数，将target和sum合并，优化
//提前减枝
class Solution1
{
  public:
    vector<vector<int>> combinationSum(vector<int> &nums, int target)
    {
		sort(nums.begin(), nums.end());
		vector<vector<int>> result;
		vector<int> path;
		dfs(nums, path, result, target, 0);
		return result;
    }

  private:
    void dfs(vector<int> &nums, vector<int> &path, vector<vector<int>> &result,
	     int gap, int start)
    {
		if (gap == 0)
		{
			result.push_back(path);
			return;
		}
		for (size_t i = start; i < nums.size(); i++)
		{
			if (gap < nums[i])
				return; //提前减枝
			path.push_back(nums[i]);
			dfs(nums, path, result, gap - nums[i], i);
			path.pop_back();
		}
    }
};

int main()
{
    vector<int> candidates = {2, 3, 6, 7};
    int target = 7;
    Solution s1;
    vector<vector<int>> result = s1.combinationSum(candidates, target);
    show2DVector(result);
    return 0;
}