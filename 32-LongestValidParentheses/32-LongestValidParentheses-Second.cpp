#include <stack>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

// 匹配问题,用栈,压入下标
// time: O(n)
// space: O(n)
class Solution1 {
  public:
	int longestValidParentheses(string s) {
		int ans = 0, last = -1;
		stack<int> is;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '(') {
				is.push(i);
			}
			else {
				if (is.empty()) {
					last = i;
				} else {
					is.pop();
					if (is.empty())	// 栈空,说明和之前连上了"(()())"中的s[0]和s[5]
						ans = max(ans, i - last);
					else	// 栈不空,计算当前对即可 "(()())"中的s[1],s[2],s[3],s[4],尤其是s[3],s[4]计算得到长度4,pop之前的top到现在的top被消除了
						ans = max(ans, i - is.top());
				}
			}
		}
		return ans;
	}
};

// DP
// DP[i] = DP[i - 2] + 2 if s[i - 1] == '(' && s[i] == ')'
// DP[i] = DP[i - 1] + DP[i - 1 - dp[i - 1] - 1] + 2 if s[i - 1] == ')' && s[i] == ')' && s[i - dp[i - 1] - 1] == '('
// time: O(n)
// space: O(n)
class Solution2 {
  public:
	int longestValidParentheses(string s) {
		int ans = 0, len = s.size();
		vector<int> dp(len, 0);
		for (int i = 1; i < len; i++) {
			if (s[i] == ')') {
				if (s[i - 1] == '(')
					dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
				else if (i - dp[i - 1] > 0 && s[i - 1 - dp[i - 1]] == '(')
					dp[i] = dp[i - 1] + ((i - dp[i - 1]) >= 2 ? dp[i - dp[i - 1] - 2] : 0) + 2;
				ans = max(ans, dp[i]);
			}
		}
		return ans;
	}
};

// 往复扫描, 贪心
// time: O(n)
// space: O(1)
class Solution {
  public:
	int longestValidParentheses(string s) {
		int left = 0, right = 0, ans = 0;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '(') left++;
			else right++;
			if (left == right) ans = max(ans, right << 1);
			else if (right > left) left = right = 0;
		}
		left = right = 0;
		for (int i = s.size() - 1; i >= 0; i--) {
			if (s[i] == '(') left++;
			else right++;
			if (left == right) ans = max(ans, right << 1);
			else if (left > right) left = right = 0;
		}
		return ans;
	}
};

int main() {
	Solution s;
	string str0 = "(()";	// 2
	string str1 = ")()()()(()))";	// 10
	string str2 = ")()())";	// 4
	string str3 = ")(((()())))()(())"; // 16
	string str4 = ")(((()()))))()(())"; // 10
	string str5 = "()(()"; // 2
	cout << s.longestValidParentheses(str0) << endl;
	cout << s.longestValidParentheses(str1) << endl;
	cout << s.longestValidParentheses(str2) << endl;
	cout << s.longestValidParentheses(str3) << endl;
	cout << s.longestValidParentheses(str4) << endl;
	cout << s.longestValidParentheses(str5) << endl;
	return 0;
}