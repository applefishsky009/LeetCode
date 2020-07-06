#include <queue>
#include <stack>
#include <vector>
#include <iostream>
using namespace std;

// DFS超时
class Solution1 {
  public:
   int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
       if (obstacleGrid.size() == 0) return 0;
       int m = obstacleGrid.size(), n = obstacleGrid[0].size();
       return dfs(obstacleGrid, 0, 0, m, n);
   }
  private:
    int dfs(vector<vector<int>>& grid, int x, int y, int m, int n) {
        if (x >= m || y >= n || grid[x][y] == 1) return 0;
        if (x == m - 1 && y == n - 1) return 1;
        return dfs(grid, x + 1, y, m, n) + dfs(grid, x, y + 1, m, n);
    }
};

// DP
// dp[i][j] = 0 if f[i][j] = 1
// dp[i][j] = dp[i - 1][j] + dp[i][j - 1] if f[i][j] = 0
// time: O(mn)
// space: O(mn)
class Solution2 {
  public:
   int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        if (obstacleGrid.size() == 0) return 0;
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        dp[0][1] = 1;
        for (int i = 1; i < m + 1; i++)
            for (int j = 1; j < n + 1; j++)
                dp[i][j] = obstacleGrid[i - 1][j - 1] == 1 ? 0 : dp[i - 1][j] + dp[i][j - 1];
        return dp[m][n];
   }
};

// DP
// dp[i][j] = 0 if f[i][j] = 1
// dp[i][j] = dp[i - 1][j] + dp[i][j - 1] if f[i][j] = 0
// time: O(mn)
// space: O(n)
class Solution {
  public:
   int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        if (obstacleGrid.size() == 0) return 0;
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector<int> dp(n, 0);
        dp[0] = (obstacleGrid[0][0] == 0);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (obstacleGrid[i][j] == 1) {
                    dp[j] = 0;
                    continue;
                }
                if (j - 1 >= 0 && obstacleGrid[i][j - 1] == 0)
                    dp[j] += dp[j - 1];
            }
        }
        return dp.back();
   }
};

int main() {
    Solution s;
    // vector<vector<int>> grid = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};   // 2
    vector<vector<int>> grid = {{0, 0, 0}, {0, 1, 0}, {0, 1, 0}};   // 1
    // vector<vector<int>> grid = {{0, 0, 0}, {0, 1, 1}, {0, 1, 0}};   // 0
    cout << s.uniquePathsWithObstacles(grid) << endl;
    return 0;
}