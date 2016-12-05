#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//典型的二维路径问题
class Solution
{
  public:
    int minPathSum(vector<vector<int>> &grid)
    {
		if (grid.size() == 0)
			return 0;
		const int m = grid.size();
		const int n = grid[0].size();
		vector<vector<int>> step(m, vector<int>(n, 0));
		for (int i = 0, sumX = 0; i < n; ++i)
		{
			sumX += grid[0][i];
			step[0][i] = sumX;
		} //列循环用n
		for (int j = 0, sumY = 0; j < m; ++j)
		{
			sumY += grid[j][0];
			step[j][0] = sumY;
		} //行循环用m
		for (int i = 1; i < m; ++i)
			for (int j = 1; j < n; ++j)
				step[i][j] = min(step[i - 1][j], step[i][j - 1]) + grid[i][j];
		return step[m - 1][n - 1];
    }
};

int main()
{
    Solution s1;
    vector<vector<int>> grid{{1, 2, 3}, {4, 5, 6}};
    cout << s1.minPathSum(grid) << endl;
    return 0;
}