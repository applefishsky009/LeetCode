#include <vector>
#include <algorithm>
#include <E:\RylModule\vector.h>
using namespace std;

//注意尽量使用一次dfs，不要调用第二次，严格按照层dfs
class Solution
{
  public:
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
    {
		vector<vector<int>> result;
		sort(candidates.begin(), candidates.end());
		vector<int> path;
		dfs(result, path, candidates, target, 0);
		return result;
    }

  private:
    void dfs(vector<vector<int>> &result, vector<int> path, vector<int> candidates, int gap, int start)
    {
		if (gap == 0)
		{ //gap和target合并
			result.push_back(path);
			return;
		}
		int previous = -1;
		for (size_t i = start; i < candidates.size(); i++)
		{
			if (previous == candidates[i])
				continue; //确保本层dfs只出现一次
			if (gap < candidates[i])
				return;		      //提前剪枝
			previous = candidates[i]; //设置flag

			path.push_back(candidates[i]);
			dfs(result, path, candidates, gap - candidates[i], i + 1);
			path.pop_back();
		}
    }
};

int main()
{
    Solution s1;
    vector<int> candidates{10, 1, 2, 7, 6, 1, 5};
    int target = 8;
    vector<vector<int>> result = s1.combinationSum2(candidates, target);
    show2DVector(result);
    return 0;
}