#include <cctype>
#include <string>
#include <iostream>
using namespace std;

class Solution {
  public:
	bool isPalindrome(string s) {
		int l = 0, r = s.size() - 1;
		while (l < r) {
			while (l < s.size() && !isalnum(s[l])) l++;
			while (r >= 0 && !isalnum(s[r])) r--;
			// if (l < s.size() && r >= 0 && tolower(s[l++]) != tolower(s[r--])) return false;	// 越界判断
			if (l < r && tolower(s[l++]) != tolower(s[r--])) return false;	// 越界判断
		}
		return true;
	}
};

int main() {
	Solution s;
	string str0 = "A man, a plan, a canal: Panama";
	string str1 = "race a car";
	// string str2 = "1   1";
	string str2 = ".,";
	// cout << s.isPalindrome(str0) << endl;
	// cout << s.isPalindrome(str1) << endl;
	cout << s.isPalindrome(str2) << endl;
	return 1;
}