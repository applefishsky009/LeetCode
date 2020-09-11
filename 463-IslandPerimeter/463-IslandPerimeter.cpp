#include <vector>
#include <iostream>
using namespace std;

// 遍历四邻域
// time: O(n*m)
// space: O(1)
class Solution0 {
  public:
    int islandPerimeter(vector<vector<int>> &grid) {
        int ans = 0;
        if (grid.empty()) return ans;
        int n = grid.size(), m = grid[0].size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 0) continue;
                int cur = 0;
                for (int k = 0; k < 4; ++k) {
                    int tx = i + dx[k], ty = j + dy[k];
                    if (tx < 0 || ty < 0 || tx >= n || ty >= m || grid[tx][ty] == 0)
                        ++cur;
                }
                ans += cur;
            }
        }
        return ans;
    }
  private:
    vector<int> dx = {1, -1, 0, 0};
    vector<int> dy = {0, 0, 1, -1};
};

// 减去重合边 是否重合只和左边和上边的点有关
// time: O(n*m)
// space: O(1)
class Solution1 {
  public:
    int islandPerimeter(vector<vector<int>> &grid) {
        int ans = 0;
        if (grid.empty()) return ans;
        int n = grid.size(), m = grid[0].size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 0) continue;
                ans += 4;
                if (i > 0 && grid[i - 1][j]) ans -= 2;
                if (j > 0 && grid[i][j - 1]) ans -= 2;
            }
        }
        return ans;
    }
};

// 西面和北面的长度 * 2即周长
// time: O(n*m)
// space: O(1)
class Solution {
  public:
    int islandPerimeter(vector<vector<int>> &grid) {
        int ans = 0;
        if (grid.empty()) return ans;
        int n = grid.size(), m = grid[0].size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j]) {
                    if (i == 0 || grid[i - 1][j] == 0) ++ans;
                    if (j == 0 || grid[i][j - 1] == 0) ++ans;
                }
            }
        }
        return ans * 2;
    }
};

int main() {
    Solution s;
    vector<vector<int>> grid = {
        {0, 1, 0, 0}, 
        {1, 1, 1, 0}, 
        {0, 1, 0, 0}, 
        {1, 1, 0, 0}};
    cout << s.islandPerimeter(grid) << endl;
    return 0;
}