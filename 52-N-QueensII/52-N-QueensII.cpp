#include <vector>
#include <iostream>
using namespace std;

class Solution
{
  public:
    int totalNQueens(int n)
    {
		int num = 0;
		vector<int> C(n, 0);
		dfs(C, num, n, 0);
		return num;
    }

  private:
    void dfs(vector<int> &C, int &num, const int n, int i)
    { //第i行
		if (i >= n)
		{ //递归出口
			num++;
			return;
		}
		for (int j = 0; j < n; ++j)
		{ //Q位于第j列,当前步的遍历
			if (isValid(C, i, j))
			{			       //第i行可以位于第j列
				C[i] = j;	      //往前走一步
				dfs(C, num, n, i + 1); //递归入口
				C[i] = 0;	      //回溯
			}
		}
    }
    bool isValid(const vector<int> &C, const int i, const int j)
    { //是否可以在i行j列
		for (int k = 0; k < i; ++k)
			if (C[k] == j || abs(C[k] - j) == i - k)
				return false;
		return true;
    }
};

int main()
{
    Solution s1;
    int n = 5;
    cout << s1.totalNQueens(n) << endl;
    return 0;
}