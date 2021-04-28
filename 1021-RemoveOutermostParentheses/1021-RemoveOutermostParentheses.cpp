#include <stack>
#include <string>
#include <iostream>
#include <unordered_set>
using namespace std;

// stack 双指针->单指针也可以解
// time: O(n)
// space: O(n)
class Solution {
  public:
    string removeOuterParentheses(string s) {
        int i = 0;
        string ans;
        stack<char> istk;
        unordered_set<int> iset;    // 存放
        for (i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                if (istk.empty()) {
                    iset.insert(i);
                }
                istk.push(s[i]);
            } else {
                istk.pop();
                if (istk.empty()) {
                    iset.insert(i);
                }
            }
        }
        for (i = 0; i < s.size(); ++i) {
            if (iset.count(i) == 0) {
                ans.push_back(s[i]);
            }
        }
        return ans;
    }
};

int main() {
    Solution s1;
    // string s = "(()())(())";
    // string s = "(()())(())(()(()))";
    string s = "(()(()))()";
    cout << s1.removeOuterParentheses(s) << endl;
    return 0;
}
