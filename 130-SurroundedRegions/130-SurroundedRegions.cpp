#include <queue>
#include <vector>
#include <E:\RylModule\vector.h>
using namespace std;

//BFS，从外围开始，'O'发现之后改变节点值(这样就不用记录是否遍历过了)并BFS(相邻符合条件的节点进队列)
class Solution
{
  public:
    void solve(vector<vector<char>> &board)
    {
		int x = board.size();
		if (x < 1)
			return;
		int y = board[0].size();
		for (int j = 0; j < y; ++j)
		{ //检查上下边界
			if (board[0][j] == 'O')
				bfs(board, 0, j, x, y);
			if (board[x - 1][j] == 'O')
				bfs(board, x - 1, j, x, y);
		}
		for (int i = 0; i < x; ++i)
		{ //检查左右边界
			if (board[i][0] == 'O')
				bfs(board, i, 0, x, y);
			if (board[i][y - 1] == 'O')
				bfs(board, i, y - 1, x, y);
		}
		for (int j = 0; j < y; ++j) //遍历得到目标矩阵
			for (int i = 0; i < x; ++i)
				board[i][j] = board[i][j] == '+' ? 'O' : 'X';
    }

  private:
    void bfs(vector<vector<char>> &board, int i, int j, int x, int y)
    {
		board[i][j] = '+';
		queue<pair<int, int>> q;
		q.push(make_pair(i, j));
		while (!q.empty())
		{
			//不能递归，递归了就是dfs，注意更新下标[i][j]
			int i = q.front().first;
			int j = q.front().second;
			if (i > 0 && board[i - 1][j] == 'O')
			{
				board[i - 1][j] = '+';
				q.push(make_pair(i - 1, j));
			} //同列上一行
			if (i < x - 1 && board[i + 1][j] == 'O')
			{
				board[i + 1][j] = '+';
				q.push(make_pair(i + 1, j));
			} //同列下一行
			if (j > 0 && board[i][j - 1] == 'O')
			{
				board[i][j - 1] = '+';
			q.push(make_pair(i, j - 1));
				} //同行上一列
			if (j < y - 1 && board[i][j + 1] == 'O')
			{
				board[i][j + 1] = '+';
				q.push(make_pair(i, j + 1));
			} //同同行侠一列
			q.pop();
		}
    }
};

int main()
{
    Solution s1;
    vector<vector<char>> board = 
		{{'X', 'X', 'X', 'X'}, 
		 {'X', 'O', 'O', 'X'}, 
		 {'X', 'X', 'O', 'X'},
		 {'X', 'O', 'X', 'X'}};
    s1.solve(board);
	show2DVector(board);
    return 0;
}
