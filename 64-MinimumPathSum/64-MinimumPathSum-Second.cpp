#include <limits>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// dp
// time: O(n*m)
// space: O(n*m)
class Solution1 {
  public:
	int minPathSum(vector<vector<int>> &grid) {
		if (grid.empty()) return 0;
		int n = grid.size(), m = grid[0].size();
		vector<vector<int>> idp(n + 1, vector<int>(m + 1, INT_MAX));
		idp[0][1] = idp[1][0] = 0;
		for (int i = 1; i < n + 1; ++i)
			for (int j = 1; j < m + 1; ++j)
				idp[i][j] = min(idp[i - 1][j], idp[i][j - 1]) + grid[i - 1][j - 1];
		return idp[n][m];
	}
};

// dp - 滚动数组优化 - 初始化相对来说繁琐一些
// time: O(n*m)
// space: O(m)
class Solution {
  public:
	int minPathSum(vector<vector<int>> &grid) {
		if (grid.empty()) return 0;
		int n = grid.size(), m = grid[0].size();
		vector<int> idp(m + 1, INT_MAX);
		for (int i = 1; i < n + 1; ++i) {
			for (int j = 1; j < m + 1; ++j) {
				idp[0] = i == 1 ? 0 : INT_MAX;	// 滚动数组初始化
				idp[j] = min(idp[j - 1], idp[j]) + grid[i - 1][j - 1];
			}
		}
		return idp[m];
	}
};

int main() {
	Solution s;
	vector<vector<int>> grid0 = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};	// 7
	vector<vector<int>> grid1 = {{1, 2}, {1, 1}}; 	// 3
	cout << s.minPathSum(grid0) << endl;
	cout << s.minPathSum(grid1) << endl;
	return 0;
}