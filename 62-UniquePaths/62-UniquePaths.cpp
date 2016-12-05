#include <vector>
#include <iostream>
using namespace std;

//Solution1:数学方法
//[m,n]矩阵，从起点到终点一共有m+n-2步骤，向右一共m-1步，向下n-1步
//每一步选择向右或者向下，从m+n-2中选出m-1向右的步骤
//共有Cm-1，m+n-2种

//1.DFS,简单的二分递归
class Solution1
{
  public:
    int uniquePaths(int m, int n)
    {
		if (m < 1 || n < 1) //越界后终止，返回0，比如[2,1]->[1,1]+[2,0] = 1+0；
			return 0;
		if (m == 1 && n == 1) //收敛到终点，返回1.
			return 1;
		return uniquePaths(m - 1, n) + uniquePaths(m, n - 1);
    }
};

//二分递归有重复计算，加一个已计算过的数据表
class Solution2
{
  public:
    int uniquePaths(int m, int n)
    {
		f = vector<vector<int>>(m, vector<int>(n, 0));
		f[0][0] = 1;
		return dfs(m - 1, n - 1);
    }

  private:
    vector<vector<int>> f; //建立备忘录

    int dfs(int x, int y)
    {
		if (x < 0 || y < 0) //越界(注意由于下标索引，和Solution1不一样)后终止，返回0，比如[2,1]->[1,1]+[2,0] = 1+0；
			return 0;
		if (x == 0 && y == 0) //收敛到终点(0,0)，返回1。
			return f[0][0];
		if (f[x][y] > 0) //已经备忘过，直接返回
			return f[x][y];
		f[x][y] = dfs(x - 1, y) + dfs(x, y - 1); //没有备忘过，计算并返回
		return f[x][y];
    }
};

//自底向上的动态规划，递推公式在对第j列更新时：f[j] = f[j]+f[j-1]
//	  列：1 2 3  4  5  6  7  8  9……n		对应f下标减一
//第一次：1 1 1  1  1  1  1  1  1
//第二次：1 2 3  4  5  6  7  8  9
//第三次：1 3 6 10 15 21 28 36 45
//……
//第m次 ：1 m ......
class Solution
{
  public:
    int uniquePaths(int m, int n)
    {
		vector<int> f(n, 0);
		f[0] = 1;
		for (int i = 0; i < m; i++)
			for (int j = 1; j < n; j++)
				f[j] = f[j] + f[j - 1];
		return f[n - 1];
    }
};

int main()
{
    int m = 8;
    int n = 2;
    Solution s1;
    cout << s1.uniquePaths(m, n) << endl;
    return 0;
}