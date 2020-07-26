#include <queue>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
using namespace std;

// dfs - 带记忆的递归, 和DP的唯一区别: 有无后效性
// time: O(n*m)
// space: O(n*m)
class Solution1 {
  public:
    int longestIncreasingPath(vector<vector<int>> &matrix) {
        if (matrix.empty()) return 0;
        int n = matrix.size(), m = matrix[0].size(), ans = 0;
        vector<vector<int>> state(n, vector<int>(m, 0));    // 每个结点的最短路径为1
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                ans = max(ans, dfs(matrix, state, i, j, n, m));
        return ans;
    }
  private:
    int dfs(vector<vector<int>> &matrix, vector<vector<int>> &state, int x, int y, int n, int m) {
        if (x < 0 || x >= n || y < 0 || y >= m)   // 越界, 最长路径为0
            return 0;
        if (state[x][y] != 0) return state[x][y];  // 搜索过, 返回当前最大路径
        if (x + 1 < n && matrix[x][y] < matrix[x + 1][y])
            state[x][y] = max(state[x][y], 1 + dfs(matrix, state, x + 1, y, n, m));
        if (y + 1 < m && matrix[x][y] < matrix[x][y + 1])
            state[x][y] = max(state[x][y], 1 + dfs(matrix, state, x, y + 1, n, m));
        if (x - 1 >= 0 && matrix[x][y] < matrix[x - 1][y])
            state[x][y] = max(state[x][y], 1 + dfs(matrix, state, x - 1, y, n, m));
        if (y - 1 >= 0 && matrix[x][y] < matrix[x][y - 1])
            state[x][y] = max(state[x][y], 1 + dfs(matrix, state, x, y - 1, n, m));
        if (state[x][y] == 0) 
            state[x][y] = 1;
        return state[x][y];
    }
};

// 拓扑排序 - 删除出度为0的结点 - bfs
// time: O(n*m)
// space: O(n*m)
class Solution {
  public:
    int longestIncreasingPath(vector<vector<int>> &matrix) {
        if (matrix.empty()) return 0;
        int n = matrix.size(), m = matrix[0].size(), ans = 0;
        static constexpr int coordinate[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        vector<vector<int>> out_degrees(n, vector<int>(m, 0));    // 每个结点的最短路径为1
        for (int i = 0; i < n; ++i)   // 计算出度
            for (int j = 0; j < m; ++j)
                for (int k = 0; k < 4; k++) {
                    int new_i = i + coordinate[k][0], new_j = j + coordinate[k][1];
                    if (new_i >= 0 && new_i < n && new_j >= 0 && new_j < m && matrix[i][j] < matrix[new_i][new_j])
                        ++out_degrees[i][j];    // 出度
                }
        queue<pair<int, int>> iq;
        for (int i = 0; i < n; ++i) // 初始化 - 从出度为0的即邻域极大值开始删除
            for (int j = 0; j < m; ++j)
                if (out_degrees[i][j] == 0)
                    iq.push(pair<int, int>(i, j));
                    // iq.push({i, j});
                    // iq.push(make_pair(i, j));
        while (!iq.empty()) {   // bfs
            ++ans;  // step
            int size = iq.size();
            for (int i = 0; i < size; ++i) {
                auto cell = iq.front(); iq.pop();
                int row = cell.first, col = cell.second;
                for (int k = 0; k < 4; ++k) {   // 更新
                    int new_i = row + coordinate[k][0], new_j = col + coordinate[k][1];
                    if (new_i >= 0 && new_i < n && new_j >= 0 && new_j < m && matrix[new_i][new_j] < matrix[row][col])  // 修改邻域出度
                        if (--out_degrees[new_i][new_j] == 0)   // 出度为0, 准备删除
                            // iq.push({new_i, new_j});
                            // iq.push(make_pair(new_i, new_j));
                            iq.push(pair<int, int>(new_i, new_j));
                }
            }
        }
        return ans;
    }
};

int main() {
    Solution s;
    vector<vector<int>> matrix0 = {{9, 9, 4}, {6, 6, 8}, {2, 1, 1}};
    vector<vector<int>> matrix1 = {{3, 4, 5}, {3, 2, 6}, {2, 2, 1}};
    vector<vector<int>> matrix2 = {{1, 2}};
    cout << s.longestIncreasingPath(matrix0) << endl;
    cout << s.longestIncreasingPath(matrix1) << endl;
    cout << s.longestIncreasingPath(matrix2) << endl;
    return 0;
}
