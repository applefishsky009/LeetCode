#include <string>
#include <vector>
#include <iostream>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// 递归
// time: O(3 * exp(SEG_COUNT) * |s|)
// space: O(SEG_COUNT)
class Solution {
  public:
	vector<string> restoreIpAddresses(string s) {
		const int n = s.size();
		vector<string> ans;
		string path;
		splitIpAddresses(s, 0, n, ans, path, 0);
		return ans;
	}
  private:
	void splitIpAddresses(string &s, int pos, const int &n, vector<string> &ans, string path, int step) {
		if (step == 4) {
			ans.push_back(path);
			return;
		}
		string path_tmp, cur_path;
		for (int i = pos; i <= pos + 2; ++i) {	// 寻找下一区间
			if (i >= n) break;	// 越界保护
			if (n - i - 1 > (4 - step - 1) * 3) continue;	// 剩余字符太多, 必然不是ip
			if (n - i - 1 < (4 - step - 1) * 1) continue;	// 剩余字符太少, 必然不是ip
			int seg_ip = string2Int(s, pos, i);
			if (seg_ip > 255) return;	// ip字段不合法, 因为只包含数字, 不用判断负数
			cur_path = to_string(seg_ip);
			if (cur_path.size() < i - pos + 1) break;	// 此次分隔以0开头, 不合法
			path_tmp = path;	// 记录合法字符
			if (!path_tmp.empty()) path_tmp += ".";
			path_tmp += cur_path;
			splitIpAddresses(s, i + 1, n, ans, path_tmp, step + 1);	// 找下一个区间
		}
	} 
	int string2Int(string &s, int start, int end) {
		int res = 0;
		while (start <= end) {
			res *= 10;
			res += (s[start++] - '0');
		}
		return res;
	}
};

int main() {
	Solution s;
	string s0 = "25525511135";	// 2
	string s1 = "010010";
	show1DVector(s.restoreIpAddresses(s0));
	show1DVector(s.restoreIpAddresses(s1));
	return 0;
}