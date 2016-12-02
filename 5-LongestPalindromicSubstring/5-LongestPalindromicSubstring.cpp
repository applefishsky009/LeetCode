#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

//以每个元素为中间元素，同时从左右出发寻找O(n^2)
class Solution
{
  public:
    string longestPalindrome(const string &s)
	{
		const int n = s.size();
		if (n < 2)
			return s;
		int maxLen = 0;
		int j = 0; //low
		int k = 0; //high
		int minLen = 0;
		for (int i = 0; i < n; ++i)
		{
			if (n - i - 1 < maxLen / 2)
				break; //剩下的元素不足最长序列的一半，不可能更新长度
			j = i;
			k = i;
			while (k < n - 1 && s[k + 1] == s[j])
				k++; //skip duplicate characters
			while (j > 0 && k < n - 1 && s[j - 1] == s[k + 1])
			{
				--j;
				++k;
			} //search from both sides
			if (k - j + 1 > maxLen)
			{
				maxLen = k - j + 1;
				minLen = j;
			} //mark down the low index
		}
		return s.substr(minLen, maxLen);
    }
};

//Manacher's Algorithm O(n)
class Solution1
{
  public:
    string longestPalindrome(string s)
    {
		string T = preProcess(s); //必定是奇数长度，引入了(不一致的)边界。
		//用一侧长度表示源字符串的回文长度，回文加1，一侧要加2
		const int n = T.size();
		//以T[i]为中心，向左右扩张的长度，不包含T[i]自己
		//因此P[i]是源字符串中回文串的长度
		vector<int> P(n, 0);
		int C = 0, R = 0; //字串中心与右边界
		for (int i = 1; i < n - 1; i++)
		{
			int i_mirror = 2 * C - i; // equals to i' = C - (i-C)
			//core code
			P[i] = (R > i) ? min(R - i, P[i_mirror]) : 0; //取最小值再更新匹配
			//i在回文串内，保证了[i_mirror,C]=[C,i],又在P[i_mirror]判断过回文串长度，因此取最小值后判断
			//用可能的最左边界，来判断最右边界，以此为基础向上判断，这就是比双指针优化的地方
			// Attempt to expand palindrome centered at i
			while (T[i + 1 + P[i]] == T[i - 1 - P[i]])
				P[i]++;
			// If palindrome centered at i expand past R,
			// adjust center based on expanded palindrome.
			if (i + P[i] > R)
			{
				//每当右边界刷新记录时，更新回文串中心与半径
				//没遇到回文串之前每个偶数都是更新，回文中心变化，半径+1
				C = i;
				R = i + P[i];
			}
		}
		// Find the maximum element in P.
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