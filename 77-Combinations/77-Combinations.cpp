#include <vector>
#include <iostream>
#include <E:\RylModule\vector.h>
using namespace std;

class Solution
{
  public:
    vector<vector<int>> combine(int n, int k)
    {
		vector<vector<int>> result;
		if (n < k)
			return result;
		vector<int> path;
		dfs(n, k, 1, 0, path, result);
		return result;
    }

  private:
    // start 标识当前步, cur path中的元素数量
    void dfs(int n, int k, int start, int cur,
	     vector<int> &path, vector<vector<int>> &result)
    {
		if (cur == k)
		{
			result.push_back(path);
			return;
		}
		for (int i = start; i <= n; ++i)
		{
			path.push_back(i);
			dfs(n, k, i + 1, cur + 1, path, result);
			path.pop_back();
		}
    }
};

int main()
{
    Solution s1;
    int n = 4;
    int k = 2;
    vector<vector<int>> result = s1.combine(n, k);
	show2DVector(result);
    return 0;
}