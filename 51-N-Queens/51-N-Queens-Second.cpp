#include <vector>
#include <string>
#include <unordered_set>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// 基于集合的回溯
// 从左上到右下的斜线: 行下标和列下标之差相等 | 从右上到左下的斜线: 行下标和列下标之和相等
// 使用三个集合cols和diago1和diago2记录每一列以及两个方向上是否有皇后, 对行进行依次遍历
// time: O(n!)
// space: O(n)
class Solution0 {
  public:
	vector<vector<string>> solveNQueens(int n) {
		vector<vector<string>> solutions;
		vector<int> queens(n, -1);
		unordered_set<int> columns;
		unordered_set<int> diagonals1;
		unordered_set<int> diagonals2;
		backtrack(solutions, queens, n, 0, columns, diagonals1, diagonals2);
		return solutions;
	}
  private:
	void backtrack(vector<vector<string>> &solutions, vector<int> &queens, int n, int row, 
		unordered_set<int> &columns, unordered_set<int> &diagonals1, unordered_set<int> &diagonals2) {
		if (row == n) {
			vector<string> board = generateBoard(queens, n);	// 得到一个可行解
			solutions.push_back(board);
		} else {
			for (int i = 0; i < n; ++i) {	// row是当前行, i表示对列进行遍历判断可行性
				if (columns.find(i) != columns.end()) continue;	// 当前列有Q
				int diagonal1 = row - i;
				if (diagonals1.find(diagonal1) != diagonals1.end()) continue;
				int diagonal2 = row + i;
				if (diagonals2.find(diagonal2) != diagonals2.end()) continue;
				queens[row] = i;	// 下标是行, 值是对应的可行列
				columns.insert(i);
				diagonals1.insert(diagonal1);
				diagonals2.insert(diagonal2);
				backtrack(solutions, queens, n, row + 1, columns, diagonals1, diagonals2);
				queens[row] = -1;	// 状态回溯
				columns.erase(i);
				diagonals1.erase(diagonal1);
				diagonals2.erase(diagonal2);
			}
		}
	}
	vector<string> generateBoard(vector<int> &queens, int n) {
		vector<string> board;
		for (int i = 0; i < n; ++i) {
			string row = string(n, '.');
			row[queens[i]] = 'Q';
			board.push_back(row);
		}
		return board;
	}
};

// 基于位运算的回溯
// 从左上到右下的斜线: 行下标和列下标之差相等 | 从右上到左下的斜线: 行下标和列下标之和相等
// 将三个集合替换为三个整数的位运算, 0表示可以放, 1表示不能放, 三个整数按位或运算即得到可以放皇后的位置
// x & (-x)为lowbit, x & (x - 1)可以将最低位的1置为0.
// https://blog.csdn.net/b10221001/article/details/102118216 
// __builtin_parity(unsigned int x) 统计二进制中1个个数是偶数还是奇数	失效 ?
// __builtin_ffs(unsigned int x) 找出一个数的二进制中从末尾开始到遇见第一个1的位置	失效 ? 
// __builtin_popcount(unsigned int x) 统计二进制中1的个数
// __builtin_clz(unsigned int x) 返回一个二进制数中前导0的个数
// __builtin_ctz(unsigned int x) 返回一个二进制数中后导0的个数
// time: O(n!)
// space: O(1)
class Solution {
  public:
	vector<vector<string>> solveNQueens(int n) {
		vector<vector<string>> solutions;
		vector<int> queens(n, -1);
		solve(solutions, queens, n, 0, 0, 0, 0);
		return solutions;
	}
  private:
	void solve(vector<vector<string>> &solutions, vector<int> &queens, int n, int row, int columns, int diagonals1, int diagonals2) {
		if (row == n) {
			vector<string> board = generateBoard(queens, n);	// 得到一个可行解
			solutions.push_back(board);
		} else {
			int availablePositions = ((1 << n) - 1) & (~(columns | diagonals1 | diagonals2));	// 所有的可放置位置, 1表示可放置
			while (availablePositions != 0) {
				int position = availablePositions & (-availablePositions);	// lowBit, 一个可放位置
				availablePositions = availablePositions & (availablePositions - 1);	// lowbit置0, 便于计算下一个可放位置
				int column = __builtin_ctz(position);	// 返回二进制尾0数目, 表示列数
				queens[row] = column;
				solve(solutions, queens, n, row + 1, columns | position, (diagonals1 | position) >> 1, (diagonals2 | position) << 1);	// 通过左移和右移控制对角线的放置规则
				queens[row] = -1;	// 回溯
			}
		}
	}
	vector<string> generateBoard(vector<int> &queens, int n) {
		vector<string> board;
		for (int i = 0; i < n; ++i) {
			string row = string(n, '.');
			row[queens[i]] = 'Q';
			board.push_back(row);
		}
		return board;
	}
};

int main() {
	Solution s;
	// cout << __builtin_ffs(4) << endl;
	// cout << __builtin_parity(4) << endl;
	// cout << __builtin_ctz(4) << endl;
	// cout << __builtin_popcount(4) << endl;
	// cout << __builtin_clz(4) << endl;
	auto ans = s.solveNQueens(4);
	show2DVector(ans);
	return 0;
}