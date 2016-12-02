#include <vector>
#include <iostream>
using namespace std;

//自己之前在数独解析器里边写的接口，时间复杂度O(n^4)
//有很多重复检测，比如f[0][0],f[0][1]的列检测
class Solution {
public:
	bool isValidSudoku(const vector<vector<char>>& board){
		for (int i = 0;i < 9;++i)
			for (int j = 0;j < 9;++j)
				if (board[i][j] != '.' && !checkPool(board,i,j)) 
                    return false; 
		return true;
	}
private:
	bool checkPool(const vector<vector<char>>& board, const int row, const int col){
		for (int i = 0;i < 9;++i)
			if (i != row && board[i][col] == board[row][col]) 
                return false;
		for (int j = 0;j < 9;++j)
			if (j != col && board[row][j] == board[row][col]) 
                return false;
		int squarStartRow = (row / 3) * 3;
		int squarStartCol = (col / 3) * 3;
		for (int i = squarStartRow;i < squarStartRow + 3;++i)
			for (int j = squarStartCol;j < squarStartCol + 3;++j)
				if (!(i == row && j == col) && board[i][j] == board[row][col]) 
                    return false;
		return true;
	}
};

// LeetCode, Valid Sudoku
// 时间复杂度 O(n^2) 空间复杂度 O(1)，用Hash Table，去掉重复检测加速
class Solution1 {
public:
    bool isValidSudoku(const vector<vector<char>>& board) {
        bool used[9];
        for (int i = 0; i < 9; ++i) {
            fill(used, used + 9, false);
            for (int j = 0; j < 9; ++j) //检查行
                if (!check(board[i][j], used))
                    return false;
            fill(used, used + 9, false);
            for (int j = 0; j < 9; ++j) //检查列
                if (!check(board[j][i], used))
                    return false;
        }
        for (int r = 0; r < 3; ++r) //检查9个子格子'
            for (int c = 0; c < 3; ++c) {
                fill(used, used + 9, false);
                for (int i = r * 3; i < r * 3 + 3; ++i)
                    for (int j = c * 3; j < c * 3 + 3; ++j)
                        if (!check(board[i][j], used))
                            return false;
            }
        return true;
    }
private:
    bool check(char ch, bool used[9]) {
        if (ch == '.') 
            return true;
        if (used[ch - '1']) 
            return false;
        return used[ch - '1'] = true;
    }
};

int main() {
	Solution1 s1;
	vector<vector<char>> board = { { '5','3','.','.','7','.','.','.','.' },
								   { '6','.','.','1','9','5','.','.','.' },
								   { '.','9','8','.','.','.','.','6','.' },
								   { '8','.','.','.','6','.','.','.','3' },
								   { '4','.','.','8','.','3','.','.','1' },
								   { '7','.','.','.','2','.','.','.','6' },
								   { '.','6','.','.','.','.','2','8','.' },
								   { '.','.','.','4','1','9','.','.','5' },
								   { '.','.','.','.','8','.','.','7','9' } };
    bool isValid = s1.isValidSudoku(board);
    cout << isValid << endl;
    return 0;
}