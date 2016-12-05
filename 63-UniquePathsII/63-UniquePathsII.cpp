#include <vector>
#include <iostream>
using namespace std;

class Solution
{
  public:
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
    {
		int m = obstacleGrid.size();
		if (m < 1)
			return 0;
		int n = obstacleGrid[0].size();
		//从终点走向起点的边界条件(用0控制边界)要比从起点走向终点(传入m,n控制边界)简单
		//但是自顶向下如果没有备忘会超时
		f = vector<vector<int>>(m, vector<int>(n, 0));
		return dfs(obstacleGrid, m - 1, n - 1);
    }

  private:
    vector<vector<int>> f;
    int dfs(vector<vector<int>> &obstacleGrid, int x, int y)
    {
		if (x < 0 || y < 0 || obstacleGrid[x][y] == 1)
			return 0;
		if (x == 0 && y == 0 && obstacleGrid[x][y] == 0)
			return 1;
		if (!f[x][y])
			f[x][y] = dfs(obstacleGrid, x - 1, y) + dfs(obstacleGrid, x, y - 1);
		return f[x][y];
    }
};

int main()
{
    vector<vector<int>> obstacleGrid = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    Solution s1;
    cout << s1.uniquePathsWithObstacles(obstacleGrid) << endl;
    return 0;
}
