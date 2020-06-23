#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

// 模拟,末尾对齐,逐位相加
class Solution {
  public:
	string addBinary(string a, string b) {
		string ans; 
		int res = 0, sum = 0;
		reverse(a.begin(), a.end());
		reverse(b.begin(), b.end());
		auto p = a.begin();
		auto q = b.begin();
		while (p != a.end() || q!= b.end()) {
			sum = (*p == '1') + (*q == '1') + res;
			res = sum / 2;
			ans.push_back(to_string(sum % 2).c_str()[0]);
			if (p != a.end()) p++;
			if (q != b.end()) q++;
		}
		if (res) ans.push_back('1');
		reverse(ans.begin(), ans.end());
		return ans;
	}
};

// 循环进位-但这种方法C++无法实现,题目要求a,b length范围为1-10^4,除python外语言没有这么长的整数
class Solution1 {
  public:
	string addBinary(string a, string b) {
		int ia = stringToInt(a);
		int ib = stringToInt(b);
		while (ib) {
			int add = (ia ^ ib);	// 不进位的和
			int res = (ia & ib) << 1;	// 记录进位
			ia = add;
			ib = res;
		}
		return decToBin(ia);
	}
  private:
	int stringToInt(string a) {
		int ans = 0, i = 0;
		for (i = 0; i < a.size(); i++)
			ans += ((a[i] - '0') << (a.size() - i - 1));
		return ans;
	}
	string decToBin(int a) {
		string ans;
		do {
			ans.push_back(a % 2 + '0');
			a = a >> 1;
		} while(a);
		reverse(ans.begin(), ans.end());
		return ans;
	}
};

int main() {
	Solution s;
	// cout << s.addBinary("11", "1") << endl;
	// cout << s.addBinary("1010", "1011") << endl;
	// cout << s.addBinary("0", "0") << endl;
	cout << s.addBinary("10100000100100110110010000010101111011011001101110111111111101000000101111001110001111100001101",
	"110101001011101110001111100110001010100001101011101010000011011011001011101111001100000011011110011") << endl;
	return 1;
}