#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

// 逐位相加 "123" * "456" = 100 * 456 + 20 * 456 + 3 * 456
// time: O(m + n)
// space: O(1)
class Solution0 {
  public:
	string multiply(string num1, string num2) {
		string ans(num1.size() + num2.size(), '0');
		for (int i = num1.size() - 1; i >= 0; --i) {	// 从低位到高位
			int carry = 0;
			for (int j = num2.size() - 1; j >= 0; --j) {	// 从低位到高位
				int tmp = ans[i + j + 1] - '0' + (num1[i] - '0') * (num2[j] - '0') + carry;	// 在当前位基础上计算增量数字和
				ans[i + j + 1] = tmp % 10 + '0';	// 余
				carry = tmp / 10;	// 进位
			}
			ans[i] += carry;	// 向前进一位, j = -1
		}
		size_t startpos = ans.find_first_not_of("0");
		return string::npos == startpos ? "0" : ans.substr(startpos);
	}
};

// 做加法 "123" * "456" = 100 * 456 + 20 * 456 + 3 * 456
// time: O(mn + n^2)
// space: O(m + n)
class Solution {
  public:
	string multiply(string num1, string num2) {
		if (num1 == "0" || num2 == "0") return "0";
		int m = num1.size(), n = num2.size();
		string ans = "";
		for (int i = n - 1; i >= 0; --i) {
			string cur;
			int add = 0;
			for (int j = n - 1; j > i; --j)	cur.push_back('0');	// 补十位百位的0, 低位先进
			int y = num2[i] - '0';	// 取一个数字
			for (int j = m - 1; j >= 0; --j) {	// 6 * 123 + 50 * 123 + 400 * 123 按位相乘进位
				int x = num1[j] - '0';
				int product = x * y + add;
				cur.push_back(product % 10 + '0');
				add = product / 10;
			}
			while (add != 0) {
				cur.push_back(add % 10 + '0');
				add /= 10;
			}
			reverse(cur.begin(), cur.end());
			ans = addStrings(ans, cur);			
		}
		return ans;
	}
  private:
	// LeetCode-415-按位模拟
	// time: O(max(len1, len2))
	// space: O(1)
	string addStrings(string num1, string num2) {
		int i = num1.size() - 1, j = num2.size() - 1, add = 0;
		string ans = "";
		while (i >= 0 || j >= 0 || add != 0) {
			int x = i >= 0 ? num1[i] - '0' : 0;
			int y = j >= 0 ? num2[j] - '0' : 0;
			int result = x + y + add;
			ans.push_back(result % 10 + '0');
			add = result / 10;
			--i;
			--j;
		}
		reverse(ans.begin(), ans.end());
		return ans;
	}
};

int main() {
	Solution s;
	string num1 = "123";
	string num2 = "456";
	cout << s.multiply(num1, num2) << endl;
	return 0;
}
