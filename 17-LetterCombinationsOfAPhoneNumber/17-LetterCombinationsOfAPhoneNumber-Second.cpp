#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// 回溯
// time : O(3^m + 4^n)
// space : O(m + n)
class Solution0 {
  public:
	vector<string> letterCombinations(string digits) {
		if (digits.empty()) return vector<string> ();
		vector<string> ans;
		string tmp;
		dfs(ans, tmp, digits, 0);
		return ans;
	}
  private:
	vector<string> letter_map = {"", "", "abc", "def", "ghi",
							"jkl", "mno", "pqrs", "tuv", "wxyz"};
	void dfs(vector<string> & ans, string &tmp, string digits, int pos) {
		if (pos == digits.size()) {
			ans.push_back(tmp);
			return;
		}
		for (int i = 0; i < letter_map[digits[pos] - '0'].size(); ++i) {
			tmp +=  letter_map[digits[pos] - '0'][i];
			dfs(ans, tmp, digits, pos + 1);
			tmp.pop_back();
		}
	}
};

// 迭代
// time : O(3^m + 4^n)
// space : O(m + n)
class Solution {
  public:
	vector<string> letterCombinations(string digits) {
		if (digits.empty()) return vector<string> ();
		vector<string> ans(1, "");
		for (auto &d : digits) {
			const int n = ans.size();
			const int m = digitMap[d - '0'].size();
			ans.resize(n * m);	// 为新来的字符分配足够的空间
			for (int i = 1; i < m; ++i) // 为新的空间拷贝原来的值
				copy(ans.begin(), ans.begin() + n, ans.begin() + n * i);	// 循环扩充一倍
			for (int i = 0; i < m; ++i) {	// 为当前步赋合理值 - 扩充的倍数循环
				auto begin = ans.begin();	
				for_each(begin + n * i, begin + n * (i + 1), [&](string &s) { s += digitMap[d - '0'][i];});	// 为当前步赋予合理值
			}
		}
		return ans;
	}
  private:
    const vector<string> digitMap{"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
};

int main() {
	Solution s;
	show1DVector(s.letterCombinations("23"));
	return 0;
}