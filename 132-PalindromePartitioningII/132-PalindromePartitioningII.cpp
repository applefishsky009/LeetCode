#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

///每次从i向右扫描(i的遍历)，每找到一个回文(j的遍历)就算一次DP，可以转换成f(i)=min{f(j+1)+1} ,i<=j<n
//定义状态 P[i][j] = true if [i,j]是回文，那么P[i][j] = str[i] == str[j] && P[i + 1][j - 1]
//注意上边转移函数P[i][j]依赖于P[i + 1][j - 1]，因此i递减，j递增，否则要做备忘录

//时间复杂度O(n^2),空间复杂度O(n^2)
class Solution
{
  public:
    int minCut(const string &s)
    {
		const int n = s.size();
		vector<int> f(n + 1, 0);
		vector<vector<bool>> p(n, vector<bool>(n, false));
		//fill_n(&p[0][0], n * n, false);	#include <algorithm>,参数分别是头指针，数量，值
		//the worst case is cutting by each char，从上往下DP，所以f[n-1]=0,f[0]=n-1
		for (int i = 0; i <= n; i++)
			f[i] = n - 1 - i; // ᰯ最后一个f[n]=-1是超尾，用于DP第一次[n-1][n-1]的初始化
		for (int i = n - 1; i >= 0; i--)
		{ //f(n)的DP
			for (int j = i; j < n; j++)
			{ //find Palindrome的DP
				if (s[i] == s[j] && (j - i < 2 || p[i + 1][j - 1]))
				{
					p[i][j] = true;
					f[i] = min(f[i], f[j + 1] + 1); //第一次f[n-1][n-1]一定是0，表示从后往前第一个字符不用划分
				}				    //对于一个i，j++时f[i]找到一次回文就更新一次最小值
			}
		}
		return f[0];
    }
};

int main()
{
    Solution s1;
    const string s = "aab";
    cout << s1.minCut(s) << endl;
    return 0;
}