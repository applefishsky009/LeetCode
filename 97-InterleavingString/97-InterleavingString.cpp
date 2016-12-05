#include <vector>
#include <string>
#include <iostream>
using namespace std;

//dfs，会超时(这在release版本下运行超过30s)
class Solution
{
  public:
    bool isInterleave(string s1, string s2, string s3)
    {
		if (s3.size() != s1.size() + s2.size())
			return false;
		int beginS1 = 0;
		int beginS2 = 0;
		int beginS3 = 0;
		return dfs(s1, s2, s3, beginS1, beginS2, beginS3);
    }

  private:
    bool dfs(string s1, string s2, string s3, int beginS1, int beginS2, int beginS3)
    {
		const int m = s1.size();
		const int n = s2.size();
		for (int i = beginS3; i < m + n; ++i)
		{
			if (s3[i] != s1[beginS1] && s3[i] != s2[beginS2])
				return false;
			if (s3[i] == s1[beginS1])
			{
				if (s3[i] == s2[beginS2])
				{
					if (dfs(s1, s2, s3, beginS1 + 1, beginS2, i + 1))
						return true;
					if (dfs(s1, s2, s3, beginS1, beginS2 + 1, i + 1))
						return true;
					return false;
				}
				else
					beginS1++;
			}
			else
				beginS2++;
		}
		return true;
    }
};

//二维数组，路径(是否有通路)
//aa ab aaba
// 2 a 1 0 1
// 1 a 1 1 1
// 0   1 1 0
//       a b
//     0 1 2

class Solution1
{
  public:
    bool isInterleave(const string &s1, const string &s2, const string &s3)
    {
		if (s3.size() != s1.size() + s2.size())
			return false;
		const int m = s1.size();
		const int n = s2.size();
		vector<vector<bool>> path(m + 1, vector<bool>(n + 1, true));
		//初始化，第零行或者第零列意味着s3和另一字符串做匹配，实际匹配时的路径只与左或下的取值(还有字符是否匹配)相关
		for (size_t i = 1; i < m + 1; ++i)
			path[i][0] = path[i - 1][0] && s1[i - 1] == s3[i - 1];
		for (size_t i = 1; i < n + 1; ++i)
			path[0][i] = path[0][i - 1] && s2[i - 1] == s3[i - 1];
		//计算通路
		for (size_t i = 1; i < m + 1; ++i)
			for (size_t j = 1; j < n + 1; ++j)
				path[i][j] = (s1[i - 1] == s3[i + j - 1] && path[i - 1][j]) || 
							 (s2[j - 1] == s3[i + j - 1] && path[i][j - 1]);
		return path[m][n];
    }
};

int main()
{
    Solution1 s;
    //string s1 = "bbbbbabbbb";
    //string s2 = "babaaaabba";
    //string s3 = "babbbabbbaaabbababbb";
    string s1 = "bbbbbabbbbabaababaaaabbababbaaabbabbaaabaaaaababbbababbbbbabbbbababbabaabababbbaabababababbbaaababaa";
    string s2 = "babaaaabbababbbabbbbaabaabbaabbbbaabaaabaababaaaabaaabbaaabaaaabaabaabbbbbbbbbbbabaaabbababbabbabaab";
    string s3 = "babbbabbbaaabbababbbbababaabbabaabaaabbbbabbbaaabbbaaaaabbbbaabbaaabababbaaaaaabababbababaababbababbbababbbbaaaabaabbabbaaaaabbabbaaaabbbaabaaabaababaababbaaabbbbbabbbbaabbabaabbbbabaaabbababbabbabbab";
    cout << s.isInterleave(s1, s2, s3) << endl;
    return 0;
}