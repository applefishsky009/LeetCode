#include <stack>
#include <string>
#include <iostream>
using namespace std;

// 栈 - 空字符串认为是有效字符串, 意思是""返回true而不是字符串内包含空字符串
// time: O(n)
// space: O(n)
class Solution0 {
  public:
	bool isValid(string s) {
		if (s.size() & 1) return false;
		stack<char> istk;
		for (auto &c : s) {
			if (c == '(' || c == '[' || c == '{') istk.push(c);
			else if (istk.empty()) return false;
			else if ((c == ')' && istk.top() == '(') || 
					(c == ']' && istk.top() == '[') || 
					(c == '}' && istk.top() == '{')) istk.pop();
			else return false;
		}
		return istk.empty();
	}
};

// 栈
// time: O(n)
// space: O(n)
class Solution {
  public:
	bool isValid(string s) {
		if (s.size() & 1) return false;
		stack<char> istk;
		for (auto &c : s) {
			if (c == '(' || c == '[' || c == '{') istk.push(c);
			else if (istk.empty() || 
					(c == ')' && istk.top() != '(') || 
					(c == ']' && istk.top() != '[') || 
					(c == '}' && istk.top() != '{')) return false;
			else istk.pop();
		}
		return istk.empty();
	}
};

int main() {
	Solution s;
	string s0 = "()";	// 1
	string s1 = "()[]{}";	// 1
	string s2 = "(]";	// 0
	string s3 = "([)]";	// 0
	string s4 = "{[]}";	// 1
	string s5 = "[";	// 0
	cout << s.isValid(s0) << endl;
	cout << s.isValid(s1) << endl;
	cout << s.isValid(s2) << endl;
	cout << s.isValid(s3) << endl;
	cout << s.isValid(s4) << endl;
	cout << s.isValid(s5) << endl;
	return 0;
}