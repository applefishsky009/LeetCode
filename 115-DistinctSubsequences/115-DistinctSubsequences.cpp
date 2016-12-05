#include <string>
#include <vector>
#include <iostream>
using namespace std;

//两个字符串问题，经典二维DP，下边用二维空间解答(习惯)，换成一维滚动数组的方法很简单
//设状态为f[i][j]表示T[0,j]在S[0,i]出现的次数，那么就有如下状态转移方程：
//1. 若s[i] == T[j] f[i][j] = f[i - 1][j] + f[i - 1][j-1]
//2. 若s[i] != T[j] f[i][j] = f[i - 1][j]
//注意初始条件，我们认为s[i][0]永远为1,即s之前永远有一个T[0,0]
class Solution
{
  public:
    int numDistinct(string s, string t)
    {
        const int m = t.size();
        const int n = s.size();
        vector<vector<int>> f(n + 1, vector<int>(m + 1, 0));
        for (int i = 0; i <= n; ++i)
            f[i][0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (t[j - 1] != s[i - 1])
                    f[i][j] = f[i - 1][j];
                else
                    f[i][j] = f[i - 1][j] + f[i - 1][j - 1];
            }
        }
        return f[n][m];
    }
};

//滚动数组
class Solution1
{
  public:
    int numDistinct(const string &S, const string &T)
    {
        vector<int> f(T.size() + 1);
        f[0] = 1;
        for (int i = 0; i < S.size(); ++i)
            for (int j = T.size() - 1; j >= 0; --j)
                f[j + 1] += S[i] == T[j] ? f[j] : 0;
        return f[T.size()];
    }
};

int main()
{
    string s = "rabbbit";
    string t = "rabbit";
    Solution s1;
    int k = s1.numDistinct(s, t);
    cout << k << endl;
    return 0;
}