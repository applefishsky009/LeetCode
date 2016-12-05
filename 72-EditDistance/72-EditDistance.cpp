#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//两个字符串问题，很显然是二维DP
//设状态为f[i][j],表示A[0,i]和B[0,j]之间的最小编辑距离，设A[0,i]形式是str1c;B[0,j]形式是str2d;
//如果c==d，则f[i][j] = f[i-1][j-1];
//如果c != d,
//	替换：f[i][j] = f[i-1][j-1]+1;	//c替换为d
//	添加：f[i][j] = f[i][j-1]+1;	//表示c后添加一个d，str1c与str2之间的距离加1
//	删除：f[i][j] = f[i-1][j]+1;	//表示删除c，str1与str2d之间的距离加1

//初始化DP状态
//状态转移函数(当前状态每一个可能的操作对应的转移函数)
class Solution
{
  public:
    int minDistance(string word1, string word2)
    {
		const int m = word1.size();
		const int n = word2.size();
		vector<vector<int>> f(m + 1, vector<int>(n + 1, 0));
		for (int i = 0; i <= m; ++i)
			f[i][0] = i;
		for (int j = 0; j <= n; ++j)
			f[0][j] = j;
		for (int i = 1; i <= m; ++i)
		{
			for (int j = 1; j <= n; ++j)
			{
				if (word1[i - 1] == word2[j - 1])
					f[i][j] = f[i - 1][j - 1];
				else
					f[i][j] = min(f[i - 1][j - 1] + 1, min(f[i - 1][j] + 1, f[i][j - 1] + 1));
			}
		}
		return f[m][n];
    }
};

//考虑到上述的二维DP状态转移可能与之前三个状态有关(矩阵左、下、左下三个角)，因此可以优化空间
//将m*n优化为m*1，左下的状态可以用一个变量来记录(这是因为下方的还未更新，左边的已经更新)
class Solution1
{
  public:
    int minDistance(const string &word1, const string &word2)
    {
		if (word1.size() < word2.size())
			return minDistance(word2, word1);
		vector<int> f(word2.size() + 1, 0);
		int upper_left = 0; //额外变量记录 f[i-1][j-1]
		for (size_t i = 0; i <= word2.size(); ++i)
			f[i] = i;
		for (size_t i = 1; i <= word1.size(); ++i)
		{
			upper_left = f[0];
			f[0] = i;
			for (size_t j = 1; j <= word2.size(); ++j)
			{
				int upper = f[j];
				if (word1[i - 1] == word2[j - 1])
					f[j] = upper_left;
				else
					f[j] = 1 + min(upper_left, min(f[j], f[j - 1]));
				upper_left = upper;
			}
		}
		return f[word2.length()];
    }
};

int main()
{
    Solution1 s1;
    string word1("abcde");
    string word2("cavdffff");
    int result = s1.minDistance(word1, word2);
	cout << result << endl;
    return 0;
}