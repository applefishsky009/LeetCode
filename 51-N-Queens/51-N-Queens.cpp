#include <vector>
#include <string>
#include <iostream>
#include <E:\RylModule\vector.h>
using namespace std;

class Solution
{
  public:
    vector<vector<string>> solveNQueens(int n)
    {
		vector<vector<string>> result;
		vector<int> C(n, -1); // C[i]表示第i行皇后所在的列编号
		dfs(C, result, 0);
		return result;
    }

  private:
    void dfs(vector<int> &C, vector<vector<string>> &result, int row)
    {
		const int n = C.size();
		if (row == n)
		{ //终止条件，意味着有可行解，制作可行解。
			vector<string> solution;
			for (int i = 0; i < n; ++i)
			{
				string s(n, '.'); //fill (6)	string(size_t n, char c);
				for (int j = 0; j < n; ++j)
				{ //找每一行的Q的列编号
					if (j == C[i])
					s[j] = 'Q';
				}
				solution.push_back(s);
			}
			result.push_back(solution); //可行解入集合
			return;			//终止递归
		}
		for (int j = 0; j < n; ++j)
		{ //逐列寻找，合法则递归
			const bool ok = isValid(C, row, j);
			if (!ok)
				continue; //非法，尝试下一列
			//合法，记录并递归
			C[row] = j;
			dfs(C, result, row + 1);
			//递归完成，撤销动作继续找合法位置
			C[row] = -1;
		}
    }
    bool isValid(const vector<int> &C, int row, int j)
    {
		for (int i = 0; i < row; ++i)
			if (C[i] == j || abs(C[i] - j) == abs(i - row))
				return false;
		return true;
    }
};

int main()
{
    Solution s1;
    int n = 4;
    vector<vector<string>> result = s1.solveNQueens(n);
    show2DVector(result);
    return 0;
}