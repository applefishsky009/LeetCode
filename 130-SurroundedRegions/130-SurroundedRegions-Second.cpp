#include <queue>
#include <vector>
#include <iostream>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// dfs必须无后效性, 不能对每个点进行dfs然后判断他是否到边界并更新之前遍历到的每个点, 有后效性考虑用UF来解
// time: O(n * m)
// space: O(n * m)
class Solution0 {
  public:
	void solve(vector<vector<char>> &board) {
		int n = board.size();
		if (n == 0) return;
		int m = board[0].size();
		for (int i = 0; i < n; ++i) {
			dfs(board, i, 0, n, m);
			dfs(board, i, m - 1, n, m);
		}
		for (int j = 1; j < m - 1; ++j) {
			dfs(board, 0, j, n, m);
			dfs(board, n - 1, j, n, m);
		}
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				board[i][j] = board[i][j] == 'A' ? 'O' : 'X';
	}
  private:
	void dfs(vector<vector<char>> &board, int x, int y, const int n, const int m) {
		if (x >= n || x < 0 || y < 0 || y >= m || board[x][y] != 'O') return;
		board[x][y] = 'A';
		dfs(board, x + 1, y, n, m);
		dfs(board, x - 1, y, n, m);
		dfs(board, x, y + 1, n, m);
		dfs(board, x, y - 1, n, m);
	}
};

// bfs
// time: O(n * m)
// space: O(n * m)
class Solution {
  public:
	void solve(vector<vector<char>> &board) {
		int n = board.size();
		if (n == 0) return;
		int m = board[0].size();
		queue<pair<int, int>> ique;
		for (int i = 0; i < n; ++i) {
			if (board[i][0] == 'O') ique.emplace(i, 0);
			if (board[i][m - 1] == 'O') ique.emplace(i, m - 1);
		}
		for (int j = 1; j < m - 1; ++j) {
			if (board[0][j] == 'O') ique.emplace(0, j);
			if (board[n - 1][j] == 'O') ique.emplace(n - 1, j);
		}
		while (!ique.empty()) {
			int x = ique.front().first, y = ique.front().second;
			ique.pop();
			board[x][y] = 'A';
			for (int k = 0; k < 4; ++k) {
				int mx = x + dx[k], my = y + dy[k];
				if (mx < 0 || mx >= n || my < 0 || my >= m || board[mx][my] != 'O') continue;
				ique.emplace(mx, my);
			}
		}
		for (int i = 0; i < n; ++i) 
			for (int j = 0; j < m; ++j)
				board[i][j] = board[i][j] == 'A' ? 'O' : 'X';
	}
  private:
	const int dx[4] = {1, -1, 0, 0};
	const int dy[4] = {0, 0, 1, -1};
};

int main() {
	Solution s;
	// vector<vector<char>> board = {{'X', 'X', 'X', 'X'}, {'X', 'O', 'O', 'X'}, {'X', 'X', 'O', 'X'}, {'X', 'O', 'X', 'X'}};
	// vector<vector<char>> board = {{'X', 'X', 'X', 'X'}, {'X', 'O', 'O', 'X'}, {'X', 'O', 'O', 'X'}, {'X', 'O', 'O', 'X'}};
	vector<vector<char>> board = {{'X', 'O', 'O', 'X'}, {'X', 'O', 'X', 'X'}, {'X', 'X', 'X', 'X'}, {'X', 'O', 'O', 'X'}};
	show2DVector(board);
	s.solve(board);
	show2DVector(board);
	return 0;
}
