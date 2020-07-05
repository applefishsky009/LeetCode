#include <vector>
#include <string>
#include <iostream>
using namespace std;

// 朴素匹配-超时
// time: O(??)
// Space: O(??)
class Solution1 {
  public:
	bool isMatch(string s, string p) {
		return isMatch(s, p, 0, 0);
	}
  private:
	bool isMatch(const string &s, const string &p, int spos, int ppos) {
		cout << "spos:" << spos << " ppos:" << ppos << endl;
		if (ppos == p.size() && spos == s.size())
			return true;
		if (p[ppos] == '?' || p[ppos] == s[spos])
			return isMatch(s, p, spos + 1, ppos + 1);
		else if (p[ppos] == '*') {
			while (ppos < p.size() && p[ppos + 1] == '*')	// 多个*进行剪枝
				ppos++;
			for (int i = spos; i <= s.size(); i++)
				if (isMatch(s, p, i, ppos + 1))
					return true;
		}
		return false;
	}
};

// dp
// dp[i][j] = dp[i - 1][j - 1] if si == pj || p[j] == ?
// dp[i][j] = dp[i][j - 1] || dp[i - 1][j] if p[j] == *	
// dp[i][j] = dp[i][j - 1]表示不使用这个*,直接跳过, 
// dp[i][j] = dp[i - 1][j]表示*匹配一个或多个字符,这里只用了一个是因为dp[i - 1][j]的计算过程必然计算过之前的多个匹配了
// 证明: dp[i][j] = dp[i][j - 1] | dp[i - 1][j - 1] | ... | dp[0][j - 1], dp[i - 1][j] = dp[i - 1][j - 1] | dp[i - 2][j - 1] | ... | dp[0][j - 1]
// 所以 dp[i][j] = dp[i][j - 1] | dp[i - 1][j]
// dp[i][j] = 0, others
// time: O(mn)
// Space: O(mn)
class Solution2 {
  public:
	bool isMatch(string s, string p) {
		int slen = s.size(), plen = p.size();
		vector<vector<int>> dp(slen + 1, vector<int>(plen + 1, 0));
		dp[0][0] = 1;	// 初始化
		for (int j = 1; j <= plen; j++)	{	// dp[i][0]表示p是空串,dp值全为0
			if (p[j - 1] == '*') dp[0][j] = 1;	// dp[0][j]表示s是空串,p的前j个字符均为*号时才匹配
			else break;
		}
		for (int i = 1; i <= slen; i++) {
			for (int j = 1; j <= plen; j++) {
				if (p[j - 1] == '*')
					dp[i][j] = dp[i][j - 1] | dp[i - 1][j];
				else if (p[j - 1] == '?' || s[i - 1] == p[j - 1])
					dp[i][j] = dp[i - 1][j - 1];
			}
		}
		return dp[slen][plen];
	}
};

// 贪心
// time: O(mlgn)
// Space: O(1)
class Solution3 {
  public:
	bool isMatch(string s, string p) {
		auto allStars = [](const string &str, int left, int right) {
			for (int i = left; i < right; i++)
				if (str[i] != '*')
					return false;
			return true;
		};
		auto charMatch = [](char u, char v) {
			return u == v || v == '?';
		};
		while (s.size() && p.size() && p.back() != '*') {
			if (charMatch(s.back(), p.back())) {
				s.pop_back();
				p.pop_back();
			}
			else return false;
		}
		if (p.empty()) return s.empty();
		int sIndex = 0, pIndex = 0;	// 表示遍历到s和p的位置, 在s中寻找某个ui
		int sRecord = -1, pRecord = -1;
		while (sIndex < s.size() && pIndex < p.size()) {
			if (p[pIndex] == '*') {	// 遇到*表示找到了ui,开始找ui + 1的字符串
				++pIndex;
				sRecord = sIndex;	// 记录起始位置
				pRecord = pIndex;
			} else if (charMatch(s[sIndex], p[pIndex])) {	// 字符匹配, 继续寻找ui的下一个字符
				++sIndex;
				++pIndex;
			} else if (sRecord != -1 && sRecord + 1 < s.size()) {	// 两个字符不匹配, 重新寻找ui, 枚举下一个s中的起始位置
				++sRecord;
				sIndex = sRecord;
				pIndex = pRecord;
			} else 	// 不匹配且下一个位置不存在, 匹配失败
				return false;
		}
		return allStars(p, pIndex, p.size());
	}
};

// Two Pointers-贪心
// time: O(mlgn)
// Space: O(1)
class Solution {
  public:
	bool isMatch(string s, string p) {
		return isMatch(s.c_str(), p.c_str());
	}
  private:
	bool isMatch(const char *s, const char *p) {
		bool star = false;
		const char *str, *ptr;
		for (str = s, ptr = p; *str != '\0'; str++, ptr++) {
			switch (*ptr) {
			case '?':	// 下一趟匹配
				break;
			case '*':	// 找到了*分割的当前字符串, 找下一个
				star = true;
				s = str, p = ptr;	// 记录起始位置
				while(*p == '*')	// skip continuous
					p++;
				if (*p == '\0')
					return true;	// 紧跟结束符任意匹配
				str = s - 1;	// 回退一格, 抵消for中的自加
				ptr = p - 1;	
				break;
			default:
				if (*str != *ptr) {	// 当前不相等
					if (!star)	// 不相等且没出现过通配符, 匹配失败
						return false;
					s++;	// 在s中贪心匹配字符
					str = s - 1;	// 回退
					ptr = p - 1;
				} // else 匹配成功, 下趟匹配
			}
		}
		while (*ptr == '*')
			ptr++;
		return (*ptr == '\0');
	}
};

int main() {
	Solution s;
	string s0 = "aa";
	string p0 = "a";
	string s1 = "cb";
	string p1 = "?a";
	string s2 = "adceb";
	string p2 = "a*b";
	string s3 = "acdcb";
	string p3 = "a*c?b";
	string s4 = "aa";
	string p4 = "*";
	string s5 = "aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba";
	string p5 = "a*******b";
	string s6 = "aaaa";
	string p6 = "***a";
	string s7 = "abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabababaabbababaabbbbbbaaaabababbbaabbbbaabbbbababababbaabbaababaabbbababababbbbaaabbbbbabaaaabbababbbbaababaabbababbbbbababbbabaaaaaaaabbbbbaabaaababaaaabb";
	string p7 = "**aa*****ba*a*bb**aa*ab****a*aaaaaa***a*aaaa**bbabb*b*b**aaaaaaaaa*a********ba*bbb***a*ba*bb*bb**a*b*bb";
	cout << s.isMatch(s0, p0) << endl;	// 0
	cout << s.isMatch(s1, p1) << endl;	// 0
	cout << s.isMatch(s2, p2) << endl;	// 1
	cout << s.isMatch(s3, p3) << endl;	// 0
	cout << s.isMatch(s4, p4) << endl;	// 1
	cout << s.isMatch(s5, p5) << endl;	// 0
	cout << s.isMatch(s6, p6) << endl;	// 1
	cout << s.isMatch(s7, p7) << endl;	// 0
	return 0;
}