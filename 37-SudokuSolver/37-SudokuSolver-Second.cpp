#include <vector>
#include <iostream>
#include <D:\Github\RylModule\vector.h>
using namespace std;

// dfs
// 注意这道题的关键在于填充一个数字之后依然是sudoku问题, 转化为其子问题解答
// time: O(9^9*9)	宽松上界,取决于输入数据
// space: O(9^9*9)	宽松上界,取决于输入数据
class Solution {
  public:
	void solveSudoku(vector<vector<char>> &board) {
		dfs(board);
		return;
	}
  private:
	const int n = 9;
	bool dfs(vector<vector<char>> &board) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (board[i][j] != '.') continue;
				for (int k = 0; k < n; ++k) {
					board[i][j] = k + '1';
					if (isValid(board, i, j) && dfs(board))
						return true;
					board[i][j] = '.';
				}
				return false;
			}
		}
		return true;	// 沒有需要填的空格, 子问题转化结束
	}
	bool isValid(vector<vector<char>> &board, int x, int y) {
		for (int i = 0; i < n; ++i)
			if (i != x && board[i][y] == board[x][y])
				return false;
		for (int j = 0; j < n; ++j)
			if (j != y && board[x][j] == board[x][y])
				return false;
		for (int i = 3 * (x / 3); i < 3 * (x / 3 + 1); ++i)
			for (int j = 3 * (y / 3); j < 3 * (y / 3 + 1); ++j) 
				if ((i != x || j != y) && board[i][j] == board[x][y])
					return false;
		return true;
	}
};

int main() {
    Solution s1;
    vector<vector<char>> board = {
				{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
				{'6', '.', '.', '1', '9', '5', '.', '.', '.'},
				{'.', '9', '8', '.', '.', '.', '.', '6', '.'},
				{'8', '.', '.', '.', '6', '.', '.', '.', '3'},
				{'4', '.', '.', '8', '.', '3', '.', '.', '1'},
				{'7', '.', '.', '.', '2', '.', '.', '.', '6'},
				{'.', '6', '.', '.', '.', '.', '2', '8', '.'},
				{'.', '.', '.', '4', '1', '9', '.', '.', '5'},
				{'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
    s1.solveSudoku(board);
    show2DVector(board);
    return 0;
}