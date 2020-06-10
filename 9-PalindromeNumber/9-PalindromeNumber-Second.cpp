#include <string>
#include <vector>
#include <iostream>
using namespace std;

// 不能转为字符串来解决这个问题
class Solution1 {
  public:
	bool isPalindrome(int x) {
		string s = to_string(x);
		int l = 0, r = s.size() - 1;
		while (l < r)
			if (s[l++] != s[r--])
				return false;
		return true;
	}
};

// 剪枝
class Solution {
  public:
	bool isPalindrome(int x) {
		if (x < 0 || (x % 10 == 0 && x != 0))	// 剪枝
			return false;
		int revertedNum = 0;
		while (x > revertedNum) {
			revertedNum = revertedNum * 10 + x % 10;
			x /= 10;
		}
		return x == revertedNum || x == revertedNum / 10;	// 去除中位数
	}
};

// 不用字符串的常规解法
class Solution2 {
  public:
	bool isPalindrome(int x) {
		if (x < 0)
			return false;
		vector<int> ans(32, 0);
		int l = 0, r = 0;
		while (x) {
			ans[r++] = x % 10;
			x = x / 10;
		}
		r--;
		while (l < r)
			if (ans[l++] != ans[r--])
				return false;
		return true;
	}
};


int main() {
	Solution s;
	cout << s.isPalindrome(121) << endl;
	cout << s.isPalindrome(-121) << endl;
	cout << s.isPalindrome(1221) << endl;
	cout << s.isPalindrome(1231) << endl;
	return 1;
}