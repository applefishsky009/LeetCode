#include <vector>
#include <iostream>
#include <algorithm>
#include <E:\RylModule\vector.h>
using namespace std;

//DFS，思路更像动态规划
class Solution
{
  public:
    vector<vector<int>> subsetsWithDup(vector<int> &s)
    {
		sort(s.begin(), s.end()); //排序
		vector<vector<int>> result;
		vector<int> path;
		dfs(s, s.begin(), path, result);
		return result;
    }

  private:
    void dfs(const vector<int> &s, vector<int>::iterator start, vector<int> &path, vector<vector<int>> &result)
    {
		result.push_back(path); //start指针(尾指针)之前的path
		for (vector<int>::iterator i = start; i < s.end(); i++)
		{
			if (i != start && *i == *(i - 1))
				continue; //DFS条件，新元素(i==start)必须DFS，旧元素判断是否有重复。
			//对i的DFS，DFS的元操作
			path.push_back(*i);
			dfs(s, i + 1, path, result); //DFS
			path.pop_back();		 //Backtracking
		}
    }
};

int main()
{
    vector<int> s = {1, 2, 2};
    Solution s1;
    vector<vector<int>> result = s1.subsetsWithDup(s);
	show2DVector(result);
    return 0;
}