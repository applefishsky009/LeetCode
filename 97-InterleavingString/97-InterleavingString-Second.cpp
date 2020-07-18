#include <string>
#include <vector>
#include <iostream>
using namespace std;

// 朴素解法, 超时, 需要剪枝
class Solution1 {
  public:
	bool isInterleave(string s1, string s2, string s3) {
		if (s1.size() + s2.size() != s3.size()) return false;
		return isInterleave(s1, 0, s2, 0, s3, 0);
	}
  private:
	bool isInterleave(string s1, int spos1, string s2, int spos2, string s3, int spos3) {
		if (spos3 == s3.size()) return true;
		if (s1[spos1] == s3[spos3] && s2[spos2] == s3[spos3])
			return isInterleave(s1, spos1 + 1, s2, spos2, s3, spos3 + 1) || isInterleave(s1, spos1, s2, spos2 + 1, s3, spos3 + 1);
		if (s1[spos1] == s3[spos3])
			return isInterleave(s1, spos1 + 1, s2, spos2, s3, spos3 + 1);
		if (s2[spos2] == s3[spos3])
			return isInterleave(s1, spos1, s2, spos2 + 1, s3, spos3 + 1);
		return false;
	}
};

// DP
// 初始状态 DP[0][0] = 1, 并初始化DP[i][0], DP[0][j]
// DP[i][j] = dp[i - 1][j] if dp[i - 1][j] && s1[i] = s3[i + j] || dp[i][j - 1] if dp[i][j - 1] && s2[j] = s3[i + j]
// time: O(mn)
// space: O(mn)
class Solution2 {
  public:
	bool isInterleave(string s1, string s2, string s3) {
		int n = s1.size(), m = s2.size(), mn = s3.size();
		if (n + m != mn) return false;
		vector<vector<int>> idp(n + 1, vector<int>(m + 1, 0));
		idp[0][0] = 1;
		for (int i = 1; i < n + 1; ++i)
			idp[i][0] = (idp[i - 1][0] && s1[i - 1] == s3[i - 1]);
		for (int j = 1; j < m + 1; ++j)
			idp[0][j] = (idp[0][j - 1] && s2[j - 1] == s3[j - 1]);
		for (int i = 1; i < n + 1; ++i)
			for (int j = 1; j < m + 1; ++j)
				if (idp[i - 1][j] && s1[i - 1] == s3[i + j - 1] || idp[i][j - 1] && s2[j - 1] == s3[i + j - 1])
					idp[i][j] = 1;
		return idp[n][m];
	}
};

// DP - 合并初始化
// 初始状态 DP[0][0] = 1, 并初始化DP[i][0], DP[0][j]
// DP[i][j] = dp[i - 1][j] if dp[i - 1][j] && s1[i] = s3[i + j] || dp[i][j - 1] if dp[i][j - 1] && s2[j] = s3[i + j]
// time: O(mn)
// space: O(mn)
class Solution3 {
  public:
	bool isInterleave(string s1, string s2, string s3) {
		int n = s1.size(), m = s2.size(), mn = s3.size();
		if (n + m != mn) return false;
		vector<vector<int>> idp(n + 1, vector<int>(m + 1, 0));
		idp[0][0] = 1;
		for (int i = 0; i < n + 1; ++i) {
			for (int j = 0; j < m + 1; ++j) {
				if (i > 0)
					idp[i][j] |= (idp[i - 1][j] && s1[i - 1] == s3[i + j - 1]);	// idp[i][j]一定为0
				if (j > 0)
					idp[i][j] |= (idp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
			}
		}
		return idp[n][m];
	}
};

// DP - 合并初始化 - 滚动数组优化
// 初始状态 DP[0][0] = 1, 并初始化DP[i][0], DP[0][j]
// DP[i][j] = dp[i - 1][j] if dp[i - 1][j] && s1[i] = s3[i + j] || dp[i][j - 1] if dp[i][j - 1] && s2[j] = s3[i + j]
// time: O(mn)
// space: O(m)
class Solution {
  public:
	bool isInterleave(string s1, string s2, string s3) {
		int n = s1.size(), m = s2.size(), mn = s3.size();
		if (n + m != mn) return false;
		// vector<vector<int>> idp(n + 1, vector<int>(m + 1, 0));
		vector<int> idp(m + 1, 0);
		idp[0] = 1;
		for (int i = 0; i < n + 1; ++i) {
			for (int j = 0; j < m + 1; ++j) {
				if (i > 0)
					// idp[j] |= (idp[j] && s1[i - 1] == s3[i + j - 1]);	// 因为idp[j]不一定为0, 不能用这个式子
					idp[j] &= (s1[i - 1] == s3[i + j - 1]);
				if (j > 0)
					idp[j] |= (idp[j - 1] && s2[j - 1] == s3[i + j - 1]);
			}
		}
		return idp[m];
	}
};

int main() {
	Solution s;
	// string s1 = "aabcc";
	// string s2 = "dbbca";
	// string s3 = "aadbbcbcac";	// 1
	// string s1 = "aabcc";
	// string s2 = "dbbca";
	// string s3 = "aadbbbaccc";	// 0
	string s1 = "ab";
	string s2 = "bc";
	string s3 = "bcab";	// 1
	cout << s.isInterleave(s1, s2, s3) << endl;
	return 0;
}