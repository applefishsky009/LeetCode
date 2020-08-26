#include <string>
#include <vector>
#include <iostream>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// 回溯
// time : O(3^m + 4^n)
// space : O(m + n)
class Solution {
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

int main() {
	Solution s;
	show1DVector(s.letterCombinations("23"));
	return 0;
}