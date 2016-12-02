#include <vector>
#include <iostream>
#include <E:\RylModule\vector.h>
using namespace std;

//注意原地修改的DFS一定要返回bool来判断是否需要重置现场，否则无条件重置现场必然会出现问题
//DFS当前步的决策与之后的结果有关，自己写的
class Solution
{
  public:
    void solveSudoku(vector<vector<char>> &board)
    {
		dfs(board, 0);
		return;
    }

  private:
    bool dfs(vector<vector<char>> &board, int cell)
    {
		if (cell == 81)
			return true;
		int row = cell / 9;
		int col = cell % 9;
		if (board[row][col] != '.')
			return dfs(board, cell + 1);
		else
		{
			vector<bool> charPool(10, true); //Hash Table
			makePool(charPool, board, row, col);
			for (int i = 1; i <= 9; ++i)
			{
				if (charPool[i] == true)
				{
					board[row][col] = i + '0';
					if (dfs(board, cell + 1))
						return true;
				}
			}
			board[row][col] = '.'; //Backtracking(当前步填什么都是错的，回溯并返回false)
			return false;
		}
    }
    void makePool(vector<bool> &charPool, const vector<vector<char>> &board, const int row, const int col)
    {
		for (int i = 0; i < 9; ++i)
			if (board[i][col] != '.')
				charPool[board[i][col] - '0'] = false;
		for (int j = 0; j < 9; ++j)
			if (board[row][j] != '.')
				charPool[board[row][j] - '0'] = false;
		int squarStartRow = (row / 3) * 3;
		int squarStartCol = (col / 3) * 3;
		for (int i = squarStartRow; i < squarStartRow + 3; ++i)
			for (int j = squarStartCol; j < squarStartCol + 3; ++j)
				if (board[i][j] != '.')
					charPool[board[i][j] - '0'] = false;
    }
};

//针对每一个位置遍历，有效的值dfs，效率没有Hash Table高
class Solution1
{
  public:
    bool solveSudoku(vector<vector<char>> &board)
    {
		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j)
			{
				if (board[i][j] == '.')
				{
					for (int k = 0; k < 9; ++k)
					{
						board[i][j] = '1' + k;
						if (isValid(board, i, j) && solveSudoku(board))
							return true;
						board[i][j] = '.';
					}
					return false;
				}
			}
		return true;
    }

  private:
    bool isValid(const vector<vector<char>> &board, int x, int y)
    {
	int i, j;
	for (i = 0; i < 9; i++)
	    if (i != x && board[i][y] == board[x][y])
		return false;
	for (j = 0; j < 9; j++)
	    if (j != y && board[x][j] == board[x][y])
		return false;
	for (i = 3 * (x / 3); i < 3 * (x / 3 + 1); i++)
	    for (j = 3 * (y / 3); j < 3 * (y / 3 + 1); j++)
		if ((i != x || j != y) && board[i][j] == board[x][y])
		    return false;
	return true;
    }
};

int main()
{
    Solution1 s1;
    vector<vector<char>> board = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
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