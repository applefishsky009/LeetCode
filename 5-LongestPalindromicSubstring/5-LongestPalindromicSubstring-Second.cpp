#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

// DP: P[i, j] = P[i + 1, j - 1] ^ Si == Sj
class Solution
{
  public:
    string longestPalindrome(string s) {
        int i = 0, j = 0, l = 0, n = s.size();
        string ans;
        vector<vector<int>> dp(n, vector<int>(n));
        for (l = 0; l < n; ++l)	// 行扫描
            for (i = 0; i + l < n; ++i) {	// 列扫描优先
                j = i + l;	//DP状态方程右上角
                if (l == 0)
                    dp[i][j] = 1;	// 对角线是回文
                else if (l == 1)	// 对角线右上位置
                    dp[i][j] = (s[i] == s[j]);
                else	// 利用左下位置状态转移
                    dp[i][j] = (s[i] == s[j] && dp[i + 1][j - 1]);
                if (dp[i][j] && l + 1 > ans.size()) 
                    ans = s.substr(i, l + 1);
            }
        return ans;
    }
};

// Manacher's Algorithm O(n)-臂长的map信息
// O(n) runtime
// O(n) space
class Solution1
{
  public:
    string longestPalindrome(string s)
    {
		string T = preProcess(s); //必定是奇数长度，引入了(不一致的)边界。
		const int n = T.size();
		vector<int> P(n, 0); // 臂长
		int C = 0, R = 0; // 字串中心与右边界
		for (int i = 1; i < n - 1; i++)
		{
			int i_mirror = 2 * C - i; // equals to i' = C - (i - C), 已经判断过的镜像位置
			P[i] = (R > i) ? min(R - i, P[i_mirror]) : 0; // 取最小值再更新匹配, 计算先验信息的臂长
			while (T[i + 1 + P[i]] == T[i - 1 - P[i]])	// 更新臂长
				P[i]++;
			if (i + P[i] > R)	// 臂长拓展到新位置,C,R更新便于复用先验信息
			{
				C = i;
				R = i + P[i];
			}
		}
		// 映射回子串
		int max_len = 0;
		int center_index = 0;
		for (int i = 1; i < n - 1; i++)
		{
			if (P[i] > max_len)
			{
				max_len = P[i];
				center_index = i;
			}
		}
		return s.substr((center_index - 1 - max_len) / 2, max_len);
    }

  private:
    // Transform S into T.
    // For example, S = "abba", T = "^#a#b#b#a#$".
    // ^ and $ signs are sentinels appended to each end to avoid bounds checking
    string preProcess(const string &s)
    {
		int n = s.length();
		if (n == 0)
			return "^$";
		string ret = "^";
		for (int i = 0; i < n; i++)
			ret += "#" + s.substr(i, 1);
		ret += "#$";
		return ret;
    }
};

int main()
{
    Solution1 s1;
    string s = "importantabcdedcbasimple";
    cout << s1.longestPalindrome(s) << endl;
    return 0;
}